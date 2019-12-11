#include "JuliaSet.h"

JuliaSet::JuliaSet() : ComplexFractal(){
  mA = -.650492;
  mB = -.478235;
}

JuliaSet::JuliaSet(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b) :
ComplexFractal(height, width, min_x, max_x, min_y, max_y){
  mA = a;
  mB = b;
}

JuliaSet::~JuliaSet( ){}


double JuliaSet::getA( ) const { return mA; }
double JuliaSet::getB( ) const { return mB; }

void JuliaSet::setParameters(const double& a, const double& b){
  bool valid_a = validMin(a) && validMax(a);
  bool valid_b = validMin(b) && validMax(b);

  if(valid_a && valid_b){
    mA = a;
    mB = b;
  }
}

void JuliaSet::calculateNextPoint(const double x0, const double y0, double& x1, double &y1) const{
    x1 = x0 * x0 - y0 * y0  + mA;
    y1 = 2 * x0 * y0 + mB;
  }

bool JuliaSet::near_origin(double x, double y) const{
    return pow(x, 2.0) + pow(y, 2.0) <= 4.0;
}

bool JuliaSet::valid_cord(double x, double y) const{
  bool valid_y = (y <= getMaxY()) && (y >= getMinY());
  bool valid_x = (x <= getMaxX()) && (x >= getMinX());
  return valid_x && valid_y;
}

int JuliaSet::calculatePlaneEscapeCount(const double& x0, const double& y0) const{
  int max_count = getMaxNumber();
  double x1;
  double y1;

  int count = 0;
  for(count = 0; count < max_count; count++){


    if (count == 0){
      if(!near_origin(x0, y0)){
        break;
      }
      calculateNextPoint(x0, y0, x1, y1);
    }
    else{
      if(!near_origin(x1, y1)){
        break;
      }
      calculateNextPoint(x1, y1, x1, y1);
    }

  }
  return count;
}

int JuliaSet::calculateNumber(const int& row, const int& column) const{
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
