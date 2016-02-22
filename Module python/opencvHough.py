# -*- coding: utf-8 -*-
"""
Created on Sun Feb 21 22:09:34 2016

@author: Max
"""

#Imports
###############################################################################
import sys
import numpy as np
import matplotlib.pyplot as plt
import cv2


#Class
###############################################################################
class Point:
    def __init__(self):
        self.x = 0.0
        self.y = 0.0
    
    def setData(self,x,y):
        self.x = x
        self.y = y
    
    def setX(self,x):
        self.x = x
    
    def setY(self,y):
        self.y = y
        


#Methods
###############################################################################

#Angles
##########
def sin(nbDegre):
    return np.sin(np.deg2rad(nbDegre))

def cos(nbDegre):
    return np.cos(np.deg2rad(nbDegre))
    
def tan(nbDegre):
    return sin(nbDegre)/cos(nbDegre)



#File parser
##########
def fileParser(filename):

    angle, distance = np.loadtxt(filename, unpack=True)
    return angle, distance    


#Write results in txt file
##########
def writeResults(filename,Xres,Yres):

    fichier = open(filename,'w')
    
    for i in range(len(Xres)):
        fichier.write(str(Xres[i])+" "+str(Yres[i])+" "+"0\n")
        
    fichier.close
    
    

#Data extraction
##########
def translateLidarData(angle, distance): 
    
    X = list()
    Y = list()    
    
    for i in range (angle.size):
        if distance[i] != 4000:
            X.append(distance[i]*cos(angle[i]))
            Y.append(distance[i]*sin(angle[i]))        
    
    return X, Y




#Mapping
##########
def mapping(X,Y):
    
    img = np.zeros((4000,8000,3), np.uint8)
    
    img[2000][1000] = 255
    
    return img 

#Discretization mapping
##########
def discretizeMap(X,Y, factor):    
    
    xr = np.linspace(0, (8000/factor)-1, 8000/factor)
    yr = np.linspace(0, (4000/factor)-1, 4000/factor)    
    
    discretizedMatrix = np.zeros((4000/factor,8000/factor,3), np.uint8)
    
    for j in range(len(xr)):
        for i in range(len(yr)):
            
            for k in range(len(X)):
                
                if X[k]+4000 > factor*j and X[k]+4000 < factor*(j+1) and Y[k] > factor*i and Y[k] < factor*(i+1):
                    discretizedMatrix[i][j] += 255
                    
    return discretizedMatrix
    

#Thresholding
##########    
def thresholding(discretizedMatrix, threshold):
    
    Xdiscret = list()
    Ydiscret = list()    
    
    for i in range(discretizedMatrix.size/discretizedMatrix[0].size):
        for j in range(discretizedMatrix[0].size):
            
            if discretizedMatrix[i][j] < threshold:
                discretizedMatrix[i][j] = 0

            else:
                Xdiscret.append(j-20)
                Ydiscret.append(i)
            
    return discretizedMatrix
    

#Back to the original space
########## 
def translateLinesBack(lineList, factor):
    
    resList = list()    
    
    for i in range(len(lineList)):
        
        resList.append([((lineList[i][0][0]*factor)-4000,(lineList[i][0][1]*factor)-4000),(lineList[i][1][0]*factor, lineList[i][1][1]*factor)]) 
             
    return resList

#Main
###############################################################################

if len(sys.argv) > 1:
    myfile = sys.argv[1]

else:
    print("please enter the name of the point cloud file\nlidar.txt selected\n\n")
    myfile = "lidar.txt" #default

factor = 8

angle, distance = fileParser(myfile)

X,Y = translateLidarData(angle, distance)

img = discretizeMap(X,Y, factor)
#imgP = img
#img = cv2.imread("chess.jpg")

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

ret, thresh = cv2.threshold(gray,127,255,cv2.THRESH_BINARY)
edges = cv2.Canny(gray,50,150,apertureSize = 3)

lines = cv2.HoughLines(edges,1,np.pi/180,20)

lineList = list()

for i in range(lines.size/2):
    
    for rho,theta in lines[i]:
        a = np.cos(theta)
        b = np.sin(theta)
        x0 = a*rho
        y0 = b*rho
        x1 = int(x0 + 1000*(-b))
        y1 = int(y0 + 1000*(a))
        x2 = int(x0 - 1000*(-b))
        y2 = int(y0 - 1000*(a))
        
        cv2.line(img,(x1,y1),(x2,y2),(0,0,255),2)
        
        lineList.append([(x1,y1),(x2,y2)])

lineList = translateLinesBack(lineList, factor)
'''
minLineLength = 0
maxLineGap = 400
linesP = cv2.HoughLinesP(edges,1,np.pi/180,5,minLineLength,maxLineGap)

for i in range(linesP.size/2):
    
    for xa,ya,xb,yb in linesP[i]:
        cv2.line(imgP,(xa,ya),(xb,yb),(0,255,0),2)
'''

cv2.imshow('Hough standard',img)
#cv2.imshow('Probabilistic Hough', imgP)
#plt.imshow(img)
cv2.waitKey(0)
cv2.destroyAllWindows()