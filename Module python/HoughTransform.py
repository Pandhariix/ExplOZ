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


def translateLidarData(angle, distance):
    
    predivDist = 1
    
    X = np.array([])
    Y = np.array([])    
    
    Xlist = list()
    Ylist = list()    
    
    for i in range (angle.size):
        if distance[i] != 4000:
            Xlist.append((distance[i]/predivDist)*cos(angle[i]))
            Ylist.append((distance[i]/predivDist)*sin(angle[i]))
    
    X.resize(len(Xlist))
    Y.resize(len(Ylist))

    for i in range (len(Xlist)):
        X[i] = Xlist[i]
        Y[i] = Ylist[i]        
    
    return X, Y

#Main
###############################################################################

#X, Y, Z = np.loadtxt("data.txt", unpack=True)
angle, distance = np.loadtxt("lidar.txt", unpack=True)

X, Y = translateLidarData(angle, distance)

X,Y,Z = np.loadtxt("results.txt", unpack=True)

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
threshold = 6

listePtsInteret = list()

xGauche = -15
xDroit = 10
yBas = 0
yHaut = 15

value1 = xGauche    # a choisir en fonction de l'echelle du graph
value2 = xDroit

for i in range(rowsH):
    for j in range(colsH):
        
        if H[i][j] >= threshold:
            
            
            if ((theta[j] < 3)-(theta > -3)).any():
               listePtsInteret.append([[rho[i],rho[i]],[yBas,yHaut]])
               
            elif ((theta[j] < 183)-(theta > -177)).any(): 
                  listePtsInteret.append([[rho[i],rho[i]],[yBas,yHaut]])
            '''
            epsilon = 0.0001
            listePtsInteret.append([[value1,value2],[(-value1/(tan(theta[j])+epsilon))+(rho[i]/(sin(theta[j])+epsilon)),(-value2/(tan(theta[j])+epsilon))+(rho[i]/(sin(theta[j])+epsilon))]])            
            '''
            '''
            if theta[j] == 0:
                listePtsInteret.append([[rho[i],rho[i]],[yBas,yHaut]])
                
            elif theta[j] == 180:
                listePtsInteret.append([[-rho[i],-rho[i]],[yBas,yHaut]])
            
            elif theta[j] == 90:
                listePtsInteret.append([[xGauche,xDroit],[rho[i], rho[i]]])
                
            elif theta[j] == -90:
                listePtsInteret.append([[xGauche,xDroit],[-rho[i], -rho[i]]])
                
            else:
                listePtsInteret.append([[xGauche,xDroit],[(-xGauche/tan(theta[j]))+(rho[i]/sin(theta[j])),(-xDroit/tan(theta[j]))+(rho[i]/sin(theta[j]))]])
            '''
            
            #Lignes classiques transformee de Hough
            '''
            if theta[j] == 0:
                listePtsInteret.append([[value1,value2],[rho[i],rho[i]]])
            
            elif theta[j] == 90:            
                listePtsInteret.append([[rho[i],rho[i]],[value1,value2]])

            elif theta[j] == -90:
                listePtsInteret.append([[-rho[i],-rho[i]],[value1,value2]])

            else:
                listePtsInteret.append([[value1,value2],[(-value1/tan(theta[j]))+(rho[i]/sin(theta[j])),(-value2/tan(theta[j]))+(rho[i]/sin(theta[j]))]])
            '''


plt.scatter(X,Y,100)
plt.axis([xGauche, xDroit, yBas, yHaut])
plt.title('Nuage de points avec Matplotlib')
plt.xlabel('x')
plt.ylabel('y')

for a in range(len(listePtsInteret)):
    plt.plot(listePtsInteret[a][0], listePtsInteret[a][1], 'r-', lw=2)
    
plt.show()