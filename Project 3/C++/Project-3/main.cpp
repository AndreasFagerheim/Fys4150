#include <iostream>
#include <cmath>
#include "methods.h"
#include <fstream>
using namespace std;




int main()
{
    cout <<"Task a started"<<endl;
    double const pi = 4*atan(1);

    double exact_value = 5*pi*pi/(16.0*16.0);


    ofstream outfile;

   // outfile.open("/Users/andreas/Computational Physics/Fys4150/Project 3/C++/Project-3/GaussLegendreData.txt", ios::app);//std::ios_base::app
   // outfile << "Exact value of integration: "<< setprecision(4)<<exact_value<<endl<<endl;
   // outfile << "Integrating using Gauss-Legendre Quadrature with a order N polynomal."<<endl;
   // outfile << "------------------------------------------------------------"<<endl;
   // outfile << setw(5)<<"N"<<setw(20)<<"Numerical value"<<endl;
   // outfile.close();

    int order = 10;
    double a =-5,b= 5;

    double *roots = new double[order];
    double *weights = new double[order];


    rootsLegendre(order, roots);
    weightsLegendre(order,weights, roots, a , b);

    //------------------------------- Starting integration proseadure ------------------------------

    double integral = 0;    //sets integral to zero to start with
    // integrating over six dimensions so need six for loops
//    int maxOrder = 41;
//    for(int num = 1;num<2;num++){
//        cout <<"order: "<<num*10<<endl;
//        order = num*10;

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

    cout << "integration completed"<< endl;
    cout << "integral value "<<integral;
    outfile.open("/Users/andreas/Computational Physics/Fys4150/Project 3/C++/Project-3/GaussLegendreData.txt", ios::app);
    outfile<<setw(5)<<order<<setw(10)<<setprecision(5)<<integral<<endl;
    outfile.close();
    delete [] roots;
    delete [] weights;
//   }
    return 0;
}



