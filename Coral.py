import os
import cv2
import numpy as np
from PIL import Image, ImageDraw, ImageFont
import time
from multiprocessing import Process, Manager
from tflite_runtime.interpreter import load_delegate
from tflite_runtime.interpreter import Interpreter
import uart
from concurrent.futures import ThreadPoolExecutor, as_completed

# Focal length of the camera in pixels
FOCAL_LENGTH = 2571  # focal length(3600)/pixel size(1.4)
SPECIFIC_DISTANCE = 10

# Known widths of the objects in the real world (in some units, e.g., cm)
KNOWN_WIDTHS = {
    "car": 200,  # example width in cm
    "motorcycle": 70,
    "person": 50,
    "truck": 300,
    "tuktuk": 150,
    "van": 250,
    "bump": 600,  # example width in cm
    "stop_sign": 4.6,
    "no_right_turn": 60,
    "no_left_turn": 60,
    "no_parking": 60,
    "park": 60,
    "traffic-light-red": 30,
    "traffic-light-yellow": 30,
    "traffic-light-green": 30
}
# 
# Labels for each model
labels = [
    #["bump"],
    ["stop_sign", "limit","traffic-light-red", "traffic-light-yellow", "traffic-light-green","bump"],
    ["car", "motorcycle", "person", "truck", "tuktuk", "van"]
]

class Car:
    DIRECTIONS = {
        "go": "G",
        "stop": "S",
        "right": "R",
        "left": "L",
        "back": "B",
        "front_left": "FL",
        "front_right": "FR",
        "back_left": "BL",
        "back_right": "BR"
    }
    
    UART_TxCommands = {
    "fstop":        0x10,
    "stop":         0x20,
    "GO"  :         0x30,
    "leftH":        0x40,
    "leftM":        0x48,
    "leftL":        0x4c,
    "rightH":       0x50,
    "rightM":       0x58,
    "rightL":       0x5c,
    "decspeedH":    0x60,
    "decspeedM":    0x68,
    "decspeedL":    0x6c,
    "incspeedH":    0x70,
    "incspeedM":    0x78,
    "incspeedL":    0x7c,
    "bump":         0x08, #4 MSBs, add 4 LSBs for distance value
    "sign":         0x09, #4 MSBs, add 4 LSBs for sign number
    "lane":         0x0a, #4 MSBs, add 3 bits for distance, add 1 bit for direction (0 left, 1 right)
    "distance":     0x0b, #4 MSBs, add '0', add 3 LSBs for distance
    "distance_ext": 0x0b, #4 MSBs, add '1', add 3 LSBs for distance, send 8 bits instantly for extended distance 
    "v2vmsg":       0xff, #TODO
    "requestack":   0x0e, #4 MSBs, add '0', add 3 LSB for request number 
    "request_invld":0xe8, #sent request is not a valid request
    "ackerr":       0xf0  #sent ack is error (either ack or transmitted command is affected by noise, or no ack received) -> retransmit
    }

    UART_RxCommands = {
    #ack is 6 LSBs represent values in UART_TxCommands 
    "ackcmnd_min":  0x04,    #minimum ack
    "ackcmnd_max":  0x1b,   #maximum ack
    #data ack is 6 bit LSBs represents data sent
    "ackdata_min":  0x60,   #minimum data ack
    "ackdata_max":  0xbe,   #maximum data ack 
    "ackerr":       0x80,   #error in request valid response (requestack) followed by retransmission
    "nack":         0xa0,   #no ack sent -> retransmit
    "lanedata":     0xc0    #request lane data        
    }

    SPEEDS = {
        1: "1",
        2: "2",
        3: "3",
        4: "4",
        5: "5",
        6: "6",
        7: "7"
    }

    def __init__(self, uart_handler):
        self.uart_handler = uart_handler

    def update_state(self, direction):
        if direction in self.UART_TxCommands: # and speed in self.SPEEDS:
            self.send_command(self.UART_TxCommands[direction])
            #self.send_command(self.SPEEDS[speed])
        else:
            print("Invalid direction or speed")

    def send_command(self, command):
        if self.uart_handler:
            self.uart_handler.transmit(command)
            print(f"Sent command to UART buffer: {command}")

uart_handler = uart.UARTTransmitter(port='/dev/ttyS0', baud_rate=9600)
car = Car(uart_handler=uart_handler)

def action_stop_sign():
    car.update_state("stop")

def action_no_right_turn():
    pass

def action_no_left_turn():
    pass

def action_no_parking():
    pass

def action_park():
    car.update_state("stop", 1)

def action_traffic_light_red():
    pass

def action_traffic_light_yellow():
    pass

def action_traffic_light_green():
    pass

def action_bump():
    pass

def action_vehicle():
    pass

def action_person():
    pass

def GO_func():
    car.update_state("GO")

label_to_action = {
    "stop_sign": action_stop_sign,
    "no_right_turn": action_no_right_turn,
    "no_left_turn": action_no_left_turn,
    "no_parking": action_no_parking,
    "park": action_park,
    "traffic-light-red": action_traffic_light_red,
    "traffic-light-yellow": action_traffic_light_yellow,
    "traffic-light-green": action_traffic_light_green
}

def draw_boxes(image, results):
    draw = ImageDraw.Draw(image)
    font = ImageFont.load_default()
    detected_objects = {}

    for result in results:
        box, class_id, score, model_index = result
        x_min, y_min, x_max, y_max = box
        draw.rectangle([x_min, y_min, x_max, y_max], outline="white", width=5)
        label = labels[model_index][class_id]
        perceived_width = x_max - x_min
        distance = -3+(KNOWN_WIDTHS[label] * 3.6*640) / (perceived_width*3.68)
        draw.text((x_min, y_min), f'{label}: {score:.2f} Distance: {distance:.2f}', fill="white", font=font)
        if label in detected_objects:
            detected_objects[label].append(distance)
        else:
            detected_objects[label] = [distance]

    return detected_objects

def apply_nms(boxes, scores, threshold=0.5):
    picked_indices = []
    indices = np.argsort(scores)[::-1]

    while len(indices) > 0:
        current_index = indices[0]
        picked_indices.append(current_index)

        current_box = boxes[current_index]
        rest_of_indices = indices[1:]

        overlap_left = np.maximum(current_box[0], boxes[rest_of_indices][:, 0])
        overlap_top = np.maximum(current_box[1], boxes[rest_of_indices][:, 1])
        overlap_right = np.minimum(current_box[2], boxes[rest_of_indices][:, 2])
        overlap_bottom = np.minimum(current_box[3], boxes[rest_of_indices][:, 3])

        overlap_width = np.maximum(0, overlap_right - overlap_left + 1)
        overlap_height = np.maximum(0, overlap_bottom - overlap_top + 1)

        overlap_area = overlap_width * overlap_height
        current_area = (current_box[2] - current_box[0] + 1) * (current_box[3] - current_box[1] + 1)
        rest_of_areas = (boxes[rest_of_indices][:, 2] - boxes[rest_of_indices][:, 0] + 1) * (boxes[rest_of_indices][:, 3] - boxes[rest_of_indices][:, 1] + 1)

        iou = overlap_area / (current_area + rest_of_areas - overlap_area)

        indices = np.delete(indices, 0)
        indices = np.delete(indices, np.where(iou > threshold)[0])

    return picked_indices

def preprocess_image(image, input_size):
    image = image.convert('RGB')
    image = image.resize(input_size)
    image = np.array(image) / 255.0  # Normalize to [0, 1]
    image = np.expand_dims(image, axis=0)  # Add batch dimension
    return image.astype(np.float32)

def load_model(model_path):
    interpreter = Interpreter(model_path, experimental_delegates=[load_delegate('libedgetpu.so.1')])
    interpreter.allocate_tensors()
    return interpreter

def run_inference(interpreter, input_data):
    input_details = interpreter.get_input_details()
    output_details = interpreter.get_output_details()

    interpreter.set_tensor(input_details[0]['index'], input_data)
    interpreter.invoke()

    output_data = [interpreter.get_tensor(output_detail['index']) for output_detail in output_details]
    return output_data

def postprocess_output(output_data, input_size, original_size, confidence_threshold=0.5):
    detection_info = output_data[0]  # Assuming batch size of 1
    detection_info = detection_info[0].T

    results = []
    for detection in detection_info:
        class_probs = detection[4:]
        class_id = np.argmax(class_probs)
        class_score = class_probs[class_id]

        if class_score > confidence_threshold:
            x_center, y_center, width, height = detection[:4]
            x1 = int((x_center - width / 2) * input_size[0])
            y1 = int((y_center - height / 2) * input_size[1])
            x2 = int((x_center + width / 2) * input_size[0])
            y2 = int((y_center + height / 2) * input_size[1])

            # Scale coordinates back to original frame size
            x1 = int(x1 * original_size[0] / input_size[0])
            y1 = int(y1 * original_size[1] / input_size[1])
            x2 = int(x2 * original_size[0] / input_size[0])
            y2 = int(y2 * original_size[1] / input_size[1])

            box = [x1, y1, x2, y2]
            results.append((box, class_id, class_score))

    return results

def model_inference(interpreter, frame, input_size, confidence_threshold, model_index):
    original_size = frame.shape[1], frame.shape[0]  # (width, height)
    resized_frame = cv2.resize(frame, input_size)  # Resize to model input size
    image = Image.fromarray(cv2.cvtColor(resized_frame, cv2.COLOR_BGR2RGB))
    input_data = preprocess_image(image, input_size)
    output_data = run_inference(interpreter, input_data)
    results = postprocess_output(output_data, input_size, original_size, confidence_threshold)
    return [(result[0], result[1], result[2], model_index) for result in results]

def process_frame(interpreters, frame, input_size, confidence_threshold):
    results = []
    with ThreadPoolExecutor(max_workers=len(interpreters)) as executor:
        futures = [
            executor.submit(model_inference, interpreter, frame, input_size, confidence_threshold, model_index)
            for model_index, interpreter in enumerate(interpreters)
        ]
        for future in as_completed(futures):
            results.extend(future.result())
    return results

def detect_objects(model_paths, camera_index=0, input_size=(320, 320), confidence_threshold=0.5, output_video_path='camera.mp4'):
    interpreters = [load_model(model_path) for model_path in model_paths]
    cap = cv2.VideoCapture(camera_index)
    
    if not cap.isOpened():
        print(f"Error: Unable to access camera at index {camera_index}")
        return
    
    fourcc = cv2.VideoWriter_fourcc(*'mp4v')
    width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
    fps = cap.get(cv2.CAP_PROP_FPS)
    fps = 5
    out = cv2.VideoWriter(output_video_path, fourcc, fps, (width, height))
    
    action_triggered = []
    detected_objects = {}
    i=0

    while True:
        ret, frame = cap.read()
        if not ret:
            print("Failed to grab frame")
            break
        
        start_time = time.time()
        results = process_frame(interpreters, frame, input_size, confidence_threshold)
        end_time = time.time()
        print(f"Total time taken for inference: {end_time - start_time} seconds")

        if results:
            boxes = np.array([result[0] for result in results])
            scores = np.array([result[2] for result in results])
            picked_indices = apply_nms(boxes, scores, threshold=0.5)
            filtered_results = [results[i] for i in picked_indices]

            image = Image.fromarray(cv2.cvtColor(frame, cv2.COLOR_BGR2RGB))
            detected_objects = draw_boxes(image, filtered_results)
            frame_with_boxes = cv2.cvtColor(np.array(image), cv2.COLOR_RGB2BGR)
            out.write(frame_with_boxes)
            cv2.imshow('Detection', frame_with_boxes)

            nearest_distance = float('inf')
            nearest_label = None
            for label, distances in detected_objects.items():
                for distance in distances:
                    if distance < nearest_distance:
                        nearest_distance = distance
                        nearest_label = label

            if nearest_label:
                if nearest_label not in action_triggered: 
                    print(f"Nearest {nearest_label}: {nearest_distance} cm")
                    if nearest_label in label_to_action and nearest_distance <= SPECIFIC_DISTANCE:
                        label_to_action[nearest_label]() 
                        action_triggered.append(nearest_label)
                        i = 1
                    else:
                        if(i == 1):
                            GO_func()
                            i=0
        else:
            print("No object detected")
            action_triggered.clear()
            if(i == 1):
                GO_func()
                i=0
            out.write(frame)
            cv2.imshow('Detection', frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    out.release()
    cv2.destroyAllWindows()
    car.update_state("stop")
    uart_handler.close()

if __name__ == "__main__":
    start_time = time.time()
    
    model_paths = ['/home/raspberrypi/Desktop/esraa_comp_best_integer_quant_edgetpu.tflite']
    input_size = (320, 320)
    confidence_threshold = 0.5
    output_video_path = 'camera.mp4'
    car.update_state("GO")
    detect_objects(model_paths, camera_index=0, input_size=input_size, confidence_threshold=confidence_threshold, output_video_path=output_video_path)
    end_time = time.time()
    print(f"Total time taken for inference: {end_time - start_time} seconds")
