import tkinter as tk
from tkinter import messagebox
import serial
import time

# Serial port settings
SERIAL_PORT = 'COM3'  # Replace with your Arduino's serial port
BAUD_RATE = 9600

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE)
    time.sleep(2)  # Wait for the connection to initialize
except:
    messagebox.showerror("Error", "Cannot open serial port.")
    exit()

def send_rgb():
    try:
        r = int(entry_red.get())
        g = int(entry_green.get())
        b = int(entry_blue.get())
        
        if 0 <= r <= 255 and 0 <= g <= 255 and 0 <= b <= 255:
            ser.write(f"{r},{g},{b}\n".encode())
            label_status.config(text=f"Sent: {r},{g},{b}")
        else:
            messagebox.showerror("Error", "RGB values must be between 0 and 255.")
    except ValueError:
        messagebox.showerror("Error", "Please enter valid integers for RGB values.")

# Create the main window
root = tk.Tk()
root.title("RGB LED Controller")

# Create and place widgets
tk.Label(root, text="Red (0-255):").grid(row=0, column=0)
entry_red = tk.Entry(root)
entry_red.grid(row=0, column=1)

tk.Label(root, text="Green (0-255):").grid(row=1, column=0)
entry_green = tk.Entry(root)
entry_green.grid(row=1, column=1)

tk.Label(root, text="Blue (0-255):").grid(row=2, column=0)
entry_blue = tk.Entry(root)
entry_blue.grid(row=2, column=1)

button_send = tk.Button(root, text="Send", command=send_rgb)
button_send.grid(row=3, columnspan=2)

label_status = tk.Label(root, text="Status: Not sent")
label_status.grid(row=4, columnspan=2)

# Run the Tkinter event loop
root.mainloop()

# Close the serial connection when the GUI is closed
ser.close()
