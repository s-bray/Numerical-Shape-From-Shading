#include "../include/lbfgs.hpp"
#include "../include/matrix.hpp"
#include "../include/vector.hpp"
#include <cmath>
using namespace std;

//Implementation of the L-BFGS gradient descent
Vector<double> LBFGS(Vector<double> &x, double (*function)(const Vector<double> &, const Matrix &), Vector<double> (*gradientFunction)(const Vector<double> &, const Matrix &), const Matrix &M, double eps)
{
    DiagonalMatrix Id(x.dim, 1);
    double gamma = 1;  //Scaling factor
    int m = 5;         //Number of iterations stored to calculate Hk
    int k = 0;         //Iteration
    int wolfemax = 20; //maximum number of iterations for Wolfe line search
    Vector<Vector<double>> s(m);
    Vector<Vector<double>> y(m);
    Vector<double> a(m, 0);
    double b;
    double c1 = pow(10, -4);
    double c2 = 0.9999999;
    while (true)
    {
        cout << "Iteration: " << k << "\n";
        Vector<double> gradient = gradientFunction(x, M);
        Vector<double> q = gradient;
        cout << "Gradient norm " << gradient.norm() << "\n";
        if (gradient.norm() < eps || k == 2000)
        {
            return x;
        }
        if (k > 0)
        {
            gamma = (s.val[(k - 1) % m] * y.val[(k - 1) % m]) / (y.val[(k - 1) % m] * y.val[(k - 1) % m]);
        }
        //Approximation of the inverse of the Hessian of the quadratic form of the function
        DiagonalMatrix Hk_0 = Id * gamma;
        //Calculation of the descent direction Hk*Delta(e) using the two loop recursion approximation
        for (int i = max(k - 1, 0); i > max(k - m - 1, 0); i--)
        {
            a.val[i % m] = (1 / (y.val[i % m] * s.val[i % m])) * (s.val[i % m] * q);
            q = q - y.val[i % m] * a.val[i % m];
        }
        Vector<double> r = Hk_0 * q;

        for (int i = max(k - m, 0); i < max(k, 0); i++)
        {
            b = (1 / (y.val[i % m] * s.val[i % m])) * (y.val[i % m] * r);
            r = r + s.val[i % m] * (a.val[i % m] - b);
        }

        Vector<double> descentDirection = r * -1;

        //Calculation of the optimal step size alpha using the strong Wolfe conditions
        double alpha = 1;
        double f = function(x, M);
        cout << "function: " << f << "\n";
        double ps = gradient * descentDirection;
        //Wolfe line search
        int wolfe = 0;
        while (true)
        {
            Vector<double> xd = x + descentDirection * alpha;
            double fd = function(xd, M);
            Vector<double> g = gradientFunction(xd, M);

            //Strong Wolfe conditions
            if ((fd <= f + c1 * alpha * ps && abs(g * descentDirection) <= c2 * abs(ps)) || (wolfe > wolfemax))
            {
                break;
            }
            alpha = alpha / 2;
            wolfe++;
        }

        Vector<double> xkPlusOne = x + descentDirection * alpha;

        y.val[k % m] = gradientFunction(xkPlusOne, M) - gradientFunction(x, M);
        s.val[k % m] = xkPlusOne - x;
        x = xkPlusOne;
        k++;
    }
};