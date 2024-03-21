#ifndef __NEWTON_METHOD__
#define __NEWTON_METHOD__

#include "matrix.hpp"

Vector<double> gradientFunctional(const Vector<double> &x, const Matrix &image);
double functional(const Vector<double> &x, const Matrix &image);
Vector<double> LBFGS(Vector<double> &x, double (*function)(const Vector<double> &, const Matrix &), Vector<double> (*functionGradient)(const Vector<double> &, const Matrix &), const Matrix &image, double eps);
Vector<double> gradientHeight(const Vector<double> &x, const Matrix &h);
double heightFunctional(const Vector<double> &x, const Matrix &height);
void matrixToMesh(const string &file, const Matrix &M);

Vector<double> NewtonsMethod(Vector<double> &x0, double (*function)(const Vector<double> &, const Matrix &),
                              Vector<double> (*gradientFunction)(const Vector<double> &, const Matrix &),
                              Matrix (*hessianFunction)(const Vector<double> &, const Matrix &),
                              const Matrix &M, double eps, int maxIter);

#endif