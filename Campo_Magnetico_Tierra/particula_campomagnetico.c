#include<stdio.h>
#include<math.h>
#include<stdlib.h>

float func_prime_velocity(float masa, float c, float energia_cinetica);


int main (int argc, char **argv){
  int i;
  int j;
  
  float h = 0.01;
  float min_t = 0.0;
  float max_t = 100.0;
  float n_points = ((max_t - min_t) / h);
/*
Inicializar punteros que representan las listas para las funciones y, x, z &  t
 */
  float* x;
  float* y;
  float* z; 
  float* t;
  FILE* data;
  float pitch;
  float energia_cinetica; 
  float c = 299759458; // velocidad de la luz m/s // 
  float masa = 0.00000000000000000000000000167; //kg masa del proton en reposo // 
  float Radio = 6378100; //metros del radio de la Tierra//
  float To = min_t;

/*revisa el numero de argumentos que entra en al consola */ 
  if(argc!=3){
    printf("debe introducir los parámetros de energía cinética y el ángulo pitch");
    exit(1);
  }


/*Dimensiones de los punteros */
  x = malloc(n_points*sizeof(float));
  y = malloc(n_points*sizeof(float));
  z = malloc(n_points*sizeof(float));
  t = malloc(n_points*sizeof(float));

  energia_cinetica = atof(argv[1]); 
  pitch = atof(argv[2]);
  
/*llenando los punteros de 0.0s */
  for (i=0;i<n_points;i++){
    x[i]=0.0;
    y[i]=0.0;
    z[i]=0.0;
    t[i]=0.0;
    if(i==0){
      x[i] = 2*Radio;
    }
  }
  /* HASTA AQUI LLEGAMOOOOOOOOOSSSSSSSS!!!!!!!!
     /* definiendo las variables apra rungekutta*/

  float k1x;
  float k1y;
  float k2x;
  float k2y;
  float k3x;
  float k3y;
  float k4x;
  float k4y;
  float average_kx;
  float average_ky;
  float y1;
  float y2;
  float y3;
  float x1;
  float x2;
  float x3;
  float t1;
  float t2;
  float t3;

/*Empezando RungeKutta4*/

  for (i=1;i<n_points;i++){
    
    k1x = func_primex(x[i-1],y[i-1]);
    k1y = func_primey(x[i-1],y[i-1]);
    
  

/*Primer paso */

    t1 = t[i-1] + (h/2.0);
    y1 = y[i-1] + (h/2.0) * k1y;
    x1 = x[i-1] + (h/2.0) * k1x;
    k2x = func_primex(x1, y1);
    k2y= func_primey(x1, y1);
    
/*Segundo paso */

    t2 = t[i-1] + (h/2.0);
    y2 = y[i-1] + (h/2.0) * k2y;
    x2 = x[i-1] + (h/2.0) * k2x;  
    k3x = func_primex(x2, y2);
    k3y = func_primey(x2, y2);
        
/*Tercer paso */

    t3 = t[i-1] + h;
    y3 = y[i-1] + h * k3y;
    x3 = x[i-1] + h * k3x;
    k4x = func_primex(x3, y3);
    k4y = func_primey(x3, y3);
    
/*Cuarto paso */

    average_kx = (1.0/6.0)*(k1x + 2.0*k2x + 2.0*k3x + k4x);
    average_ky = (1.0/6.0)*(k1y + 2.0*k2y + 2.0*k3y + k4y);
    
    t[i] = t[i-1] + h;
    y[i] = y[i-1] + h * average_ky;
    x[i] = x[i-1] + h * average_kx;
}
  char n[150];
  sprintf(n,"trayectoria_%.0f_%.0f.dat",energia_cinetica,pitch);
  data = fopen(n, "w");

  for(i=0;i<n_points;i++){
    fprintf(data, "%f %f %f %f \n", t[i], x[i], y[i], z[i]);
}
 
  return 0;
}

float func_prime_velocity(float masa, float c, float energia_cinetica){
  float v; 
  float ff;
  ff = energia_cinetica + (masa*pow(c,2));
  v = c * (sqrt(((pow(masa, 2)*pow(c, 4))/(pow(ff, 2)))-1));
  return v;
}
