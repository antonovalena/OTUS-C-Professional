# include "SpareMatrix.h"
# include <iostream>


int main() {
    SpareMatrix<int, 0> matrix;

    for (int i = 0; i < 10; ++i) {
        matrix[i][i] = i;
        matrix[i][9-i] = 9 - i;
    }

    std::cout << "Matrix [1,1] to [8,8]\n";

    for (int i = 1; i < 9; ++i) {
        for (int j = 1; j < 9; ++j) {
            std::cout <<  matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Matrix size = " << matrix.size() << std::endl;

    std::cout << "Matrix positions:\n";
    for(auto& [cord, val]: matrix) {
        std::cout << "[" << cord.first << "," << cord.second << "] = " <<  val << std::endl;
    }

    return 0;

}