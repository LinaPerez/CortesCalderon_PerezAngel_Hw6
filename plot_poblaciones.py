#Este programa grafica los resultados del archivo rungekutta_cazadoresPresas_1.c
import sys
import pylab
import numpy as np

#recogemos el nombre del archivo.dat que entra como parametro
nombredatos = sys.argv[1]

#cargar datos del archivo
datos = np.loadtxt(nombredatos)

#definir arreglos para graficar
x = datos[:,1]
y = datos[:,2]

l=list(nombredatos)
n=len(l)
l[n-4:n]=[]
nombredatos="".join(l)

#Graficar
pylab.plot(x,y)
pylab.xlabel('X')
pylab.ylabel('Y')
pylab.title('Poblaciones x-y')
pylab.savefig(str(nombredatos)+'.pdf')
