#include <iostream>
#include "matrix.h"

using std::cout;
using std::endl;

int main(){
    Matrix m1(3, 2);
    Matrix m2(2, 3);
    // set the values for m1
    m1[0][0] = 1;
    m1[0][1] = 4;
    m1[1][0] = 2;
    m1[1][1] = 5;
    m1[2][0] = 3;
    m1[2][1] = 6;
    // and m2
    m2[0][0] = 0;
    m2[0][1] = 1;
    m2[0][2] = 2;
    m2[1][0] = 4;
    m2[1][1] = 6;
    m2[1][2] = 8;
    // test multiplication
    Matrix m3 = m1.multiply(m2);
    cout << m3 << endl;
}   