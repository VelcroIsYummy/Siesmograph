import serial

# Serial port configuration
port_name = '/dev/cu.usbmodem1101'  # Replace with your Arduino's port name
baud_rate = 115200

# File path to save the data
file_path = 'bl1.txt'

try:
    # Open serial port
    ser = serial.Serial(port_name, baud_rate)
    print(f"Serial port '{port_name}' opened successfully")

    # Open the file in append mode
    with open(file_path, 'a') as file:
        print(f"File '{file_path}' opened successfully")
        i = -1
        while True:
            # Read data from serial port
            data = ser.readline().decode().strip()
            
            # Print data to console
            print(data)
            i = i+1
            
            # Write data to file
            file.write(data + ','+ str(i) +'\n')
            
            # Flush data to disk
            file.flush()

except serial.SerialException as e:
    print(f"Error opening serial port: {e}")

except FileNotFoundError as e:
    print(f"Error opening file: {e}")
