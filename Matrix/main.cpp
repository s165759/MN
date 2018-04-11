#include <iostream>
#include "Matrix.h"


int main() {

    Matrix::DenseMatrix<int, 3, 3> A {{2,0,0}, {0,2,0}, {0,0,2}}, B {{5, 4, 3}, {2, 3, 6}, {3, 4, 4}};
    Matrix::DenseMatrix<int, 3, 4> D {{2,3,4,5}, {6,7,8,9}, {1,2,3,4}};

    auto C = A * D;

    std::cout << C;


    return 0;
}