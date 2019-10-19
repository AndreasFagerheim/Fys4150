#include <iostream>
#include <cmath>
using namespace std;


const int maxrecursions = 50;
const double tolerance = 1.0E-10;


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

void adaptive_integration(double a, double b, double *integral, int n, int steps, double (*func)(double)){
    if(steps > maxrecursions){
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
        adaptive_integration(a,c,integral,n, ++steps, func);
        adaptive_integration(c,b,integral,n, ++steps, func);
    }
}

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
