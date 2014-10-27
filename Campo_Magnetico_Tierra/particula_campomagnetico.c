#include<stdio.h>
#include<math.h>
#include<stdlib.h>

float func_prime_vx(float , float , float );
float func_prime_vy(float , float , float );
float func_prime_vz(float , float , float );


int main (int argc, char **argv){
  int i;
  int j;
  
  float h = 0.01;
  float min_t = 0.0;
  float max_t = 100.0;
  float n_points = ((max_t - min_t) / h);
/*
Inicializar punteros que representan las listas para las funciones y, x, z, vx, vy, vz &  t
 */
  float* x;
  float* y;
  float* z; 
  float* t;
  float* vx;
  float* vy;
  float* vz;
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
  vx = malloc(n_points*sizeof(float));
  vy = malloc(n_points*sizeof(float));
  vz = malloc(n_points*sizeof(float));
  t = malloc(n_points*sizeof(float));

/*Entradas por consola */
  energia_cinetica = atof(argv[1]); 
  pitch = atof(argv[2]);
  pitch_rad = (pitch*math.pi)/180;
  
/*llenando los punteros de 0.0s */
  for (i=0;i<n_points;i++){
    x[i]=0.0;
    y[i]=0.0;
    z[i]=0.0;
    t[i]=0.0;
    vx[i]=0.0;
    vy[i]=0.0;
    vz[i]=0.0;
    if(i==0){
      x[i] = 2*Radio;
      vy[i] = v*math.cos(pitch_rad);
      vz[i] = v*math.sin(pitch_rad);
    }
  }
  
  float v; 
  float ff;
  ff = energia_cinetica + (masa*pow(c,2));
  v = c * (sqrt(((pow(masa, 2)*pow(c, 4))/(pow(ff, 2)))-1));
  float lambda = 1/(sqrt(1-((pow(v,2))/(pow(c,2)))));

  /* guardar archivo
}
  char n[150];
  sprintf(n,"trayectoria_%.0f_%.0f.dat",energia_cinetica,pitch);
  data = fopen(n, "w");

  for(i=0;i<n_points;i++){
    fprintf(data, "%f %f %f %f \n", t[i], x[i], y[i], z[i]);
}
 */
  return 0;
}

float func_prime_vx(float , float , float ){
 
  return ;
}
float func_prime_vy(float masa, float c, float energia_cinetica){
 
  return ;
}
float func_prime_vz(float masa, float c, float energia_cinetica){
 
  return ;
}
