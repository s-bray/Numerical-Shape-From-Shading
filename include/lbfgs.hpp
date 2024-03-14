#ifndef __LBFGS__
#define __LBFGS__
#include "matrix.hpp"

Vector<double> gradientFunctional(const Vector<double> &x, const Matrix &image);
double functional(const Vector<double> &x, const Matrix &image);
Vector<double> LBFGS(Vector<double> &x, double (*function)(const Vector<double> &, const Matrix &), Vector<double> (*functionGradient)(const Vector<double> &, const Matrix &), const Matrix &image, double eps);
Vector<double> gradientHeight(const Vector<double> &x, const Matrix &h);
double heightFunctional(const Vector<double> &x, const Matrix &height);
void matrixToMesh(const string &file, const Matrix &M);
#endif