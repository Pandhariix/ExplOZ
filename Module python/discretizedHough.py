# -*- coding: utf-8 -*-
"""
Created on Thu Feb 18 14:05:59 2016

@author: Max

Programme de discretisation de l'espace et de detection de lignes via Hough
"""

#Imports
###############################################################################
import numpy as np
import matplotlib.pyplot as plt


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


#Discretization
##########
def discretizeMap(X,Y):
    
    xr = np.linspace(0, 39, 40)
    yr = np.linspace(0, 19, 20)    
    
    discretizedMatrix = np.array([])
    discretizedMatrix.resize(20,40)
    
    for j in range(len(xr)):
        for i in range(len(yr)):
            
            for k in range(len(X)):
                
                if X[k]+4000 > 200*j and X[k]+4000 < 200*(j+1) and Y[k] > 200*i and Y[k] < 200*(i+1):
                    discretizedMatrix[i][j] += 1
                    
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
            
    return discretizedMatrix, Xdiscret, Ydiscret

#fill matrix
##########
def fillPointMatrix(Xdiscret, Ydiscret):
    
    MatPts = np.array([])
    MatPts.resize(40,40)    
    
    for i in range(len(Xdiscret)):
        MatPts.itemset((int(Ydiscret[i]), int(Xdiscret[i])),1)
        
    return MatPts


#Hough
##########    
def houghTransform(MatPts, theta_res = 1, rho_res = 1):
    
    nRows = MatPts[0].size
    nCols = MatPts[0].size
    
    theta = np.linspace(-90.0, 0.0, np.ceil(90.0/theta_res) + 1.0)
    theta = np.concatenate((theta, -theta[len(theta)-2::-1]))
    
    D = np.sqrt((nRows - 1)**2 + (nCols - 1)**2)
    q = np.ceil(D/rho_res)
    nrho = 2*q + 1
    rho = np.linspace(-q*rho_res, q*rho_res, nrho)
    H = np.zeros((len(rho), len(theta)))
    
    for rowIdx in range(nRows):
        for colIdx in range(nCols):
            if MatPts[rowIdx, colIdx]:
                for thIdx in range(len(theta)):
                    rhoVal = colIdx*np.cos(theta[thIdx]*np.pi/180.0) + \
                        rowIdx*np.sin(theta[thIdx]*np.pi/180)
                    rhoIdx = np.nonzero(np.abs(rho-rhoVal) == np.min(np.abs(rho-rhoVal)))[0]
                    H[rhoIdx[0], thIdx] += 1
                    
    return rho, theta, H    



#Main
###############################################################################

angle, distance = fileParser("lidar.txt")

X,Y = translateLidarData(angle, distance)

discretizedMatrix = discretizeMap(X,Y)

discretizedMatrix, Xdiscret, Ydiscret = thresholding(discretizedMatrix, 2)

writeResults("results.txt",Xdiscret,Ydiscret)

MatPts = fillPointMatrix(Xdiscret, Ydiscret)

rho, theta, H = houghTransform(MatPts)

#####degueu

colsH = H[0].size
rowsH = H.size/H[0].size
threshold = 6

listePtsInteret = list()

xGauche = -20
xDroit = 20
yBas = 0
yHaut = 20

value1 = xGauche    # a choisir en fonction de l'echelle du graph
value2 = xDroit

for i in range(rowsH):
    for j in range(colsH):
        
        if H[i][j] >= threshold:
            
            epsilon = 0
            listePtsInteret.append([[value1,value2],[(-value1/(tan(theta[j])+epsilon))+(rho[i]/(sin(theta[j])+epsilon)),(-value2/(tan(theta[j])+epsilon))+(rho[i]/(sin(theta[j])+epsilon))]])

#####


plt.scatter(Xdiscret, Ydiscret, 100)
plt.axis([xGauche, xDroit, yBas, yHaut])
plt.title('Nuage de points avec Matplotlib')
plt.xlabel('x')
plt.ylabel('y')

for a in range(len(listePtsInteret)):
    plt.plot(listePtsInteret[a][0], listePtsInteret[a][1], 'r-', lw=2)
    
plt.show()

plt.imshow(H)
