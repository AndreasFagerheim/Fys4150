#include "gaussianquadrature.h"
#include <cmath>
#include <iostream>
using namespace std;


double Legendre(int order, double x)
{
    double L_p  = 1.0;  // L_{j} (L_previous)
    double L_pp = 0.0;	// L_{j-1} (L_previous,prevoius)
    double L = L_p; 	// current L (value of Legendre polynomial)
    for (int j=0; j<order; j++){
        L_pp = L_p;
        L_p = L;
        // calculate new L
        L = (2*j + 1)*x*L_p - j*L_pp;
        L /= (j+1.0);
    }
    return L;
}

double dLegendre(int order, double x)
{
    double dL = order*(x*Legendre(order, x) - Legendre(order-1, x))/(x*x - 1);
    return dL;
}



void rootsLegendre(int order, double *roots)
{
    // calculating the roots of the legendre polynomial using Newtons method
    double const pi = 4*atan(1);
    double tol = 1e-8;
    int maxnIter = 1000;
    int nRoots = (order+1)/2;
    for (int i=0; i<nRoots; i++) {
        // initial guess for zero point
        double xk = cos(pi*(4*(i+1) - 1.0)/(4*order + 2.0));
        int nIter = 0;
        double err = 2*tol; // just make the current error larger than the tolerance
        while (err > tol && nIter < maxnIter) {
            double dxk = Legendre(order, xk)/dLegendre(order, xk);
            xk -= dxk;
            nIter += 1;
            err = fabs(dxk);
        }
        roots[i] = xk;
    }
    for (int i=nRoots; i < order; i++) {
        roots[i] = -1.0*roots[i-nRoots];
    }
    if (order%2==1) {
        roots[order] = 0.0;
    }
}


void weightsLegendre(int order, double *weights, double *roots, double a, double b)
{
    double xm = (b-a)/2;
    double xp = (b+a)/2;
    for (int i=0; i < order; i++) {
        double xk = roots[i];
        double dL = dLegendre(order, xk);
        double w = 2.0*xm/((1-xk*xk)*dL*dL);
        weights[i] = w;
    }
    /* Calculating the mesh points and change the limits from x \in [-1,1] to t \in [a, b].
     * We have that
     *                          t = (b-a)/2*x + (b+a)/2
     * The weights are conserved.
     */

    for (int i=0; i < order; i++) {
        roots[i] = xm*roots[i]+xp;
    }

}



void gauss_laguerre(double *x, double *w, int n, double alf)
{
    int i,its,j;
    double ai;
    double p1,p2,p3,pp,z,z1;
    int MAXIT = 10;
    double EPS = 3.0e-14;

    for (i=1; i<=n; i++) {
        if (i == 1) {
            z=(1.0+alf)*(3.0+0.92*alf)/(1.0+2.4*n+1.8*alf);
        } else if (i == 2) {
            z += (15.0+6.25*alf)/(1.0+0.9*alf+2.5*n);
        } else {
            ai=i-2;
            z += ((1.0+2.55*ai)/(1.9*ai)+1.26*ai*alf/
                (1.0+3.5*ai))*(z-x[i-2])/(1.0+0.3*alf);
        }
        for (its=1;its<=MAXIT;its++) {
            p1=1.0;
            p2=0.0;
            for (j=1;j<=n;j++) {
                p3=p2;
                p2=p1;
                p1=((2*j-1+alf-z)*p2-(j-1+alf)*p3)/j;
            }
            pp=(n*p1-(n+alf)*p2)/z;
            z1=z;
            z=z1-p1/pp;
            if (fabs(z-z1) <= EPS) break;
        }
        if (its > MAXIT) cout << "too many iterations in gaulag" << endl;
        x[i]=z;
        w[i] = -exp(gammln(alf+n)-gammln((double)n))/(pp*n*p2);
    }
}
// end function gaulag

double gammln( double xx)
{
    double x,y,tmp,ser;
    static double cof[6]={76.18009172947146,-86.50532032941677,
        24.01409824083091,-1.231739572450155,
        0.1208650973866179e-2,-0.5395239384953e-5};
    int j;

    y=x=xx;
    tmp=x+5.5;
    tmp -= (x+0.5)*log(tmp);
    ser=1.000000000190015;
    for (j=0;j<=5;j++) ser += cof[j]/++y;
    return -tmp+log(2.5066282746310005*ser/x);
}
