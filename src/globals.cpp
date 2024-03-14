#include "../include/globals.hpp"
#include <cmath>
const int lambda_int = 10; // Importance factor for the integrability of the solution
const int lambda_csmo = 10; // Importance factor for the smoothness of the solution
const double step = 1; // Discretization step (square root of the importance factor for the deviation of the input image from the projection of the solution)