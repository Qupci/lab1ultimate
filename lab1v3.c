#include<stdio.h> 
#include<math.h> 

int main() { 
  double eps; 
  double x; 
  double sum = 0; 
  double prevsum; 
  int n; 
  int i = 1; 
  printf("Enter sequentially x, n and eps:\n"); 
  
  while (1){ 
    printf("\nx: ");
    scanf("%lf",&x); 
    if (x <= 1 && x > (-1)) { 
      break; 
    }
    else { 
     printf("\nx (%lf) cannot be less or equal to -1 or more than 1",x); 
    }
  } 
    
  while (1){
    printf("\nn: ");
    scanf("%d",&n); 
    if (n > 0) {
      break;
    }
    else {
      printf("\nn (%d) cannot be less or equal to 0",n);
    }
  }
    
  while (1){
    printf("\neps: ");
    scanf("%lf",&eps);
    if (eps < 1) {
      break;
    }
    else {
      printf("\neps (%lf) cannot be more or equal to 1",eps);
    }
  }

  printf("\n\n---------------\nx: %lf\nn: %d\neps: %lf\n---------------\n",x,n,eps); 

  while (1) { 
    prevsum = sum;
    sum += pow((-1),i+1) * (pow(x,i) / i); 
    printf("\nstep %d\nsum = %lf", i, sum);
    ++i; 
    if ((sum - prevsum) <= eps) {
      printf("\nfinished. Return 0");
      return 0; 
    }
    if (n < i){
      printf("\nfinished. Return 1");
      return 1;
    }
  }
}