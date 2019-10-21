#include <iostream>
#include <cmath>
#include "libbok.h"
using namespace std;


const int maxrecursions = 50;
const double tolerance = 1.0E-10;






int main()
{

    //Brute force monte calro integration taken from example in book by Morten Hjorth-Jensen Computational physics

    int i, n;
    long idum;
    double crude_mc,x,sum,fx,variance;

    crude_mc = sum = 0;
    idum = -1;
    cout << "read in the number of Monte-Carlo samples"<<endl;
    cin >> n;
    for(i = 1;i<=n;i++){
        x = ran0(&idum);
        fx = func(x);
        crude_mc +=fx;
        sum += fx*fx;
    }
    crude_mc = crude_mc/((double) n);
    sum = sum/((double) n);

    variance = sum-crude_mc*crude_mc;

    //final output

    cout<<"variance = "<<variance <<"integral = "<<crude_mc<<" Exact = "<<M_PI<<endl;


}
