#include<stdio.h>
#include<math.h> // for pow
#include<stdlib.h> // for atoi,atof
#include<string.h> // for strncmp

double x, eps, new_x, sum;
int n, i=0;

int end(double sum, int retval);
int inputValue(int argc, char **argv);
void initPrint();

void printVariant10(){
  new_x = pow(x,i);
  sum += new_x;
  printf("\n%lf     %lf     %d          ", sum, new_x, i+1);
}

int main(int argc, char **argv) {
  switch (inputValue(argc,argv)){
    case 0: // use both n and eps limiters
      while (1) {
        printVariant10();
        i++;
        if (new_x <= eps)
          return end(sum, 0);
        if (n <= i)
          return end(sum, 1);
      }
    case 3: // use eps as limiter
      do {
        printVariant10();
        i++;
      } while (new_x >= eps);
      return end(sum, 0);
    case 4: // use n as limiter
      for (i;i<=n;i++) {
        printVariant10();
      }
      return end(sum, 1);
  }
}

int inputValue(int argc, char **argv){
  int fail = 0;
  if (argc != 1) {
    if (strncmp(argv[1],"--test",6) == 0 && argc > 2 ) {
      switch (atoi(argv[2])) {
        case 0:
          x = 0.9;
          n = 100;
          eps = 0.001;
          return 0;
        case 1:
          x = 0.9;
          n = 20;
          eps = 0.001;
          return 0;
      }
    } else if (argc == 4) {
      x = fabs(atof(argv[1]));
      n = fabs(atoi(argv[2]));
      eps = fabs(atof(argv[3]));
      if (x > 1) {
        printf("\nx (%lf) cannot be more than 1",x);
        fail = 1;
        }
      if (eps > 1) {
        printf("\neps (%lf) cannot be more than 1",eps);
        fail = 1;
        }
      if (fail) {
        return 1;
      } else {
        if (n == 0 && eps == 0) {
          printf("\nAt least one limiter (n or eps) should be not zero.");
          return 1;
        } else if (n == 0) {
          initPrint();
          return 3;
        } else if (eps == 0) {
          initPrint();
          return 4;
        }
        initPrint();
        return 0;
      }
    } 
  } 
  printf("ПИ 382007-в2 Ильюшенков Сергей Денисович\nЛабараторная 1, вариант 10\n\nusage: lab1v10 x n eps");
  printf("\n\n--test number\t\t0 exit by eps; 1 exit by n");
  return 2;
} 

void initPrint(){
  printf("\n\n------------------------------------------------\nx: %lf\nn: %d\neps: %lf\ni: %d\n------------------------------------------------\n",x,n,eps,i);
  printf("\nsum:         x^i:         step:         ");
  n--; // for halt variant printing at user defined n
}

int end(double sum, int retval) {
  printf("\nfinished.\nsum: %lf answer: %lf\nexit code: %d",sum,1 / (1-x),retval);
  return retval;
}