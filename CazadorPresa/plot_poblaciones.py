#Este programa grafica los resultados del archivo rungekutta_cazadoresPresas_1.c
import sys
import matplotlib.pyplot as plt
import numpy as np

#recogemos el nombre del archivo.dat que entra como parametro
nombredatos = sys.argv[1]

#cargar datos del archivo
datos = np.loadtxt(nombredatos)

#definir arreglos para graficar
x = datos[:,1]
y = datos[:,2]

#saber cuales fueron las condiciones iniciales
l=list(nombredatos)
n=len(l)
l[n-4:n]=[]
nombredatos="".join(l)

#Graficar
plt.plot(x,y)
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Poblaciones X-Y')
plt.savefig(str(nombredatos)+'.pdf')
