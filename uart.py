import serial
import threading
import time

class CircularBuffer:
    def __init__(self, max_size):
        self.buffer = []
        self.max_size = max_size
        self.lock = threading.Lock()

    def append(self, item):
        with self.lock:
            if len(self.buffer) >= self.max_size:
                # If the buffer is full, remove the last item (lowest priority)
                self.buffer.pop(-1)
            self.buffer.append(item)
            # Sort the buffer based on command value (lower value means higher priority)
            self.buffer.sort()

    def pop(self):
        with self.lock:
            if self.buffer:
                # Pop the highest priority item (first one)
                return self.buffer.pop(0)
            return None

    def is_empty(self):
        with self.lock:
            return len(self.buffer) == 0
        
        
class UARTHandler:
    def __init__(self, port='/dev/ttyUSB0', baudrate=9600):
        self.ser = serial.Serial(port, baudrate)
        self.lock = threading.Lock()
        self.running = True
        self.buffer = CircularBuffer(max_size=100)
        self.thread = threading.Thread(target=self.transmit_from_buffer)
        self.thread.start()

    def send_command(self, command):
        self.buffer.append(command)
        #print(f"Command added to buffer: {command}")

    def transmit_from_buffer(self):
        while self.running:
            if not self.buffer.is_empty():
                command = self.buffer.pop()
                if command:
                    data_bytes = bytes.fromhex(command)
                    with self.lock:
                        self.ser.write(data_bytes)
                        #print(f"Command sent: {command}")
            time.sleep(0.1)  # Adjust the sleep time as needed for your use case

    def close(self):
        self.running = False
        self.thread.join()
        self.ser.close()
        print("Serial port closed.")