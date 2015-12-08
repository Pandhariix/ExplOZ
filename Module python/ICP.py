# PROGRAMMME DE RECALAGE POUR LA TEAM EXPLOZ

# Pour l'instant, on suppose que les nuages de points sont de même taille, à modifier ulterieurement

import numpy as np
import matplotlib.pyplot as plt

#Methods
###############################################################################
def sin(nbDegre):
    return np.sin(np.deg2rad(nbDegre))

def cos(nbDegre):
    return np.cos(np.deg2rad(nbDegre))




def loadTxtFile(fileName):
    
    X,Y = np.loadtxt(fileName, unpack = True)
    X.astype(int)
    Y.astype(int)
    
    return X,Y



def createMatrixFromArrays(X,Y):
    
    nbPts = X.size

    if(max(X) > max(Y)):
        size = max(X)
    else:
        size = max(Y)

    size = size + 1

    MatPts = np.array([])
    MatPts.resize(int(size),int(size))
    
    for i in range(nbPts):
        MatPts.itemset((int(X[i]),int(Y[i])),1)
    
    return MatPts



def createTransformationMatrix(Tx,Ty,Rz):
    
    T = np.array([])
    T.resize(3,3)
    
    T[0][0] = cos(Rz)
    T[0][1] = -sin(Rz)
    T[0][2] = Tx
    T[1][0] = sin(Rz)
    T[1][1] = cos(Rz)
    T[1][2] = Ty
    T[2][0] = 0
    T[2][1] = 0
    T[2][2] = 1
    
    return T
    

def product(X,Y,T):
    
    Xtemp = np.array([])
    Ytemp = np.array([])
    
    Xtemp.resize(X.size)
    Ytemp.resize(Y.size)    
    
    for i in range(X.size):
        Xtemp[i] = T[0][0]*X[i] + T[0][1]*Y[i] + T[0][2]
        Ytemp[i] = T[1][0]*X[i] + T[1][1]*Y[i] + T[1][2]
    
    X = Xtemp
    Y = Ytemp
    
    return X,Y
    


def centreDeMasse(X,Y):
    
    muX = 0
    muY = 0
    
    nbPoints = X.size
    
    for i in range(nbPoints):
        
        muX = muX + (1/nbPoints)*X[i]
        muY = muY + (1/nbPoints)*Y[i]
    
    return muX, muY
    


def SVD(Ox,Oy,Px,Py):
    
    muOx, muOy = centreDeMasse(Ox,Oy)
    muPx, muPy = centreDeMasse(Px,Py)
    
    OxPrime = np.array([])
    OyPrime = np.array([])
    PxPrime = np.array([])
    PyPrime = np.array([])
    
    OxPrime.resize(Ox.size)
    OyPrime.resize(Oy.size)
    PxPrime.resize(Px.size)
    PyPrime.resize(Py.size)
    
    for i in range(Ox.size):
        
        OxPrime[i] = Ox[i]-muOx
        OyPrime[i] = Oy[i]-muOy
        PxPrime[i] = Px[i]-muPx
        PyPrime[i] = Py[i]-muPy
        
    W = np.array([][])
    W.resize(2,2)
    
    W
        
#Main
###############################################################################

X, Y = loadTxtFile("ICP.txt")

plt.scatter(X,Y,100)
plt.xlabel('x')
plt.ylabel('y')

T = createTransformationMatrix(10,10,45)

X,Y = product(X,Y,T)

plt.scatter(X,Y,100)
plt.xlabel('x')
plt.ylabel('y')

plt.show