import cv2 as cv
import matplotlib.pyplot as plt
import matplotlib.patches as patches
from PIL import Image
import numpy as np
from numpy import inf as INF
import random

fig = plt.figure()
ax = plt.axes()

inputFile = open("./tests/4.in","r")
rectCount = int(inputFile.readline())
maxX,maxY=-INF,-INF
minX,minY=INF,INF
random.seed(0)
for i in range(0,rectCount):
    curLine = inputFile.readline()
    curLine = curLine.split(' ')
    
    rect = patches.Rectangle((int(curLine[0]), int(curLine[2])),int(curLine[1])-int(curLine[0]), int(curLine[3])-int(curLine[2]), linewidth=1, edgecolor=(0,0,1,1), facecolor=(1.0,1.0,0.5,0.5))
    ax.add_patch(rect)
    minX = min(minX,int(curLine[0]))
    minY = min(minY,int(curLine[2]))
    maxX = max(maxX,int(curLine[1]))
    maxY = max(maxY,int(curLine[3]))

inputFile = open("./tests/tcase4.out","r")
measure = inputFile.readline()

count = int(inputFile.readline())

for i in range(0,count):
    curLine = inputFile.readline()
    curLine = curLine.split(' ')
    print(curLine)
    plt.plot([int(curLine[0]),int(curLine[1])],[int(curLine[2]),int(curLine[2])],color='r',linewidth=2)

count = int(inputFile.readline())

for i in range(0,count):
    curLine = inputFile.readline()
    curLine = curLine.split(' ')
    print(curLine)
    plt.plot([int(curLine[2]),int(curLine[2])],[int(curLine[1]),int(curLine[0])],color='r',linewidth=2)
contour = inputFile.readline()
plt.title("Measure is " + measure +"\nContour is " + contour)


plt.xlim([minX-2,maxX+2])
plt.ylim([minY-2,maxY+2])

plt.show()