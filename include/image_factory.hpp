#ifndef __IMAGEFACTORY__
#define __IMAGEFACTORY__

#include "./matrix.hpp"
#include "./vector.hpp"

class ImageFactory {
public:
   int n_vert, n_quad; // number of points/quadrangles of the mesh
   int pix_m, pix_n; // dimensions of the image
   Matrix vertices; // points of the mesh
   Matrix quadrangles; // quadrangles of the mesh (vertices indexed by vertices)
   Matrix image; // grayscale image 0->255
   Matrix derivH; // directional derivatives of the height at each point of the image

   ImageFactory(const char*); // constructor that reads the mesh file
   void flatten(Vector<double> &source); // 3D mesh -> 2D matrix
   void save2D(const char*); // save 2D matrix
};

Matrix csvtoMatrix(const char* csvfile); // convert csv file to matrix
#endif