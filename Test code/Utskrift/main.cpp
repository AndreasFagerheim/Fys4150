
#include "functions.h"
using namespace std;



#include <iostream>
#include <armadillo>
#include <fstream>

using namespace arma;
using namespace std;

ofstream file;

int main(int argc, char** argv)
 {
    ofstream file, outfile;
    file.open("mytext.txt");
    outfile.open("/Users/andreas/Documents/Fys4150/Filer/Utskrift/mytext.txt", ios_base::app);
    outfile <<"testing";
    outfile.close();




cout << "Armadillo version: " << arma_version::as_string() << endl;
mat A;
// Hard coding of the matrix
// endr indicates "end of row"
//A << 0.165300 << 0.454037 << 0.995795 << 0.124098 << 0.047084 << endr
//<< 0.688782 << 0.036549 << 0.552848 << 0.937664 << 0.866401 << endr
 // << 0.348740 << 0.479388 << 0.506228 << 0.145673 << 0.491547 << endr
 //<< 0.148678 << 0.682258 << 0.571154 << 0.874724 << 0.444632 << endr
//  << 0.245726 << 0.595218 << 0.409327 << 0.367827 << 0.385736 << endr;
A = randu<mat>(6,6);
mat d = diagmat(A);
d.print("d=");
// .n_rows = number of rows
// .n_cols = number of columns

cout << "A.n_rows = " << A.n_rows << endl;
cout << "A.n_cols = " << A.n_cols << endl;
// Print the matrix A
A.print("A =");
outfile.open("/Users/andreas/Documents/Fys4150/Filer/Utskrift/mytext.txt", ios_base::trunc);
outfile << A;
outfile.close();
// Computation of the determinant
//cout << "det(A) = " << det(A) << endl;
// inverse
cout << "inv(A) = " << endl << inv(A) << endl;
// save to disk
A.save("MatrixA.txt", raw_ascii);
// Define a new matrix B which reads A from file
mat B;
B.load("/Users/andreas/Documents/Fys4150/Filer/Utskrift/mytext.txt");
B.print("The matrix B:");
B += 5.0*A;
B.print("The matrix B:");
// generate the identity matrix
mat C = eye<mat>(4,4);
// transpose of B
cout << "trans(B) =" << endl;
// maximum from each column (traverse along rows)
cout << "max(B) =" << endl;
cout << max(B) << endl;
// sum of all elements B
cout << "sum(sum(B)) = " << sum(sum(B)) << endl;
cout << "accu(B) = " << accu(B) << endl;
// trace = sum along diagonal
cout << "trace(B) = " << trace(B) << endl;
// random matrix -- values are uniformly distributed in the [0,1] interval

return 0; }
