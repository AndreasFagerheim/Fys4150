#ifndef METHODS_H
#define METHODS_H


class methods
{
public:
    methods();
};
double int_function(double x1, double y1, double z1, double x2, double y2, double z2);
double Legendre(int N, double x);
double dLegendre(int N, double x);
void rootsLegendre(int N, double *roots);
void weightsLegendre(int N, double *weights, double *roots, double start, double end);

#endif // METHODS_H
