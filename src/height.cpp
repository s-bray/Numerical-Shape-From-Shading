#include "../include/vector.hpp"
#include "../include/matrix.hpp"
#include "../include/globals.hpp"
#include <cmath>

// Definition of the height functional
double heightFunctional(const Vector<double>& h, const Matrix& x)
{
    int numRows = x.n / 2;
    int numCols = x.m;
    Matrix height = h.toMatrix(numRows, numCols);
    double value = 0;
    for (int i = 1; i < numRows; i++)
    {
        for (int j = 1; j < numCols; j++)
        {
            value += pow(height(i + 1, j) - height(i, j) - step * x(i, j), 2) + pow(height(i, j + 1) - height(i, j) - step * x(i + numRows, j), 2);
        }
    }
    return value;
}