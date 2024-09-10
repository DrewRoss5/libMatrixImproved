#include <iostream>
#include "matrix.h"

using std::cout;
using std::endl;

int main(){
    Matrix m1(2, 2);
    Matrix m2(2, 2);
    // populate m1
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;
    // and m2
    m2[0][0] = 2;
    m2[0][1] = 4;
    m2[1][0] = 6;
    m2[1][1] = 8;
    // test equality operators
    if (m1 != m2)
        cout << "Test 1 passed" << endl;
    if (m1 == m1)
        cout << "Test 2 passed" << endl;

    


}