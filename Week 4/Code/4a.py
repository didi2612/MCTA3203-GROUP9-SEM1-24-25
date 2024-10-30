# Group 9 Referenced to matplotlib packages

import serial
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import time

ser = serial.Serial('COM6', 9600)
time.sleep(2)
x_positions = [0]
y_positions = [0]
gestures = []
THRESHOLD_X = 5000
THRESHOLD_Y = 5000
dt = 0.1

def detect_gesture(ax, ay, gx, gy):

    if abs(ax) > THRESHOLD_X and abs(gy) > THRESHOLD_Y:
        return "Wave"
    elif ax < -THRESHOLD_X and ay > THRESHOLD_Y:
        return "Swipe Left"
    elif ax > THRESHOLD_X and ay > THRESHOLD_Y:
        return "Swipe Right"
    return "Detecting"


def update_plot(frame):
    global x_positions, y_positions


    line = ser.readline().decode().strip()
    if "AX" in line and "AY" in line:
        try:
            ax = int(line.split("AX: ")[1].split(" ")[0])
            ay = int(line.split("AY: ")[1].split(" ")[0])
            gx = int(line.split("GX: ")[1].split(" ")[0])
            gy = int(line.split("GY: ")[1].split(" ")[0])
            gesture = detect_gesture(ax, ay, gx, gy)
            gestures.append(gesture)
            new_x = x_positions[-1] + ax * (dt ** 2)
            new_y = y_positions[-1] + ay * (dt ** 2)
            x_positions.append(new_x)
            y_positions.append(new_y)
            if len(x_positions) > 100:
                x_positions.pop(0)
                y_positions.pop(0)
            ax_plot.clear()
            ax_plot.plot(x_positions, y_positions, marker='o')
            ax_plot.set_xlim(-10000, 10000)
            ax_plot.set_ylim(-10000, 10000)
            ax_plot.set_xlabel("X Position")
            ax_plot.set_ylabel("Y Position")
            ax_plot.set_title(f"Hand Movement: {gesture}")
        except ValueError:
            # Handle parsing errors
            print("Error parsing data")


fig, ax_plot = plt.subplots()
ani = FuncAnimation(fig, update_plot, interval=10, save_count=10000)
plt.show()
ser.close()
