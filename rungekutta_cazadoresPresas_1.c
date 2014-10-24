#include<stdio.h>
#include<math.h>
#include<stdlib.b>

void func_prime1(float x, float y);
void func_prime2(float x, float y);
int main (int argc, char **argv){
  int i;
  int j;
  
  float h = 0.01;
  float min_t = 0.0;
  float max_t = 1.0;
  float n_points = ((max_t - min_t) / h);

  float x*;
  float y*;
  float t*;

  float Xo = ;
  float Yo = ;
  float To = min_t;

  x = malloc(n_points*sizeof(float));
  y = malloc(n_points*sizeof(float));
  t = malloc(n_points*sizeof(float));

  for (i=0;i<n_points;i++){
    x[i]=0.0;
    y[i]=0.0;
    t{i]=0.0;
  }
  for (i=1;i<n_points;i++){
  
    k11 = func_prime1(x[i-1],y[i-1]);
    k12 = func_prime1(x[i-1],y[i-1]);
    
    #first step
    t1 = t[i-1] + (h/2.0);
    y1 = y[i-1] + (h/2.0) * k1
    x1 = x[i-1] + (h/2.0) * k1?
    k2 = func_prime(x1, y1)
    
    #second step
    x2 = x[i-1] + (h/2.0)
    y2 = y[i-1] + (h/2.0) * k2
    k3 = func_prime(x2, y2)
        
    #third step
    x3 = x[i-1] + h
    y3 = y[i-1] + h * k3
    k4 = func_prime(x3, y3)
    
    #fourth step
    average_k = (1.0/6.0)*(k1 + 2.0*k2 + 2.0*k3 + k4)
    
    x[i] = x[i-1] + h
    y[i] = y[i-1] + h * average_k
}
  return 0;
}

void func_prime1(x_,y_){
  return (20*x_) - (x_*y_) ;
}
void func_prime2(x_,y_){
  return (-30*y_) - (x*y_);
}
