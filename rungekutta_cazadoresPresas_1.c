#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void func_primex(float x, float y);
void func_primey(float x, float y);
int main (int argc, char **argv){
  int i;
  int j;
  
  float h = 0.01;
  float min_t = 0.0;
  float max_t = 1.0;
  float n_points = ((max_t - min_t) / h);
/*
Inicializar punteros que representan las listas para las funciones y, x &  t
 */
  float x*;
  float y*;
  float t*;
  FILE* datos;

  float Xo = 20.0;
  float Yo = 30.0;
  float To = min_t;
/*Dimensiones de los punteros */
  x = malloc(n_points*sizeof(float));
  y = malloc(n_points*sizeof(float));
  t = malloc(n_points*sizeof(float));
/*llenando los punteros de 0.0s */
  for (i=0;i<n_points;i++){
    x[i]=0.0;
    y[i]=0.0;
    t{i]=0.0;
  }
/*Empezando RungeKutta4*/

  for (i=1;i<n_points;i++){
    
    k1x = func_primex(x[i-1],y[i-1]);
    k1y = func_primey(x[i-1],y[i-1]);
    
/*Primer paso */

    t1 = t[i-1] + (h/2.0);
    y1 = y[i-1] + (h/2.0) * k1y;
    x1 = x[i-1] + (h/2.0) * k1x;
    k2x = func_primex(x1, y1);
    K2y= func_primey(x1, y1);
    
/*Segundo paso */

    t2 = t[i-1] + (h/2.0);
    y2 = y[i-1] + (h/2.0) * k2y;
    x2 = x[i-1] + (h/2.0) * k2x;  
    k3x = func_primex(x3, y3);
    k3y = func_primey(x3, y3);
        
/*Tercer paso */

    t3 = t[i-1] + h;
    y3 = y[i-1] + h * k3y;
    x3 = x[i-1] + h * k3x;
    k4x = func_primex(x4, y4);
    k4y = func_primey(x4, y4);
    
/*Cuarto paso */

    average_kx = (1.0/6.0)*(k1x + 2.0*k2x + 2.0*k3x + k4x);
    average_ky = (1.0/6.0)*(k1y + 2.0*k2y + 2.0*k3y + k4y);
    
    t[i] = t[i-1] + h;
    y[i] = y[i-1] + h * average_ky;
    x[i] = x[i-1] + h * average_kx;
}

  datos = fopen("poblaciones.dat"."w");
  for(i=0;i<n_points;i++){
    fprint(datos, "%f %f %f \n", t[i], x[i], y[i]);
}

  return 0;
}

void func_primex(x_,y_){
  return (20*x_) - (x_*y_) ;
}
void func_primey(x_,y_){
  return (-30*y_) + (x*y_);
}
