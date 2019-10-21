double Legendre(int order, double x);

double dLegendre(int order, double x);

void rootsLegendre(int order, double *roots);

void weightsLegendre(int order, double *weights, double *roots, double a, double b);

void gauss_laguerre(double *x, double *w, int n, double alf);

double gammln( double xx);

void gauleg(double x1, double x2, double x[], double w[], int n);
