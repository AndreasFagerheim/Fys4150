#include "functions.h"
#include <fstream>
functions::functions()
{

}
double** create_matrix(double**A,int n){
    double** a = A;
    for(int i = 0; i<n;i++){
        for(int j= 0;j<n;j++ ){
            a[i][j] = i * j;
        }
    }
    return a;
}

