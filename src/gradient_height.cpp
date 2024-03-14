#include "../include/matrix.hpp"
#include "../include/vector.hpp"
#include "../include/globals.hpp"

//Définition du gradient de la hauteur
#include "../include/matrix.hpp"
#include "../include/vector.hpp"
#include "../include/globals.hpp"

// Definition of the height gradient
Vector<double> gradientHeight(const Vector<double>& h, const Matrix& x) {
    int numRows = x.n / 2;
    int numCols = x.m;
    Matrix height = h.toMatrix(numRows, numCols);
    Matrix gradient(numRows, numCols, 0);

    for (int i = 1; i < numRows + 1; i++) {
        for (int j = 1; j < numCols + 1; j++) {
            if (i != 1 && j != 1 && i != numRows && j != numCols) {
                gradient(i, j) = 4 * height(i, j) - height(i - 1, j) - step * x(i - 1, j) - height(i + 1, j) + step * x(i, j) - height(i, j - 1) - step * x(i + numRows, j - 1) - height(i, j + 1) + step * x(i + numRows, j);
            }
        }
    }

    return toVector(gradient * 2);
}
