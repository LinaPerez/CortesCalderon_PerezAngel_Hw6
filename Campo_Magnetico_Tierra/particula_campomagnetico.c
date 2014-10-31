#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define h 1E-5
#define min_t 0.0
#define max_t 100.0
#define pi 3.1415
#define c 299759458
#define masa 1.67E-27
#define Radio 6378100
#define Bo 3E-5
#define carga 1.16E-19


void campo_dipolo (float* r, float* a, float* v, float energia_cinetica);

int main (int argc, char **argv){
  int i;
  int j;
  int m;
  float n_points = ((max_t - min_t) / h);

/*
Inicializar punteros que representan las listas para las funciones y, x, z, vx, vy, vz &  t
 */
  float* b;
  float* a;
  float* a1;
  float* a2;
  float* a3;
  float* v; 
  float* r;
  float* t;
  FILE* data;
  float pitch;
  float energia_cinetica1; 
  float To = min_t;

/*revisa el numero de argumentos que entra en al consola */ 

  if(argc!=3){
    printf("debe introducir los parámetros de energía cinética y el ángulo pitch");
    exit(1);
  }


/*Dimensiones de los punteros */
  r = malloc(3*sizeof(float));
  b = malloc(3*sizeof(float));
  a = malloc(3*sizeof(float));
  a1 = malloc(3*sizeof(float)); 
  a2 = malloc(3*sizeof(float)); 
  a3 = malloc(3*sizeof(float));
  v = malloc(3*sizeof(float));
  t = malloc(n_points*sizeof(float));
 

/*Entradas por consola */
  energia_cinetica1 = atof(argv[1]); 
  pitch = atof(argv[2]);
  float  pitch_rad = (pitch*pi)/180.0;
  float energia_cinetica = (energia_cinetica1*1.60217733E-13); // energia cinetica en joules 

 
  float v_o1 = energia_cinetica/(masa*pow(c,2));
  float v_o2 = (1.0/((v_o1)+1.0));
  float v_o3 = 1-(pow(v_o2,2));
  float v_o4 = c*(sqrt(v_o3));
  float v_o = v_o4;

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
  /* RungeKutta 4 orden */
  float t1 = min_t;
  for(j=1; j<n_points;j++){
    t1 = j* h;
    
    
     
    
    campo_dipolo (r, a, v, energia_cinetica);
   
    a1x= a[0];
    a1y= a[1];
    a1z= a[2];
    
    
    
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
    
    
   campo_dipolo (r, a1, v, energia_cinetica);
    
    a2x= a1[0];
    a2y= a1[1];
    a2z= a1[2];
    
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
    
    
    
    campo_dipolo (r, a2, v, energia_cinetica);

    
    a3x= a2[0];
    a3y= a2[1];
    a3z= a2[2];
    
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
    
    campo_dipolo (r, a3, v, energia_cinetica);
    
    a4x= a3[0];
    a4y= a3[1];
    a4z= a3[2];
    
    
    float average_vx = (1.0/6.0)*(a1x+(2.0*a2x)+(2.0*a3x)+a4x);
    float average_vy = (1.0/6.0)*(a1y+(2.0*a2y)+(2.0*a3y)+a4y);
    float average_vz = (1.0/6.0)*(a1z+(2.0*a2z)+(2.0*a3z)+a4z);
    float average_rx = (1.0/6.0)*(v1x+(2.0*v2x)+(2.0*v3x)+v4x);
    float average_ry = (1.0/6.0)*(v1y+(2.0*v2y)+(2.0*v3y)+v4y);
    float average_rz = (1.0/6.0)*(v1z+(2.0*v2z)+(2.0*v3z)+v4z);
    
    v[0] = v3x + (h*average_vx);
    r[0] = r3x + (h*average_rx);
    v[1] = v3y + (h*average_vy);
    r[1] = r3y + (h*average_ry);
    v[2] = v3z + (h*average_vz);
    r[2] = r3z + (h*average_rz);
     
    
    for(m=0;m<n_points;m+=1000){
      if(m==j){
    
	  fprintf(data, "%f %f %f %f \n", t1, r[0], r[1], r[2]);

      }
    }
  }    

  return 0;
}

void campo_dipolo ( float* r, float* a, float* v, float energia_cinetica){
  float R = sqrt(pow(r[0], 2)+pow(r[1], 2) + pow(r[2], 2)); 
 /*valor inicial de la velocidad a partir de energia cinetica */ 
  float v_o1 = energia_cinetica/(masa*pow(c,2));
  float v_o2 = (1.0/((v_o1)+1.0));
  float v_o3 = 1-(pow(v_o2,2));
  float v_o4 = c*(sqrt(v_o3));

  float lambda = 1/(sqrt(1-(pow((v_o4/c), 2))));
  
  double b0, b1, b2;

  b0= (((-3*r[0]*r[2])*Bo*pow(Radio, 3))/pow(R, 5)); 
  b1= (((-3*r[1]*r[2])*Bo*pow(Radio, 3))/pow(R, 5));
  b2= ((((-2*pow(r[2],2)) + pow(r[0], 2) + pow(r[1], 2))*(Bo*pow(Radio, 3)))/pow(R, 5));
  float v0 = (carga/(lambda*masa))*v[0];
  float v1 = (carga/(lambda*masa))*v[1];
  float v2 = (carga/(lambda*masa))*v[2];
  a[0] = (b2*v1) - (v2*b1);
  a[1] = (v2*b0) - (b2*v0);
  a[2] = (b1*v0) - (v1*b0);
 
}
