#ifndef LIBBOK_H
#define LIBBOK_H

double trapezoidal_rule(double a, double b, int n, double (*func)(double));
void adaptive_integration(double a, double b, double *integral, int n, int steps, double (*func)(double), int maxRecursions, double tolerance);
void adaptive_integration(double a, double b, double *integral, int n, int steps, double (*func)(double), int maxRecursions, double tolerance);
double func(double x);
double ran0(long *idum);
#endif // LIBBOK_H
