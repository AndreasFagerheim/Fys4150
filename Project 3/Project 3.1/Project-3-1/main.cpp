#include <iostream>
#include "lib.h"
#include <cmath>
#include <fstream>
using namespace std;

//     Here we define various functions called by the main program

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
void gaussLegendreIntegral(int start, int stop, int order, double *values, int counter);
int main()
{
     int order;
     double a, b;
     a = -2;
     b = 2;
     //cout << "Read in the number of integration points" << endl;
     //cin >> n;
     //cout << "Read in integration limits" << endl;
     //cin >> a >> b;


     // calculating exact value of integral
     double const pi = 4*atan(1);
     double exact_value = 5*pi*pi/(16.0*16.0);
     ofstream outfile;

     outfile.open("/Users/andreas/Computational Physics/Fys4150/Project 3/Project 3.1/Project-3-1/GaussLegendreData.txt", ios::trunc);//std::ios_base::app
     outfile << "Exact value of integration: "<< setprecision(6)<<exact_value<<endl<<endl;
     outfile << "Integrating using Gauss-Legendre Quadrature with a order N polynomal."<<endl;
     outfile << "------------------------------------------------------------"<<endl;
     outfile << setw(5)<<"N"<<setw(20)<<"Numerical value"<<setw(20)<<"Relative error"<<endl<<endl;
     outfile.close();
    //----------------------- Start the ingral--------------------
     int samples  =6;
     double *integralValues = new double[samples];
     for(int i = 1;i<(samples+1);i++){
          order = i*5;
          gaussLegendreIntegral(a,b,order,integralValues, (i-1));
          outfile.open("/Users/andreas/Computational Physics/Fys4150/Project 3/Project 3.1/Project-3-1/GaussLegendreData.txt", ios::app);//std::ios_base::app
          outfile<<setw(5)<<order<<setw(15)<<setprecision(6)<<integralValues[i-1]<<setw(20)<<setprecision(4)<<fabs(integralValues[i-1] - exact_value)/exact_value<<endl;
          outfile.close();
     }
}  // end of main program











//-----------------------------------------------------------------------
//  this function defines the function to integrate

void gaussLegendreIntegral(int start, int stop, int order, double *integralValues, int counter){
    //   reserve space in memory for vectors containing the mesh points
    //   weights and function values for the use of the gauss-legendre
    //   method
    double *roots = new double [order];
    double *weights = new double [order];
    //   set up the mesh points and weights
         gaussLegendre(start, stop,roots,weights, order);
    //   evaluate the integral with the Gauss-Legendre method
    //   Note that we initialize the sum

    double integral = 0.;
    for(int i = 0;i<order;i++){
        for(int j = 0;j<order;j++){
            for(int k = 0;k<order;k++){
                for(int l = 0;l<order;l++){
                    for(int m = 0;m<order;m++){
                        for(int n = 0;n<order;n++){
                            integral += weights[i]*weights[j]*weights[k]*weights[l]*weights[m]*weights[n]*int_function(roots[i],roots[j],roots[k],roots[l],roots[m],roots[n]);
                        }
                    }
                }
            }
        }
    }
//    final output

     integralValues[counter] = integral;
     cout << "Gaussian quad = " << integral << endl;
     delete [] roots;
     delete [] weights;
}

void gaussLaguerreIntegral(int n){
    double pi = 4*atan(1);
    double exact_value = 5*pi*pi/(16*16.);
    double theta_start = 0, theta_stop = pi;
    double phi_start = 0, phi_stop = 2*pi;
    double alpha = 2;

    // distanses integrated with gauss-laguerre and thefore needs n+1 points
    // because of called functions from lib.h
    double *r = new double [n+1];
    double *weightsR = new double [n+1];

    //angles integrated with legendre functions from earlier
    double *theta = new double[n];
    double *phi = new double[n];
    double *weightsTheta = new double[n];
    double *weightsPhi = new double[n];

    //distance
    gauss_laguerre(r,weightsR,n,alpha);
    //angles
    gaussLegendre(theta_start,theta_stop,theta,weightsTheta,n);
    gaussLegendre(phi_start,phi_stop,phi,weightsPhi,n);



}
