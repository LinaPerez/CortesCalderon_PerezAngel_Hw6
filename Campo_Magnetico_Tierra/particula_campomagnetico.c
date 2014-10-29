#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void campo_dipolo (float* b, float* r);
void aceleracion (float* a, float* v, float* b);

int main (int argc, char **argv){
  int i;
  int j;
  float pi = 3.1416;
  
  float h = 0.000001;
  float min_t = 0.0;
  float max_t = 100.0;
  float n_points = ((max_t - min_t) / h);
/*
Inicializar punteros que representan las listas para las funciones y, x, z, vx, vy, vz &  t
 */
  float* b;
  float* a;
  float* v; 
  float* r;
  FILE* data;
  float pitch;
  float energia_cinetica; 
  float c = 299759458; // velocidad de la luz m/s // 
  float masa = 0.00000000000000000000000000167; //kg masa del proton en reposo // 
  float Radio = 6378100; //metros del radio de la Tierra//
  float To = min_t;
  float Bo = 0.00003; // Teslas del campo magnetico en el ecuador //
/*revisa el numero de argumentos que entra en al consola */ 
  if(argc!=3){
    printf("debe introducir los parámetros de energía cinética y el ángulo pitch");
    exit(1);
  }


/*Dimensiones de los punteros */
  r = malloc(3*sizeof(float));
  b = malloc(3*sizeof(float));
  a = malloc(3*sizeof(float));
  v = malloc(3*sizeof(float));
 

/*Entradas por consola */
  energia_cinetica = atof(argv[1]); 
  pitch = atof(argv[2]);
 float  pitch_rad = (pitch*pi)/180.0;

  /*valor inicial de la velocidad a partir de energia cinetica */
  float v_o; 
  float ff;
  ff = energia_cinetica + (masa*pow(c,2));
  v_o = c * (sqrt(((pow(masa, 2)*pow(c, 4))/(pow(ff, 2)))-1));
  float lambda = 1/(sqrt(1-((pow(v_o,2))/(pow(c,2)))));
  
  /*valores iniciales para r y v */
  for (i=0;i<3;i++){
    
    if(i==0){
      r[i] = 2*Radio;
      v[i] = 0.0;
      
    }
    if(i==1){
      r[i] = 0.0;
      v[i] = v_o*sin(pitch_rad);
      
    }
    if(i==2){
      r[i] = 0.0;
      v[i] = v_o*cos(pitch_rad);
      
    }
    
  }
  
  /* RungeKutta 4 orden */

  for(i=0; i<3; i++){

    /* usar constantes ?
    float a1;
    float a2;
    float a3;
    float a4;
    float v1;
    float v2;
    float v3;
    float v4;
    */
   
    campo_dipolo (b, r);
    aceleracion (a, v, b);

    v[i] = v[i] + (h/2.0) * a[i];
    r[i] = r[i] + (h/2.0) * v[i];
    campo_dipolo (b, r);
    aceleracion (a, v, b);


    v[i] = v[i] + (h/2.0) * a[i];
    r[i] = r[i] + (h/2.0) * v[i];
    campo_dipolo (b, r);
    aceleracion (a, v, b);

    v[i] = v[i] + (h/2.0) * a[i];
    r[i] = r[i] + (h/2.0) * v[i];
    campo_dipolo (b, r);
    aceleracion (a, v, b);



  }




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

void campo_dipolo (float* b, float* r){
  float R = sqrt(pow(r[0], 2)+pow(r[1], 2) + pow(r[2], 2)); 
  float Radio = 6378100;
  float Bo = 0.00003;
  b[0]= (-1*(Bo*pow(Radio, 3)/pow(R, 5)) * (3*r[0]*r[2])); 
  b[1]= (-1*(Bo*pow(Radio, 3)/pow(R, 5)) * (3*r[1]*r[2]));
  b[2]= (-1*(Bo*pow(Radio, 3)/pow(R, 5)) * (2*pow(r[2],2) - pow(r[0], 2) - pow(r[1], 2)));

}
void aceleracion (float* a, float* v, float* b){
  a[0] = (b[2]*v[1]) - (v[2]*b[1]);
  a[1] = (b[2]*v[0]) - (v[2]*b[0]);
  a[2] = (b[1]*v[0]) - (v[1]*b[0]);
 
}
