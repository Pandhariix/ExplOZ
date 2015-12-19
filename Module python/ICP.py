# PROGRAMMME DE RECALAGE POUR LA TEAM EXPLOZ

# nuages de points de meme taille, a modif

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
        
        muX = muX + X[i]
        muY = muY + Y[i]
    
    muX = muX/nbPoints
    muY = muY/nbPoints    
    
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
        
    
    OVectorPrime = np.array([])
    PVectorPrime = np.array([])

    OVectorPrime.resize(2, OxPrime.size)
    PVectorPrime.resize(2, PxPrime.size)
    
    for i in range(2):
        for j in range(OVectorPrime[0].size):
            
            if i==0:
                OVectorPrime[i][j] = OxPrime[j]
            else:
                OVectorPrime[i][j] = OyPrime[j]
    
    for i in range(2):
        for j in range(PVectorPrime[0].size):
            
            if i==0:
                PVectorPrime[i][j] = PxPrime[j]
            else:
                PVectorPrime[i][j] = PyPrime[j]    
    
    W = np.array([])
    W.resize(2,2)

    W =  np.matrix(OVectorPrime)*np.matrix(PVectorPrime.T)
    
    U,S,Vtranspos = np.linalg.svd(W)

    R = U*Vtranspos
    t = np.matrix([muOx, muOy]).T-R*np.matrix([muPx, muPy]).T
    
    T = np.array([])
    T.resize(3,3)
    
    T[0][0] = R.item(0,0)
    T[0][1] = R.item(0,1)
    T[0][2] = t.item(0,0)
    T[1][0] = R.item(0,1)
    T[1][1] = R.item(1,1)
    T[1][2] = t.item(1,0)
    T[2][0] = 0
    T[2][1] = 0
    T[2][2] = 1

    return T
        
#Main
###############################################################################

Ox, Oy = loadTxtFile("ICP.txt")

plt.scatter(Ox,Oy,100)
plt.xlabel('x')
plt.ylabel('y')

T = createTransformationMatrix(2,2,2)

Px,Py = product(Ox,Oy,T)

plt.scatter(Px,Py,100, c = 'r')
plt.xlabel('x')
plt.ylabel('y')

icpT = SVD(Ox,Oy,Px,Py)

PxRecalage, PyRecalage = product(Px,Py,icpT)

plt.scatter(PxRecalage,PyRecalage,100, c = 'g')
plt.xlabel('x')
plt.ylabel('y')

plt.show