import matplotlib.pyplot as plt
import numpy as np
import serial
import time
serdev = '/dev/ttyACM0'
s = serial.Serial(serdev)
Fs = 128.0;  # sampling rate
for i in range(50):
    line=s.readline()
    print(line)