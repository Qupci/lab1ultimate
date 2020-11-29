#include<stdio.h>
#include<math.h> // for pow
#include<stdlib.h> // for atoi,atof
#include<string.h> // for strncmp

double x, eps, new_x, sum, answer;
int n, i=0;

int inputValue(int argc, char **argv);

void printVariant10(){
  new_x = (i+1) * (pow(x,i));
  sum += new_x;
  printf("\n%lf\t%lf\t%d\t", sum, new_x, i+1);
}

int main(int argc, char **argv) {
  int cycleMethod = inputValue(argc,argv);
  if (cycleMethod >= 0){
    printf("\n\n------------------------------------------------\nx: %lf",x);
    if (cycleMethod) {
      printf("\nn: %d",n);
    } else {
      printf("\neps: %lf",eps);
    }
    printf("\ni: %d\n------------------------------------------------\n",x,n,eps,i);
    printf("\nsum:\t\tnew_x:\t\tstep:\t\t");
    n--; // last step == n
    answer = 1 / (pow((1-x),2)); // answer case for Variant 10
    switch (cycleMethod){
      case 0: // use eps as limiter
        do {
          printVariant10();
          i++;
        } while (new_x >= eps);
        return end(0);
      case 1: // use n as limiter
        for (i;i<=n;i++) {
          printVariant10();
        }
        return end(0);
      default:
        return cycleMethod;
    }
  } else {
    switch (cycleMethod){
      case -2:
        printf("\nError: 4XXMs3FO50M");
        return -2;
      default:
        return cycleMethod;
    }
  }
}

int inputValue(int argc, char **argv){
  int method;
  if (argc != 1) {
    if (strncmp(argv[1],"--test",6) == 0 && argc > 2 ) {
      switch (atoi(argv[2])) {
        case 0:
          x = 0.5;
          eps = 0.001;
          return 0;
        case 1:
          x = 0.5;
          n = 20;
          return 1;
      }
    } else if (argc == 4) {
      x = fabs(atof(argv[1]));
      method = atoi(argv[2]);
      if (x > 1) {
        printf("\nx (%lf) cannot be more than 1",x);
        return -2;
      }
      if (method){
        n = fabs(atoi(argv[3]));
        return 1;
      } else {
        eps = fabs(atof(argv[3]));
        if (eps > 1) {
          printf("\neps (%lf) cannot be more than 1",eps);
          return -2;
        } else {
          return 0; 
        }
      }
    } 
  } 
  printf("ПИ 382007-в2 Ильюшенков Сергей Денисович\nЛабараторная 1, вариант 10 (1 / (1-x)^2)");
  printf("\n\nusage: lab1v10 x method [eps|n]");
  printf("\n\nx\t\tfloat");
  printf("\nmethod\t\tint\t0 exit by eps; 1 exit by n");
  printf("\neps\t\tfloat");
  printf("\nn\t\tint");
  printf("\n\n--test number\t\t0 exit by eps; 1 exit by n");
  return -1;
} 

int end(retval) {
  printf("\nfinished.\nsum: %lf answer: %lf",sum,answer);
  return retval;
}