#include "../include/matrix.hpp"
#include "../include/vector.hpp"
#include "../include/globals.hpp"
#include <cmath>

// Definition of the functional to be minimized

// Look for how the Lambertian shading model is implemented. This model relates the observed image intensities to the surface normals and the lighting conditions.
// Examine how the discrepancy between observed intensities and those predicted by the shading model is computed. This discrepancy implicitly captures information about the lighting conditions.
// Check for terms involving image(i, j), p(i, j), and q(i, j), where image(i, j) represents the observed intensity at pixel (i, j), and p(i, j) and q(i, j) are related to the surface normals.

double functional(const Vector<double> &x, const Matrix &image)
{
   Matrix p = x(0, image.n * image.m - 1).toMatrix(image.n, image.m);
   Matrix q = x(image.n * image.m, 2 * image.n * image.m - 1).toMatrix(image.n, image.m);
   double e1 = 0;
   double e2 = 0;
   double e3 = 0;

   for (int i = 1; i < image.n + 1; i++)
   {
       for (int j = 1; j < image.m + 1; j++)
       {
           e1 += pow(image(i, j) - (255 / sqrt(1 + pow(p(i, j), 2) + pow(q(i, j), 2))), 2);
           if (i != image.n && j != image.m)
           {
               e2 += pow(p(i, j + 1) - p(i, j) - q(i + 1, j) + q(i, j), 2);
               e3 += pow(p(i + 1, j) - p(i, j), 2) + pow(p(i, j + 1) - p(i, j), 2) + pow(q(i, j + 1) - q(i, j), 2) + pow(q(i + 1, j) - q(i, j), 2);
           }
       }
   }
   e1 *= step * step;
   e2 *= lambda_int;
   e3 *= lambda_csmo;
   return (e1 + e2 + e3);
}