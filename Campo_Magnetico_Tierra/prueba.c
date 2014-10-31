#include<stdio.h>
#include<math.h>
#include<stdlib.h>

void campo_dipolo (double* r, double* a, double* v, double energia_cinetica);

#define dh 1E-4
#define pi 3.141592
#define c 299759458
#define masa 1.67E-27
#define Radio 6378100
#define Bo 3E-5
#define carga 1.16E-19
int main (int argc, char **argv){

  int i;
  int j;
  int m;
  double  min_t = 0.0;
  double  max_t = 100.0;
  double n_points = ((max_t - min_t) / dh);

  double* a1;
  double* a2;
  double* a3;
  double* a4;
  double* v1;
  double* v2;
  double* v3;
  double* v4;
  double* v_o; 
  double* r_o;
  double* r1;
  double* r2;
  double* r3;
  double* r4;
  double* t1;
  FILE* data;
  double pitch;
  double energia_cinetica1; 
  double To = min_t;

 if(argc!=3){
    printf("debe introducir los parámetros de energía cinética y el ángulo pitch");
    exit(1);
  }
 r1 = malloc(3*sizeof(double));
 r2 = malloc(3*sizeof(double));
 r3 = malloc(3*sizeof(double));
 r4 = malloc(3*sizeof(double));
 a1 = malloc(3*sizeof(double));
 a2 = malloc(3*sizeof(double));
 a3 = malloc(3*sizeof(double));
 a4 = malloc(3*sizeof(double));
 v1 = malloc(3*sizeof(double));
 v2 = malloc(3*sizeof(double));
 v3 = malloc(3*sizeof(double));
 v4 = malloc(3*sizeof(double));
 v_o= malloc(3*sizeof(double));
 r_o = malloc(3*sizeof(double));
 t1 = malloc(n_points*sizeof(double));
 
 energia_cinetica1 = atof(argv[1]); 
 pitch = atof(argv[2]);
 double  pitch_rad = (pitch*pi)/180.0;
 double energia_cinetica = (energia_cinetica1*1.60217733E-13); // energia cinetica en joules 


 double v_o1 = energia_cinetica/(masa*pow(c,2));
 double v_o2 = (1.0/((v_o1)+1.0));
 double v_o3 = 1-(pow(v_o2,2));
 double v_o4 = c*(sqrt(v_o3));
 double vo = v_o4;

 v_o[0] = 0.0;
 v_o[1] = vo*sin(pitch_rad);
 v_o[2] = vo*cos(pitch_rad);

 r_o[0]=2*Radio;
 r_o[1]=0.0;
 r_o[2]=0.0;

 char n[150];
 sprintf(n,"trayectoria_%.0f_%.0f.dat",energia_cinetica1,pitch);
 data = fopen(n, "w");


for(j=1; j<n_points;j++){
    t1[j] = j* dh;
  
    campo_dipolo (r_o, a1, v_o, energia_cinetica);
    
    v1[0] = v_o[0] + ((dh/2.0) * a1[0]);
    v1[1] = v_o[1] + ((dh/2.0) * a1[1]);
    v1[2] = v_o[2] + ((dh/2.0) * a1[2]);
    r1[0] = r_o[0] + ((dh/2.0) * v1[0]);
    r1[1] = r_o[1] + ((dh/2.0) * v1[1]);
    r1[2] = r_o[2] + ((dh/2.0) * v1[2]);
    
   
   campo_dipolo (r1, a2, v1, energia_cinetica);
    
    v2[0] =v_o[0] + ((dh/2.0) * a2[0]);
    v2[1] =v_o[1] + ((dh/2.0) * a2[1]);
    v2[2] =v_o[2] + ((dh/2.0) * a2[2]);      
    r2[0] =r_o[0] + ((dh/2.0) * v2[0]);
    r2[1] =r_o[1] + ((dh/2.0) * v2[1]);
    r2[2] =r_o[2] + ((dh/2.0) * v2[2]);

    
    campo_dipolo (r2, a3, v2, energia_cinetica);

    
    v3[0] = v_o[0] + ((dh/2.0) * a3[0]);
    v3[1] = v_o[1] + ((dh/2.0) * a3[1]);
    v3[2] = v_o[2] + ((dh/2.0) * a3[2]);      
    r3[0] = r_o[0] + ((dh/2.0) * v3[0]);
    r3[1] = r_o[1] + ((dh/2.0) * v3[1]);
    r3[2] = r_o[2] + ((dh/2.0) * v3[2]);
    
    campo_dipolo (r3, a4, v3, energia_cinetica);
     
    float average_vx = (1.0/6.0)*(a1[0]+(2.0*a2[0])+(2.0*a3[0])+a4[0]);
    float average_vy = (1.0/6.0)*(a1[1]+(2.0*a2[1])+(2.0*a3[1])+a4[1]);
    float average_vz = (1.0/6.0)*(a1[2]+(2.0*a2[2])+(2.0*a3[2])+a4[2]);


    v4[0] = v_o[0] + (dh*average_vx);
   
    v4[1] = v_o[1] + (dh*average_vy);
    
    v4[2] = v_o[2] + (dh*average_vz);
    
    
    float average_rx = (1.0/6.0)*(v1[0]+(2.0*v2[0])+(2.0*v3[0])+v4[0]);
    float average_ry = (1.0/6.0)*(v1[1]+(2.0*v2[1])+(2.0*v3[0])+v4[1]);
    float average_rz = (1.0/6.0)*(v1[2]+(2.0*v2[2])+(2.0*v3[0])+v4[2]);
    
    r4[0] = r_o[0] + (dh*average_rx);
    r4[1] = r_o[1] + (dh*average_ry);
    r4[2] = r_o[2] + (dh*average_rz);

    v_o[0] = v4[0];
    v_o[1] = v4[1];
    v_o[2] = v4[2];
    r_o[0] = r4[0];
    r_o[1] = r4[1];
    r_o[2] = r4[2];
    
    for(m=0;m<n_points;m+=1000){
      if(m==j){
    
	fprintf(data, "%f %f %f %f \n", t1[j], r_o[0], r_o[1], r_o[2]);
	
      }
    }
  }
 return 0;

}


void campo_dipolo (double* r, double* a, double* v, double energia_cinetica){
  double x = r[0];
  double y = r[1];
  double z = r[2]; 
 double R = sqrt(pow(x, 2)+pow(y, 2) + pow(z, 2)); 

 /*valor inicial de la velocidad a partir de energia cinetica */ 
  double v_o1 = energia_cinetica/(masa*pow(c,2));
  double v_o2 = (1.0/((v_o1)+1.0));
  double v_o3 = 1-(pow(v_o2,2));
  double v_o4 = c*(sqrt(v_o3));

  double lambda = 1/(sqrt(1-(pow((v_o4/c), 2))));
  
  double b0, b1, b2;
 
  b0 = -(Bo*pow(Radio,3)/pow(R,5))*(3*x*y); 
  b1 = -(Bo*pow(Radio,3)/pow(R,5))*(3*y*z);
  b2 = -(Bo*pow(Radio,3)/pow(R,5))*(2*pow(z,2)-pow(x,2)-pow(y,2));
  
  double v0 = (carga/(lambda*masa))*v[0];
  double v1 = (carga/(lambda*masa))*v[1];
  double v2 = (carga/(lambda*masa))*v[2];
  a[0] = (b2*v1) - (v2*b1);
  a[1] = (v2*b0) - (b2*v0);
  a[2] = (b1*v0) - (v1*b0);
  
}
