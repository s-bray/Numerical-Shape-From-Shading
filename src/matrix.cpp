#include "../include/matrix.hpp"
#include "../include/vector.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

//Definition of the Matrix class

// Constructors
Matrix::Matrix()
{
   n = 0;
   m = 0;
   val = 0;
};

Matrix::Matrix(int n_l, int n_c)
{
   n = n_l;
   m = n_c;
   val = new double *[n];

   for (int i = 0; i < n; i++)
   {
       val[i] = new double[m];

       for (int j = 0; j < m; j++)
       {
           val[i][j] = 0;
       }
   }
};

Matrix::Matrix(int n_l, int n_c, double value)
{
   n = n_l;
   m = n_c;
   val = new double *[n];

   for (int i = 0; i < n; i++)
   {
       val[i] = new double[m];

       for (int j = 0; j < m; j++)
       {
           val[i][j] = value;
       }
   }
};

Matrix::Matrix(const Matrix &M)
{
   n = M.n;
   m = M.m;
   val = new double *[n];

   for (int i = 0; i < n; i++)
   {
       val[i] = new double[m];

       for (int j = 0; j < m; j++)
       {
           val[i][j] = M.val[i][j];
       }
   }
};

Matrix::Matrix(int dim, const string &id)
{
   if (id != "Id")
   {
       cout << "This argument is not taken into account.\n";
       exit(1);
   }
   n = dim;
   m = dim;
   val = new double *[dim];
   for (int i = 0; i < dim; i++)
   {
       val[i] = new double[dim];
       for (int j = 0; j < dim; j++)
       {
           if (i == j)
           {
               val[i][j] = 1;
           }
           else
           {
               val[i][j] = 0;
           }
       }
   }
};

// Destructor

Matrix::~Matrix()
{
   if (val != 0)
   {
       for (int i = 0; i < n; i++)
       {
           delete[] val[i];
       }
       delete[] val;
       n = 0;
       m = 0;
   }
};

// Operators

Matrix &Matrix::operator=(const Matrix &M)
{
   if (this != &M) //assignment M = M not possible
   {
       if (M.n != n || M.m != m) // if sizes are not compatible
       {
           for (int i = 0; i < n; i++)
           {
               delete[] val[i];
           }
           delete[] val;
           n = M.n;
           m = M.m;
           val = new double *[n];
       }
   }

   for (int i = 0; i < n; i++)
   {
       val[i] = new double[m];
       for (int j = 0; j < m; j++)
       {
           val[i][j] = M.val[i][j];
       }
   }
   return *this;
};

double &Matrix::operator()(int i, int j) const
{
   if (i > n || j > m) // if out of range
   {
       cout << "Error: indices are too large.\n";
       exit(1);
   }
   return val[i - 1][j - 1];
};

Matrix Matrix::operator+(const Matrix &M) const
{
   Matrix tmp(n, m);
   for (int i = 0; i < n; i++)
       for (int j = 0; j < m; j++)
           tmp.val[i][j] = val[i][j] + M.val[i][j];

   return tmp;
};

Matrix Matrix::operator-(const Matrix &M) const
{
   Matrix tmp(n, m);
   for (int i = 0; i < n; i++)
   {
       for (int j = 0; j < m; j++)
       {
           tmp.val[i][j] = val[i][j] - M.val[i][j];
       }
   }
   return tmp;
};

Matrix Matrix::operator*(const Matrix &M) const
{
   Matrix tmp(n, M.m, 0);
   if (m == M.n)
   {
       for (int i = 0; i < n; i++)
           for (int j = 0; j < M.m; j++)
           {
               for (int k = 0; k < m; k++)
                   tmp.val[i][j] += val[i][k] * M.val[k][j];
           }
   }
   else
   {
       cout << "Error, the dimensions do not match.\n";
       exit(1);
   }
   return tmp;
};

Vector<double> Matrix::operator*(const Vector<double> &V) const
{
   if (m != V.dim)
   {
       cout << "The dimensions do not match.\n";
       exit(1);
   }
   Vector<double> temp(n);
   for (int i = 0; i < n; i++)
   {
       for (int j = 0; j < m; j++)
       {
           temp.val[i] += val[i][j] * V.val[j];
       }
   }
   return temp;
};

Matrix Matrix::operator*(const double nb) const
{
   Matrix tmp(n, m);
   for (int i = 0; i < n; i++)
       for (int j = 0; j < m; j++)
           tmp.val[i][j] = val[i][j] * nb;

   return tmp;
};

Matrix Matrix::operator/(const double nb) const
{
   Matrix tmp(n, m);
   if (nb)
   {
       for (int i = 0; i < n; i++)
           for (int j = 0; j < n; j++)
               tmp.val[i][j] /= nb;
   }
   else //division by 0 exception
   {
       cout << "Division by 0\n";
       exit(1);
   }
   return tmp;
};

Matrix &Matrix::operator*=(const double nb)
{
   for (int i = 0; i < n; i++)
       for (int j = 0; j < m; j++)
           val[i][j] = val[i][j] * nb;

   return *this;
};

Matrix &Matrix::operator/=(const double nb)
{
   if (nb)
   {
       for (int i = 0; i < n; i++)
           for (int j = 0; j < n; j++)
               val[i][j] /= nb;
   }
   else
   {
       cout << "Division by 0\n";
       exit(1);
   }
   return *this;
};

Matrix &Matrix::operator+=(const Matrix &M)
{
   for (int i = 0; i < n; i++)
       for (int j = 0; j < m; j++)
           val[i][j] += M.val[i][j];

   return *this;
};

Matrix &Matrix::operator-=(const Matrix &M)
{
   for (int i = 0; i < n; i++)
       for (int j = 0; j < m; j++)
           val[i][j] -= M.val[i][j];

   return *this;
};

// Output Operators

void Matrix::print()
{
   for (int i = 0; i < n; i++)
   {
       for (int j = 0; j < m; j++)
       {
           cout << val[i][j] << " ";
       }
       cout << "\n";
   }
};

ostream &operator<<(ostream &out, const Matrix &M)
{
   if (M.val == NULL)
   {
       cout << "The matrix has no values!\n";
       exit(1);
   }
   for (int i = 0; i < M.n; i++)
   {
       for (int j = 0; j < M.m; j++)
       {
           cout << M.val[i][j] << " ";
       }
       cout << "\n";
   }
   return out;
};

// External Operators

Vector<double> toVector(const Matrix &M)
{
   int dim_ = M.n * M.m;
   Vector<double> V(dim_);
   for (int i = 0; i < M.n; i++)
   {
       for (int j = 0; j < M.m; j++)
       {
           V.val[i * M.m + j] = M.val[i][j];
       }
   }
   return V;
};

Matrix transpose(const Matrix &M)
{
   int a = M.n;
   int b = M.m;

   Matrix T(b, a);

   for (int i = 0; i < a; i++)
   {
       for (int j = 0; j < b; j++)
       {
           T.val[j][i] = M.val[i][j];
       }
   }
   return T;
}

double Matrix::norm()
{
   double norm = 0;
   for (int i = 0; i < n; i++)
   {
       for (int j = 0; j < m; j++)
       {
           norm += val[i][j] * val[i][j];
       }
   }
   return sqrt(norm);
}

//Diagonal Square Matrices

DiagonalMatrix::DiagonalMatrix()
{
   n = 0;
   val = 0;
};

DiagonalMatrix::DiagonalMatrix(int n_l, double value)
{
   n = n_l;
   val = new double [n];

   for (int i = 0; i < n; i++)
   {
       val[i] = value;
   }
};

DiagonalMatrix::~DiagonalMatrix()
{
   if (val != 0)
   {
       delete[] val;
       n = 0;
   }
};

ostream &operator<<(ostream &out, const DiagonalMatrix &M)
{
   if (M.val == NULL)
   {
       cout << "The matrix has no values!\n";
       exit(1);
   }
   for (int i = 0; i < M.n; i++)
   {
       for (int j = 0; j < M.n; j++)
       {
           if (i==j)
           {
               cout << M.val[i] << " ";
           }
           else
           {
               cout << 0 << " ";
           }
       }
       cout << "\n";
   }
   return out;
}

DiagonalMatrix &DiagonalMatrix::operator=(const DiagonalMatrix &M)
{
   if (this != &M) //assignment M = M not possible
   {
       if (M.n != n) // if sizes are not compatible
       {
           delete[] val;
           n = M.n;
           val = new double[n];
       }
   }

   for (int i = 0; i < n; i++)
   {
       val[i] = M.val[i];
   }
   return *this;
}

DiagonalMatrix DiagonalMatrix::operator*(const double nb) const
{
   DiagonalMatrix tmp(n, 0);
   for (int i = 0; i < n; i++)
       tmp.val[i] = val[i] * nb;

   return tmp;
};

Vector<double> DiagonalMatrix::operator*(const Vector<double> &V) const
{
   if (n != V.dim)
   {
       cout << "The dimensions do not match.\n";
       exit(1);
   }
   Vector<double> temp(n);
   for (int i = 0; i < n; i++)
   {
       temp.val[i] += val[i] * V.val[i];
   }
   return temp;
};