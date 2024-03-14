#ifndef __MATRIX__
#define __MATRIX__
#include <string>

using namespace std;
template<typename T>
class Vector;

class Matrix
{
public:
   int n, m; // Number of rows, columns
   double **val; // Array of values

   // Constructors
   Matrix(); // Default constructor
   Matrix(int n_l, int n_c); // Constructor with dimensions, initialization to 0
   Matrix(int n_l, int n_c, double value); // Constructor with dimensions + a value
   Matrix(const Matrix &M); // Copy constructor
   Matrix(int n, const string &id); // Identity matrix constructor

   // Destructor
   ~Matrix();

   // Operators
   Matrix &operator=(const Matrix &M);
   double &operator()(int i, int j) const;

   Matrix operator+(const Matrix &M) const;
   Matrix operator-(const Matrix &M) const;
   Matrix operator*(const Matrix &M) const;
   Vector<double> operator*(const Vector<double> &V) const;

   Matrix operator*(const double nb) const;
   Matrix operator/(const double nb) const;

   Matrix &operator/=(const double nb);
   Matrix &operator*=(const double nb);

   Matrix &operator+=(const Matrix &M);
   Matrix &operator-=(const Matrix &M);

   double norm();

   // Output operators
   void print();
   friend ostream &operator<<(ostream &, const Matrix &M);
};

Matrix transpose(const Matrix &M);
Vector<double> toVector(const Matrix &M);

class DiagonalMatrix
{ // Class for diagonal square matrices
public:
   int n; // Size of the square matrix
   double *val; // Array of values (diagonal only)

   DiagonalMatrix(); // Default constructor
   DiagonalMatrix(int n_l, double value); // Constructor with dimensions + a value

   // Destructor
   ~DiagonalMatrix();

   friend ostream &operator<<(ostream &, const DiagonalMatrix &M);
   DiagonalMatrix &operator=(const DiagonalMatrix &M);
   DiagonalMatrix operator*(const double nb) const;
   Vector<double> operator*(const Vector<double> &V) const;
};

#endif