#include<stdio.h>
#include<math.h> // for pow,log,cos,sin,sinh,cosh
#include<stdlib.h> // for atoi,atof
#include<string.h> // for strncmp
#define M_PI		3.14159265358979323846

// double fact(double a) // https://stackoverflow.com/a/2417853
// {
//   return tgamma(a+1.);
// }

double fact(double a)
{
  if (a==0)
    return 1;
  return a*fact(a-1);
}

double x, eps, new_x, sum, answer;
int n, i, variant, step=1;
void (*calc)(); // https://www.learn-c.org/en/Function_Pointers

int inputValue(int argc, char **argv);
void initVariant();
void printVariant();
int end(int retval);

void v10(){new_x = (i+1) * pow(x,i);}
void v9(){new_x = 2*(pow(x,2*i-1)/(2*i-1));}
void v8(){new_x = pow(x,2*i)/fact(2*i);}
void v7(){new_x = pow(x,2*i-1)/fact(2*i-1);}
void v6(){new_x = pow(-1,i+2)*pow(x,i);}
void v5(){new_x = pow(x,i);}
void v4(){new_x = pow(-1,i+1)*(pow(x,2*i-1)/(2*i-1));}
void v3(){new_x = (pow(-1,i+1)*pow(x,i))/i;}
void v2(){new_x = pow(-1,i+2)*(pow(x,2*i)/fact(2*i));}
void v1(){new_x = pow((-1),i+1) * (pow(x,2*i-1) / fact(2*i-1));}
void initVariant(){
  switch (variant){
    case 10:
      calc = &v10;
      answer = 1 / (pow((1-x),2));
      i = 0;
      break;
    case 9:
      calc = &v9;
      answer = log((1+x)/(1-x));
      i = 1;
      break;
    case 8:
      calc = &v8;
      answer = cosh(x);
      i = 0;
      break;
    case 7:
      calc = &v7;
      answer = sinh(x);
      i = 1;
      break;
    case 6:
      calc = &v6;
      answer = 1 / (1+x);
      i = 0;
      break;
    case 5:
      calc = &v5;
      answer = 1 / (1-x);
      i = 0;
      break;
    case 4:
      calc = &v4;
      answer = atan(x);
      i = 1;
      break;
    case 3:
      calc = &v3;
      answer = log(1+x);
      i = 1;
      break;
    case 2:
      calc = &v2;
      answer = cos(x);
      i = 0;
      break;
    case 1:
      calc = &v1;
      answer = sin(x);
      i = 1;
      break;
  }
}
int testCondition(){
  int fail = 0;
  switch (variant){
    case 10:
    case 6:
    case 5:
    case 9:
      x = fabs(x);
      if (x>=1) {
        fail = 1;
        printf("\nx (%.17g) cannot be >= 1",x);
      }
      break;
    case 4:
      x = fabs((x * M_PI) / 180);
      if (x>1){
        fail = 1;
        printf("\nx (%.17g) cannot be > 1",x);
      }
      break;
    case 3:
      if (x<=-1 || x>1){
        fail = 1;
        printf("\nx (%.17g) cannot be <= -1 or > 1",x);
      }
      break;
    case 1:
    case 2:
      x = (x * M_PI) / 180;
    case 8:
    case 7:
      x = fabs(x);
      break;
  }
  return fail;
}
int main(int argc, char **argv) {
  int cycleMethod = inputValue(argc,argv);
  if (cycleMethod >= 0){
    printf("\n------------------------------------------------\nvariant: %d\nx: %.17g",variant,x);
    if (cycleMethod) {
      printf("\nn: %d",n);
    } else {
      printf("\neps: %lf",eps);
    }
    printf("\ni: %d\n------------------------------------------------\n",i);
    printf("\nstep:\tsum:\t\tnew_x:\t\t");
    initVariant();
    switch (cycleMethod){
      case 0: // use eps as limiter
        do {
          printVariant();
          step++;
        } while (fabs(new_x) >= eps);
        return end(0);
      case 1: // use n as limiter
        for (step;step<=n;step++) {
          printVariant();
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
  int method, fail = 0;
  if (argc != 1) {
    if (strncmp(argv[1],"--test",6) == 0 && argc > 2 ) {
      switch (atoi(argv[2])) {
        case 0:
          variant = 10;
          x = 0.5;
          eps = 0.001;
          return 0;
        case 1:
          variant = 10;
          x = 0.5;
          n = 20;
          return 1;
      }
    } else if (argc == 5) {
      variant = atoi(argv[1]);
      x = atof(argv[2]);
      method = atoi(argv[3]);
      fail = testCondition();
      if (method){
        n = fabs(atoi(argv[4]));
      } else {
        eps = fabs(atof(argv[4]));
        if (eps > 1) {
          printf("\neps (%.17g) cannot be more than 1",eps);
          fail = 1;
        }
      }
      if (fail){
        return -2;
      } else {
        return method;
      }
    } 
  } 
  printf("ПИ 382007-в2 Ильюшенков Сергей Денисович\nЛабараторная 1 ULTIMATE");
  printf("\n\nusage: lab1ultimate variant x method [eps|n]\n");
  printf("\nvariant\t\tint\t1 to 10");
  printf("\nx\t\tdouble");
  printf("\nmethod\t\tint\t0 exit by eps; 1 exit by n");
  printf("\neps\t\tdouble");
  printf("\nn\t\tint");
  printf("\n\n--test number\t\t0 exit by eps; 1 exit by n");
  return -1;
}
void printVariant(){
  (calc)();
  sum += new_x;
  i++;
  printf("\n%d\t%.12f\t%.12f\t",step, sum, new_x);
}
int end(int retval) {
  printf("\nfinished.\nsum: %.17g\nanswer: %.17g",sum,answer);
  return retval;
}