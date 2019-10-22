#include <iostream>
#include <cmath>
#include "libbok.h"
using namespace std;


const int maxrecursions = 50;
const double tolerance = 1.0E-10;




double int_MC_brute(double *x){
    double alpha = 2.0;
    double cons = -2*alpha;
    double exp1 = (cons*sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]));
    double exp2 = (cons*sqrt(x[3]*x[3]+x[4]*x[4]+x[5]*x[5]));
    double denom = sqrt(pow(x[0]-x[3],2) +pow(x[1]-x[4],2)+pow(x[2]-x[5],2));

    if(denom < pow(10.,-6.)){ // cheking if denominator is zero
        return 0;
    }else{
        return exp(exp1+exp2)/denom;
    }
}

int main()
{

        int N = 100000;
        int dim = 6;
        double x[dim];
        double a = -5; // lower integration limit
        double b = 5;  // upper integration limit

        long idum = -1;
        double crude_mc = 0;
        double sigma = 0;

        double fx;
        for (int i=0; i < N; i++) {
            for (int j = 0; j < dim; j++) {
                x[j] = a + (b-a)*ran0(&idum);
            }
            fx = int_MC_brute(x);
            crude_mc += fx;
            sigma += fx*fx;
        }

        double jacobidet = pow((b-a), dim);
        crude_mc /= N;
        sigma /= N;
        double variance = sigma - crude_mc*crude_mc;
        double const pi = 3.14159265359;
        double exact = 5*pi*pi/(16.0*16.0);
        crude_mc *= jacobidet;
        sigma *= jacobidet;
        cout << endl << "N          = " << N << endl;
        cout << endl << "Numeric    = " << crude_mc << endl;
        cout <<         "Exact      = " << exact << endl;
        cout <<         "Variance   = " << variance << endl;

        return 0;
}

