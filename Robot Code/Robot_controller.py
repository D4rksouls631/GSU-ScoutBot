
# Import Serial Port
import serial
# Use Pygame to access the Xbox One Controller
import pygame

from time import sleep
from pygame.constants import JOYBUTTONDOWN
pygame.init()

joysticks = []
for i in range(0, pygame.joystick.get_count()):
    joysticks.append(pygame.joystick.Joystick(i))
    joysticks[-1].init()

# Print out the name of the controller
print(pygame.joystick.Joystick(0).get_name())
# open serial port
ser = serial.Serial('COM6', 115200, timeout=.1)

# check which port was really used
print(ser.name)
# Xbox Joystick Axis:
# Axis 0 up down, down value is -1, up value is 1
# Axis 1 Left, Right, Left value is: -1, right value is 1
# center is always 0

# Main Loop
while True:
    
    incomingData = ser.readline().decode()[:-2]
    print(incomingData)
    '''
    dataSplit = incomingData.split(',')
    mpu_accel_x = dataSplit[0]
    mpu__accel_y = dataSplit[1]
    mpu_accel_z = dataSplit[2]
    mpu_gyro_x = dataSplit[3]
    mpu_gyro_y = dataSplit[4]
    mpu_gyro_z = dataSplit[5]
    mpu_temp = dataSplit[6]
    dist_1 = dataSplit[7]
    dist_2 = dataSplit[8]
    dist_3 = dataSplit[9]
    md_1 = dataSplit[10]
    md_1 = dataSplit[11]
    '''
    ls_vertical = 0
    ls_horizontal = 0
    rs_vertical = 0
    rs_horizontal = 0
    drivetrainLeftSideSpeed=0
    drivetrainRightSideSpeed=0
    sleep(1)
    for event in pygame.event.get():
        # Check for joystick events
        if event.type == JOYBUTTONDOWN:
            if event.button == 0:
                print("button 0 down")
            if event.button == 1:
                print("button 1 down")
            if event.button == 2:
                print("button 2 down")
            if event.button == 3:
                print("button 4 down")
            if event.button == 5:
                print("button 5 down")
            if event.button == 6:
                print("button 6 down")
            if event.button == 7:
                print("button 7 down")
            if event.button == 8:
                print("button 8 down")
            if event.button == 9:
                print("button 9 down")
        if event.type == pygame.JOYAXISMOTION:
            # Left stick
            if event.axis == 2:  # left/right
                if event.value < 0.5 or event.value > 0.5:
                    ls_horizontal = event.value
                    print(f"motor_speed: {ls_horizontal}")
                    sleep(0.01)
            if event.axis == 1:  # up/down
                if event.value < 0.5 or event.value > 0.5:
                    ls_vertical = event.value
                    print(f"motor_speed: {ls_vertical}")
                    sleep(0.01)
                else:
                    ls_vertical = 0
            # Right stick
            if event.axis == 2:  # left/right
                if event.value < 0.5 or event.value > 0.5:
                    rs_horizontal = event.value
                    #print(f"motor_speed: {rs_horizontal}")
                    sleep(0.01)
            if event.axis == 3:  # up/down
                if event.value < 0.5 or event.value > 0.5:
                    rs_vertical = event.value
                    #print(f"motor_speed: {rs_vertical}")
                    sleep(0.01)
                else:
                    rs_vertical = 0

            drivetrainLeftSideSpeed = ls_vertical + rs_horizontal
            drivetrainRightSideSpeed = ls_vertical - rs_horizontal
    
    print(("{0:.2f},{1:.2f}".format(drivetrainLeftSideSpeed*100, drivetrainRightSideSpeed*100)))
    ser.write(str(str(drivetrainLeftSideSpeed*100)+"," + str(drivetrainRightSideSpeed*100)))
