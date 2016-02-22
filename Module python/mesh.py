from mpl_toolkits.mplot3d.axes3d import Axes3D
import matplotlib.pyplot as plt


# imports specific to the plots in this example
import numpy as np
from matplotlib import cm
from mpl_toolkits.mplot3d.axes3d import get_test_data

def sin(nbDegre):
    return np.sin(np.deg2rad(nbDegre))

def cos(nbDegre):
    return np.cos(np.deg2rad(nbDegre))
    
def tan(nbDegre):
    return sin(nbDegre)/cos(nbDegre)


def translateLidarData(angle, distance):
    
    predivDist = 100
    
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

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

angle, distance = np.loadtxt("lidar.txt", unpack=True)

X, Y = translateLidarData(angle, distance)

xs = np.linspace(min(X)-3, max(X)+3, (max(X)-min(X)).astype(int)+6)
ys = np.linspace(min(Y)-3, max(Y)+3, (max(Y)-min(Y)).astype(int)+6)

Xp, Yp = np.meshgrid(xs, ys)


Zp = np.array([])
Zp.resize(ys.size,xs.size)

Z = np.array([])
Z.resize(ys.size,xs.size)

for i in range(ys.size):
    for j in range(xs.size):
        for k in range(X.size):
            
            if xs[j].astype(int) == X[k].astype(int) and ys[i].astype(int) == Y[k].astype(int):
                Zp[i][j] = 2
                break
            else:
                Zp[i][j] = 0


ax.plot_surface(Xp, Yp, Zp, rstride=2, cstride=2, alpha=0.4,cmap=cm.jet)

ax.set_zlim3d(0,6)
ax.set_ylim3d(0,45)
ax.set_xlim3d(-30,30)

plt.show()