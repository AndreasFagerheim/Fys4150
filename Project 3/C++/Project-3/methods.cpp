#include "methods.h"
#include <iostream>
#include <cmath>

using namespace std;



// function we want to integrate given in project 3
double int_function(double x1, double y1, double z1, double x2, double y2, double z2){
    double alpha = 2;
    double exp1 = -2*alpha*sqrt(x1*x1 + y1*y1 + z1*z1);
    double exp2 = -2*alpha*sqrt(x2*x2 + y2*y2 + z2*z2);
    double deno = sqrt(pow((x1-x2),2)+pow((y1-y2),2)+pow((z1-z2),2));
    if(deno < pow(10.,-6.)){ // cheking if denominator is zero
        return 0;
    }else{
        return exp(exp1+exp2)/deno;
    }
}


// computes the Legendre polynomal of degree N
double Legendre(int N, double x){
    double L = 1.0;
    double L_prev = 0.0;
    double L_next= L;

    for(int i = 0;i<N; i++){
        L_prev= L;
        L = L_next;
        L_next = (2*i +1)*x*L -i*L_prev;
        L_next /= (i+1.0);
    }
    return L_next;
}

double dLegendre(int N, double x){
    double dL = N*(x*Legendre(N,x)- Legendre(N-1,x))/(x*x-1);
    return dL;
}



void rootsLegendre(int N, double *roots){
    double const pi = 4*atan(1);
    double tolerance = 1e-8;
    int maxInter = 1000;
    int nRoots = (N+1)/2;
    for(int i = 0; i<nRoots;i++){
        double xk = cos(pi*(4*(i+1) -1.0)/(4*N+2.0));
        int nIter = 0;
        double err = 2*tolerance;
        while(err < tolerance && nIter < maxInter){
            double dxk = Legendre(N,xk)/dLegendre(N,xk);
            xk -= dxk;
            nIter += 1;
            err = fabs(dxk);
        }
        roots[i] = xk;
    }
    for(int i= nRoots;i<N;i++){
        roots[i] = -1.0*roots[i-nRoots];
    }
    if(N%2==1){
        roots[N]=0.0;
    }
}



void weightsLegendre(int N,double *weights, double *roots, double start, double end){
    double xm = (end-start)*0.5;
    double xp = (end+start)*0.5;
    for(int i = 0;i<N;i++){
        double xk = roots[i];
        double dL = dLegendre(N,xk);
        double w = 2.0*xm/((1-xk*xk)*dL*dL);
        weights[i] = w;
    }

    for (int i = 0;i<N;i++){
        roots[i] = xm*roots[i]+xp;
    }
}
