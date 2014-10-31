all: particle_in_field.x trayectoria_3.000000_30.000000.dat trayectoria_3.000000_30.000000.pdf trayectoria_3.000000_30.000000_3D.pdF

particle_in_field.x: particula_campomagnetico.c
	cc rungekutta_cazadoresPresas_1.c -lm -o runge_kutta.x
# Si se desean cambiar los valores que entran por consola se debe tener en cuenta que los archivos trayectoria_3_30.dat trayectora_3_30.pdf y trayectoria_3_30_3D.pdf y el comando ./particle_in_field.x 3.0 30.0. Se debe cambiar 3.0 por la energía cinética en megaelectronvolts deseada y el numero 30.0 por el pitch angle deseado en grados. Por favor mantenga las cifras decimales que se imponen.

trayectoria_3.000000_30.000000.dat: particle_in_field.x
	./particle_in_field.x 3.0 30.0
trayectoria_3.000000_30.000000.pdf: trayectoria_3.000000_30.000000.dat graficas_esfera.py
	python graficas_esfera.py  trayectoria_3.000000_30.000000.dat
	open trayectoria_3.000000_30.000000.pdf
trayectoria_3.000000_30.000000_3D.pdf: trayectoria_3.000000_30.000000.dat graficas_esfera.py
	python graficas_esfera.py  trayectoria_3.000000_30.000000.dat
	open trayectoria_3.000000_30.000000_3D.pdf
