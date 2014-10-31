#Este programa grafica los resultados del archivo particula_campo.c
import sys
import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d.axes3d import Axes3D

#recogemos el nombre del archivo.dat que entra como parametro
datosparticula = sys.argv[1]

#cargar datos del archivo
datos = np.loadtxt(datosparticula)

#definir arreglos para graficar
x = datos[:,1]
y = datos[:,2]
z = datos[:,3]

#saber cuales fueron las condiciones iniciales
l=list(datosparticula)
n=len(l)
l[n-4:n]=[]
nombredatos="".join(l)

#Graficar primero al trayectoria en x-y
plt.plot(x,y)
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Trayectoria 2D')
plt.savefig(str(nombredatos)+'.pdf')

#Gracia 3D de la trayectoria en el plano x, y, z
figura = plt.figure()
tp = Axes3D(figura)
tp.set_xlabel("$X$",fontsize=20)
tp.set_ylabel("$Y$",fontsize=20)
tp.set_zlabel("$Z$",fontsize=20)
tp.set_title("$\mathrm{Trayectoria Particula en 3D}$", fontsize=30)
tp.plot(x, y, z)
plt.savefig(str(nombredatos)+'_3D_'+'.pdf')

