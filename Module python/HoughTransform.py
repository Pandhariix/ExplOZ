# PROGRAMMME DE VISUALISATION PYTHON POUR MYR 2016 TEAM EXPLOZ

import numpy as np
import matplotlib.pyplot as plt

#Methods
###############################################################################

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



def sin(nbDegre):
    return np.sin(np.deg2rad(nbDegre))

def cos(nbDegre):
    return np.cos(np.deg2rad(nbDegre))
    
def tan(nbDegre):
    return sin(nbDegre)/cos(nbDegre)

#Main
###############################################################################

X, Y, Z = np.loadtxt("data.txt", unpack=True)

X.astype(int)
Y.astype(int)


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
           



rho, theta, H = houghTransform(MatPts)

#detection des points interressants pour les intersections, selon la valeur du threshold

colsH = H[0].size
rowsH = H.size/H[0].size
threshold = 10

listePtsInteret = []

value1 = -20    # a choisir en fonction de l'echelle du graph
value2 = 140

for i in range(rowsH):
    for j in range(colsH):
        
        if H[i][j] >= threshold:
            
            if theta[j] == 0:
                listePtsInteret.append([[value1,value2],[rho[i],rho[i]]])
            
            elif theta[j] == 90:            
                listePtsInteret.append([[rho[i],rho[i]],[value1,value2]])

            elif theta[j] == -90:
                listePtsInteret.append([[-rho[i],-rho[i]],[value1,value2]])

            else:
                listePtsInteret.append([[value1,value2],[(-value1/tan(theta[j]))+(rho[i]/sin(theta[j])),(-value2/tan(theta[j]))+(rho[i]/sin(theta[j]))]])



plt.scatter(X,Y,100)
plt.title('Nuage de points avec Matplotlib')
plt.xlabel('x')
plt.ylabel('y')

for a in range(len(listePtsInteret)):
    plt.plot(listePtsInteret[a][0], listePtsInteret[a][1], 'r-', lw=2)

plt.show()

plt.imshow(H)