#include <iostream>
#include "gaussianquadrature.h"
#include <cmath>
#include <time.h>

using namespace std;

// function to integrate
double integrand(double x1, double y1, double z1, double x2, double y2, double z2);



int main()
{
    clock_t start, finish;
    start = clock();

    int order = 25;
    double a = -5;
    double b = 5;
    double *roots = new double[order];
    double *weights = new double[order];

    rootsLegendre(order, roots);
    weightsLegendre(order, weights, roots, a, b);


    // integrate:
    double integral = 0;
    for (int i=0; i < order; i++) {
        for (int j=0; j < order; j++) {
            for (int k=0; k < order; k++) {
                for (int l=0; l < order; l++) {
                    for (int m=0; m < order; m++) {
                        for (int n=0; n < order; n++) {
                            integral += weights[i]*weights[j]*weights[k]*weights[l]*weights[m]*weights[n]*
                                    integrand(roots[i], roots[j], roots[k], roots[l], roots[m], roots[n]);
                        }
                    }
                }
            }
        }
    }

    finish = clock();
    cout << endl << "Compution time: " << ((finish - start*1.0)/CLOCKS_PER_SEC) << endl;

    double const pi = 4*atan(1);
    double exact = 5*pi*pi/(16.0*16.0);
    cout << endl << "N          = " << order << endl << endl;
    cout << "Numeric    = " << integral << endl;
    cout << "Exact      = " << exact << endl;
    //cout << "rel Error  = " << fabs(integral - exact)/exact << endl;

    delete[] roots;
    delete[] weights;
    return 0;
}

// function to integrate
double integrand(double x1, double y1, double z1, double x2, double y2, double z2) {
    double alpha = 2;
    double exp1 = -2*alpha*sqrt(x1*x1 + y1*y1 + z1*z1);
    double exp2 = -2*alpha*sqrt(x2*x2 + y2*y2 + z2*z2);
    double deno = sqrt(pow((x1-x2),2)+pow((y1-y2),2)+pow((z1-z2),2));
    if(deno < pow(10.,-6.)) {
        return 0;
    }
    else {
        return exp(exp1+exp2)/deno;
    }
}
