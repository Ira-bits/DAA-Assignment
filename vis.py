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

for i in range(0,rectCount):
	curLine = inputFile.readline()
	curLine = curLine.split(' ')
	random.seed(i)
	rect = patches.Rectangle((int(curLine[0]), int(curLine[2])),int(curLine[1])-int(curLine[0]), int(curLine[3])-int(curLine[2]), linewidth=0, edgecolor=(1,0,0,1), facecolor=(random.random(),random.random(),random.random(),0.5))
	ax.add_patch(rect)
	minX = min(minX,int(curLine[0]))
	minY = min(minY,int(curLine[2]))
	maxX = max(maxX,int(curLine[1]))
	maxY = max(maxY,int(curLine[3]))

inputFile = open("./tests/tcase4.out","r")
measure = inputFile.readline()
plt.title("Measure is " + measure)

while True:
	curLine = inputFile.readline()
	if not curLine:
		break
	curLine = curLine.split(' ')
	print(curLine)
	plt.plot([int(curLine[0]),int(curLine[1])],[int(curLine[2]),int(curLine[2])],color='r',linewidth=2)

plt.xlim([minX-10,maxX+10])
plt.ylim([minY-10,maxY+10])

plt.show()
