#include "MandelbrotSet.h"

MandelbrotSet::MandelbrotSet() : ComplexFractal(){
  int a = 1;
  a++;
}

MandelbrotSet::MandelbrotSet(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y) :
  ComplexFractal(height, width, min_x, max_x, min_y, max_y){
    int a = 1;
    a++;
}

MandelbrotSet::~MandelbrotSet( ){}

void MandelbrotSet::calculateNextPoint(const double x0, const double y0, const double& a, const double& b, double& x1, double &y1) const{
  x1 = x0 * x0 - y0 * y0 + a;
  y1 = 2 * x0 * y0 + b;
}

bool MandelbrotSet::near_origin(double x, double y) const{
    return pow(x, 2.0) + pow(y, 2.0) <= 4.0;
}

int MandelbrotSet::calculatePlaneEscapeCount(const double& a, const double& b) const {
  int max_count = getMaxNumber();
  double x1 = 0;
  double y1 = 0;

  calculateNextPoint(x1, y1, a, b, x1, y1);
  int count = 0;

  for(count = 0; count < max_count; count++){

      if(!near_origin(x1, y1)){
        break;
      }
      calculateNextPoint(x1, y1, a, b, x1, y1);
  }
  return count;
}

int MandelbrotSet::calculateNumber(const int& row, const int& column) const{
  double y_cord = calculatePlaneYFromPixelRow(row);
  double x_cord = calculatePlaneXFromPixelColumn(column);

  if(indexValid(row, column)){
    int count = calculatePlaneEscapeCount(x_cord, y_cord);
    return count;
  }
  else{
    return -1;
  }
}
