#include "../include/matrix.hpp"
#include "../include/vector.hpp"
#include "../include/image_factory.hpp"
#include "../include/lbfgs.hpp"
#include <cmath>
#include <ctime>
int main()
{


    Matrix Image = csvtoMatrix("images/vase2.csv");
    const clock_t startTime = clock(); //start timer

    // First optimization to recover the directional derivatives of the height
    cout << "L-BFGS of the functional"
         << "\n";
    Vector<double> x0(2 * Image.n * Image.m, 0.5);
    double gradTol1 = 100; // stopping condition on the gradient of the functional
    Vector<double> x = LBFGS(x0, functional, gradientFunctional, Image, gradTol1);
    Matrix heightDerivative = x.toMatrix(2 * Image.n, Image.m);

    // Second optimization to calculate the height at each pixel
    cout << "L-BFGS of the height"
         << "\n";
    Vector<double> h0(Image.n * Image.m, 0);
    double gradTol2 = pow(10, -3); // stopping condition on the gradient of the height
    Vector<double> y = LBFGS(h0, heightFunctional, gradientHeight, heightDerivative, gradTol2);
    Matrix render = y.toMatrix(Image.n, Image.m);

    // Save the mesh
    matrixToMesh("meshes/vase2.mesh", render);

    //display timer
    cout << "Execution time in seconds: " << float(clock() - startTime) / CLOCKS_PER_SEC << "\n";

    return 0;
}