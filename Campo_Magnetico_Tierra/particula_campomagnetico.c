#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void campo_dipolo (float* b, float* r);
void aceleracion (float* a, float* v, float* b);

int main (int argc, char **argv){
  int i;
  int j;
  int m;
  float pi = 3.1416;
  
  float h = 1E-6;
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
  float* t;
  FILE* data;
  float pitch;
  float energia_cinetica1; 
  float c = 299759458; // velocidad de la luz m/s // 
  float masa = 1.67E-27; //kg masa del proton en reposo // 
  float Radio = 6378100; //metros del radio de la Tierra//
  float To = min_t;
  float Bo = 3E-5; // Teslas del campo magnetico en el ecuador //
  float carga = 1.16E-19; // Coulombs 
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
  t = malloc(n_points*sizeof(float));
 

/*Entradas por consola */
  energia_cinetica1 = atof(argv[1]); 
  pitch = atof(argv[2]);
 float  pitch_rad = (pitch*pi)/180.0;
 float energia_cinetica = energia_cinetica1*1.60217733E-13; // energia cinetica en joules 

  /*valor inicial de la velocidad a partir de energia cinetica */
  float v_o; 
  float ff;
  ff = energia_cinetica + (masa*pow(c,2));
  v_o = c * (sqrt(((-pow(masa, 2)*pow(c, 4))/(pow(ff, 2)))+1));

  

  float lambda = 1/(sqrt(1-((pow(v_o,2))/(pow(c,2)))));

  float lxm = (carga/(lambda*masa)); //constantes ṕara el producto cruz
  
  /*valores iniciales para r y v */
  for(i=0;i<n_points;i++){
    t[i]=0.0;
  }
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
  char n[150];
  sprintf(n,"trayectoria_%.0f_%.0f.dat",energia_cinetica1,pitch);
  data = fopen(n, "w");
  
  /* RungeKutta 4 orden */
  float t1 = min_t;
  for(j=1; j<n_points;j++){
    t1 = j* h;
    
    
    
    float a1x;
    float a1y;
    float a1z;
    float a2x;
    float a2y;
    float a2z;
    float a3x;
    float a3y;
    float a3z;
    float a4x;
    float a4y;
    float a4z;
    float v1x;
    float v1y;
    float v1z;
    float v2x;
    float v2y;
    float v2z;
    float v3x;
    float v3y;
    float v3z;
    float v4x;
    float v4y;
    float v4z;
    float r1x;
    float r1y;
    float r1z;
    float r2x;
    float r2y;
    float r2z;
    float r3x;
    float r3y;
    float r3z;
    float r4x;
    float r4y;
    float r4z; 
    
    campo_dipolo (b, r);
    aceleracion (a, v, b);
    
    a1x= a[0]*lxm;
    a1y= a[1]*lxm;
    a1z= a[2]*lxm;
    
    
    
    v1x = v[0] + ((h/2.0) * a1x);
    v1y = v[1] + ((h/2.0) * a1y);
    v1z = v[2] + ((h/2.0) * a1z);      
    r1x = r[0] + ((h/2.0) * v1x);
    r1y = r[1] + ((h/2.0) * v1y);
    r1z = r[2] + ((h/2.0) * v1z);
    v[0] = v1x;
    v[1] = v1x;
    v[2] = v1x;
    r[0] = r1x;
    r[1] = r1y;
    r[2] = r1z;
    
    
    campo_dipolo (b, r);
    aceleracion (a, v, b);
    
    a2x= a[0]*lxm;
    a2y= a[1]*lxm;
    a2z= a[2]*lxm;
    
    v2x = v[0] + ((h/2.0) * a2x);
    v2y = v[1] + ((h/2.0) * a2y);
    v2z = v[2] + ((h/2.0) * a2z);      
    r2x = r[0] + ((h/2.0) * v2x);
    r2y = r[1] + ((h/2.0) * v2y);
    r2z = r[2] + ((h/2.0) * v2z);
    v[0] = v2x;
    v[1] = v2y;
    v[2] = v2z;
    r[0] = r2x;
    r[1] = r2y;
    r[2] = r2z;
    
    
    
    campo_dipolo (b, r);
    aceleracion (a, v, b);
    
    a3x= a[0]*lxm;
    a3y= a[1]*lxm;
    a3z= a[2]*lxm;
    
    v3x = v[0] + ((h/2.0) * a3x);
    v3y = v[1] + ((h/2.0) * a3y);
    v3z = v[2] + ((h/2.0) * a3z);      
    r3x = r[0] + ((h/2.0) * v3x);
    r3y = r[1] + ((h/2.0) * v3y);
    r3z = r[2] + ((h/2.0) * v3z);
    v[0] = v3x;
    v[1] = v3y;
    v[2] = v3z;
    r[0] = r3x;
    r[1] = r3y;
    r[2] = r3z;
    
    campo_dipolo (b, r);
    aceleracion (a, v, b);
    
    a4x= a[0]*lxm;
    a4y= a[1]*lxm;
    a4z= a[2]*lxm;
    
    
    float average_vx = (1.0/6.0)*(a1x+(2.0*a2x)+(2.0*a3x)+a4x);
    float average_rx = (1.0/6.0)*(v1x+(2.0*v2x)+(2.0*v3x)+v4x);
    float average_vy = (1.0/6.0)*(a1y+(2.0*a2y)+(2.0*a3y)+a4y);
    float average_ry = (1.0/6.0)*(v1y+(2.0*v2y)+(2.0*v3y)+v4y);
    float average_vz = (1.0/6.0)*(a1z+(2.0*a2z)+(2.0*a3z)+a4z);
    float average_rz = (1.0/6.0)*(v1z+(2.0*v2z)+(2.0*v3z)+v4z);
    
    v[0] = v3x + (h*average_vx);
    r[0] = r3x + (h*average_rx);
    v[1] = v3y + (h*average_vy);
    r[1] = r3y + (h*average_ry);
    v[2] = v3z + (h*average_vz);
    r[2] = r3z + (h*average_rz);
     
    
    for(m=100;m<n_points;m+=100){
      if(m==j){
    
	

	  fprintf(data, "%f %f %f %f \n", t1, r[0], r[1], r[2]);

      }
    }
  }    

  return 0;
}

void campo_dipolo (float* b, float* r){
  float R = sqrt(pow(r[0], 2)+pow(r[1], 2) + pow(r[2], 2)); 
  float Radio = 6378100;
  float Bo = 3E-5;
  b[0]= (-1*(Bo*pow(Radio, 3)/pow(R, 5)) * (3*r[0]*r[2])); 
  b[1]= (-1*(Bo*pow(Radio, 3)/pow(R, 5)) * (3*r[1]*r[2]));
  b[2]= (-1*(Bo*pow(Radio, 3)/pow(R, 5)) * (2*pow(r[2],2) - pow(r[0], 2) - pow(r[1], 2)));

}
void aceleracion (float* a, float* v, float* b){


  a[0] = (b[2]*v[1]) - (v[2]*b[1]);
  a[1] = (b[2]*v[0]) - (v[2]*b[0]);
  a[2] = (b[1]*v[0]) - (v[1]*b[0]);
 
}
