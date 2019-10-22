#ifndef LIB_H
#define LIB_H
#include <fstream>

using namespace std;

void gaussLegendre(double x1, double x2, double x[], double w[], int n);
double gammln( double xx);
void gauss_laguerre(double *x, double *w, int n, double alf);
void  MCBrute(int dim, double a, double b, int samples, ofstream &file);
double ran0(long *idum);
double integrandSPherical2(double r1, double theta1, double phi1,double r2, double theta2, double phi2);
double integrandSPherical(double r1, double theta1, double phi1,double r2, double theta2, double phi2);
#endif // LIB_H
