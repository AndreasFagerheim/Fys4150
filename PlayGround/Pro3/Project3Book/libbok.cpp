#include "libbok.h"
#include <iostream>
#include <cmath>

using namespace std;
/*
double ran0(long *idum)
    ** is an "Minimal" random number generator of Park and Miller
    ** (see Numerical recipe page 279). Set or reset the input value
    ** idum to any integer value (except the unlikely value MASK)
    ** to initialize the sequence; idum must not be altered between
    ** calls for sucessive deviates in a sequence.
    ** The function returns a uniform deviate between 0.0 and 1.0.
    */

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define MASK 123459876

double ran0(long *idum)
{
   long     k;
   double   ans;

   *idum ^= MASK;
   k = (*idum)/IQ;
   *idum = IA*(*idum - k*IQ) - IR*k;
   if(*idum < 0) *idum += IM;
   ans=AM*(*idum);
   *idum ^= MASK;
   return ans;
}
#undef IA
#undef IM
#undef AM
#undef IQ
#undef IR
#undef MASK

//integratino by trapezoidrule
double trapezoidal_rule(double a, double b, int n, double (*func)(double)){
    double trapez_sum;
    double fa, fb, x, step;
    int j;
    step = (b-a)/((double) n);
    fa = (*func)(a)/2.0;
    fb = (*func)(b)/2.0;
    trapez_sum = 0;
    for(j = 1;j <= n-1;j++){
        x = j*step + a;
        trapez_sum += (*func)(x);
    }
    trapez_sum = (trapez_sum+fa+fb)*step;
    return trapez_sum;
}

void adaptive_integration(double a, double b, double *integral, int n, int steps, double (*func)(double), int maxRecursions, double tolerance){
    if(steps > maxRecursions){
        cout <<"too many recursive steps, the function varies to much" << endl;
    }

    double c = (a+b)*0.5;
    double I0 = trapezoidal_rule(a,b,n,func);

    double IL = trapezoidal_rule(a,c,n,func);
    double IR = trapezoidal_rule(c,b,n,func);
    if ( fabs(IL+IR -I0)<tolerance){
        *integral = I0;
    }
    else{
        adaptive_integration(a,c,integral,n, ++steps, func, maxRecursions,tolerance);
        adaptive_integration(c,b,integral,n, ++steps, func, maxRecursions,tolerance);
    }
}



double func(double x){
    double value = 4/(1.0+x*x);
    return value;
}

