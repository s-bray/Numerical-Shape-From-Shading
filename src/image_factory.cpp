#include "../include/image_factory.hpp"
#include "../include/matrix.hpp"
#include "../include/vector.hpp"
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

ImageFactory::ImageFactory(const char *filename)
{ //constructor that reads the mesh file
  ifstream file(filename, ios::in);

  if (file)
  {
    for (int i = 0; i < 8; i++)
    {
      file.ignore(50, '\n');
    }

    file >> n_vert;
    Matrix V(n_vert, 3);

    for (int i = 1; i < n_vert + 1; i++)
    {
      file >> V(i, 1);
      file >> V(i, 2);
      file >> V(i, 3);
      file.ignore(50, '\n');
    }

    file.ignore(50, '\n');
    file.ignore(50, '\n');

    file >> n_quad;
    Matrix Q(n_quad, 4);

    for (int i = 1; i < n_quad + 1; i++)
    {
      file >> Q(i, 1);
      file >> Q(i, 2);
      file >> Q(i, 3);
      file >> Q(i, 4);
      file.ignore(50, '\n');
    }

    file.close();
    vertices = V;
    quadrangles = Q;
    pix_m = vertices(n_vert, 1);
    pix_n = vertices(n_vert, 2);
  }
  else
  {
    cerr << "Unable to open the file!" << endl;
  }
}

void ImageFactory::flatten(Vector<double> &source)
{ //mesh -> 2D matrix
  Matrix I(pix_m, pix_n);
  int S1, S2, S3;
  Vector<double> V1(3);
  Vector<double> V2(3);
  Vector<double> V3(3);
  Matrix h(2 * pix_m, pix_n);
  for (int i = 0; i < n_quad; i++)
  {//iterate over the rectangles of the mesh
    S1 = int(quadrangles(i + 1, 1));
    S2 = int(quadrangles(i + 1, 2));
    S3 = int(quadrangles(i + 1, 3));

    // Take two sides of the rectangle
    V1(1) = vertices(S1, 1) - vertices(S2, 1);
    V1(2) = vertices(S1, 2) - vertices(S2, 2);
    V1(3) = vertices(S1, 3) - vertices(S2, 3);

    V2(1) = vertices(S3, 1) - vertices(S2, 1);
    V2(2) = vertices(S3, 2) - vertices(S2, 2);
    V2(3) = vertices(S3, 3) - vertices(S2, 3);

    // normal to the mesh: cross product of sides of the rectangle
    V3 = V1 ^ V2;
    V3 /= V3.norm(); //normalization

    // Calculate the grayscale (assumed to be the same throughout the rectangle)
    I.val[i / pix_m][i % pix_n] = abs(255 * (source * V3));

    // calculate the directional derivatives of the height
    h.val[i / pix_n][i % pix_n] = -V3(1)/V3(3);
    h.val[(i / pix_n) + pix_m][i % pix_n] = -V3(2)/V3(3);
  }
  derivH = h;
  image = I;
}

void ImageFactory::save2D(const char *savefile)
{ //save matrix -> image file (ppm)
  string grey;
  ofstream img(savefile);
  img << "P3" << endl;
  img << pix_n << " " << pix_m << endl;
  img << "255" << endl;
  for (int i = 0; i < pix_m; i++)
  {
    for (int j = 0; j < pix_n; j++)
    {
      grey = to_string(int(image.val[i][j]));
      img << grey << " " << grey << " " << grey << endl;
    }
  }
  img.close();
}

Matrix csvtoMatrix(const char* csvfile)
{ //read csv file
  ifstream csv(csvfile, ios::in);
  int rows, cols;
  csv >> rows;
  csv >> cols;
  Matrix M(rows, cols);
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      csv >> M.val[i][j];
    }
  }
  return M;
}