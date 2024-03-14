#ifndef __VECTOR__
#define __VECTOR__
#include <iostream>
#include <cmath>
#include "./matrix.hpp"
using namespace std;

template <typename T>
class Vector
{
 public:
   int dim;
   T *val;
   //Constructors
   Vector();
   Vector(int d, T x = T(0));
   Vector(const Vector &V);

   //Destructor
   ~Vector();

   //Internal Operators
   Vector<T> &operator=(const Vector<T> &);
   Vector<T> &operator*=(const T);
   Vector<T> &operator/=(const T);
   Vector<T> operator^(const Vector<T> &);
   Vector<T> operator+(const Vector<T> &A);
   Vector<T> operator-(const Vector<T> &A);
   Vector<T> operator*(const T);
   Vector<T> concatenate(const Vector<T> &A);
   Matrix toMatrix(const int i, const int j) const;
   T operator*(const Vector<T> &);
   T &operator()(int) const;
   Vector<T> operator()(int, int) const;
   //Print Operator
   template <typename type>
   friend ostream &operator<<(ostream &, const Vector<type> &);
   //Norm
   double norm();
};
//External Operators
//Method Definitions

//Constructors
template <typename T>
Vector<T>::Vector() : dim(0), val(0){};

template <typename T>
Vector<T>::Vector(int d, T v)
{
   dim = d;
   val = new T[dim];
   for (int i = 0; i < dim; i++)
   {
       val[i] = v;
   }
};

template <typename T>
Vector<T>::Vector(const Vector<T> &V)
{
   dim = V.dim;
   val = NULL;
   if(dim<=0) return;
   val = new T[dim];
   for (int i = 0; i < dim; i++)
   {
       val[i] = V.val[i];
   }
};

//Destructor
template <typename T>
Vector<T>::~Vector()
{
   if (val != 0)
       delete[] val;
};

//Internal Operations
template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &V)
{
   dim = V.dim;
   if (val != 0)
       delete[] val;
   val = new T[dim];
   for (int i = 0; i < dim; i++)
   {
       val[i] = V.val[i];
   }
   return *this;
};

template <typename T>
Vector<T> &Vector<T>::operator*=(const T f)
{
   for (int i = 0; i < dim; i++)
   {
       val[i] *= f;
   }
   return *this;
};

template <typename T>
Vector<T> &Vector<T>::operator/=(const T f)
{
   if (f == 0)
   {
       cout << "Error: division by 0";
       exit(1);
   }
   for (int i = 0; i < dim; i++)
   {
       val[i] /= f;
   }
   return *this;
};

template <typename T>
T &Vector<T>::operator()(int i) const
{
   return val[i - 1];
};

template <typename T>
Vector<T> Vector<T>::operator()(int i, int j) const
{
   if (i >= j)
   {
       cout << "Error: i must be strictly less than j \n";
       exit(1);
   }
   int dim = j - i + 1;
   Vector temp(dim);
   for (int k = 0; k < dim; k++)
   {
       temp.val[k] = val[i + k];
   }
   return temp;
}
template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T> &A)
{
   if (A.dim != this->dim)
   {
       cout << "Error: vectors have different dimensions. \n";
       exit(1);
   }
   Vector<T> C = *this;
   for (int i = 0; i < A.dim; i++)
   {
       C.val[i] += A.val[i];
   }
   return C;
};
template <typename T>
Vector<T> Vector<T>::operator-(const Vector<T> &A)
{
   if (A.dim != this->dim)
   {
       cout << "Error: vectors have different dimensions. \n";
       exit(1);
   }
   Vector<T> C = *this;
   for (int i = 0; i < A.dim; i++)
   {
       C.val[i] -= A.val[i];
   }
   return C;
};

template <typename T>
Vector<T> Vector<T>::operator*(const T a)
{
   Vector V = *this;
   for (int i = 0; i < dim; i++)
   {
       V.val[i] *= a;
   }
   return V;
};

template <typename T>
Vector<T> Vector<T>::concatenate(const Vector<T> &A)
{
   Vector C(A.dim + this->dim);
   for (int i = 0; i < this->dim; i++)
   {
       C.val[i] = this->val[i];
   }
   for (int j = 0; j < A.dim; j++)
   {
       C.val[j + this->dim] = A.val[j];
   }
   return C;
};

template <typename T>
Matrix Vector<T>::toMatrix(const int i, const int j)const
{
   if (i * j != dim)
   {
       cout << "Error: dimension mismatch \n";
       exit(1);
   }
   Matrix temp(i, j);
   for (int k = 0; k < i; k++)
   {
       for (int l = 0; l < j; l++)
       {
           temp.val[k][l] = val[l+k*j];
       }
   }
   return temp;
}

//Cross product in 3D
template <typename T>
Vector<T> Vector<T>::operator^(const Vector<T> &V)
{
   if ((dim != V.dim) || (dim > 3))
   {
       cout << "Error: dimensions are greater than 3 or not equal.\n";
       exit(1);
   }
   Vector<T> result(3);

   result(1) = val[1] * V(3) - val[2] * V(2);
   result(2) = val[2] * V(1) - val[0] * V(3);
   result(3) = val[0] * V(2) - val[1] * V(1);
   return result;
}

//Dot product
template <typename T>
T Vector<T>::operator*(const Vector<T> &V)
{
   T result = T(0);
   for (int i = 0; i < dim; i++)
   {
       result += val[i] * V.val[i];
   }
   return result;
}

//Print Operator
template <typename T>
ostream &operator<<(ostream &out, const Vector<T> &V)
{
   out << "( ";
   for (int i = 0; i < V.dim; i++)
   {
       out << V.val[i] << " ";
   }
   out << ")\n";
   return out;
};

//Norm
template <typename T>
double Vector<T>::norm()
{
   return sqrt(((*this) * (*this)));
};

#endif