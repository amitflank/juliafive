#include "ComplexFractal.h"

ComplexFractal::ComplexFractal() {
  setGridSize(200, 300);
  NumberGrid::setMaxNumber(255);
  mDelta_X = .01;
  mDelta_Y = .01;
  mMinX = -1.5;
  mMaxX = 1.5;
  mMinY = -1.0;
  mMaxY = 1.0;
}

ComplexFractal::ComplexFractal(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y){
  setGridSize(height, width);
  NumberGrid::setMaxNumber(255);
  mMinX = min_x;
  mMaxX = max_x;
  mMinY = min_y;
  mMaxY = max_y;
  mDelta_X = calculateDeltaX();
  mDelta_Y = calculateDeltaY();
}

ComplexFractal::~ComplexFractal( ){}

double ComplexFractal::getMinX( ) const { return mMinX; }
double ComplexFractal::getMaxX( ) const { return mMaxX; }
double ComplexFractal::getMinY( ) const { return mMinY; }
double ComplexFractal::getMaxY( ) const { return mMaxY; }

void ComplexFractal::setGridSize(const int& height, const int& width){
  if(height >= 2 && width >= 2){
    NumberGrid::setGridSize(height, width);
    setDeltas(calculateDeltaX(), calculateDeltaY());
  }
}

void ComplexFractal::setPlaneSize(const double& min_x, const double& max_x, const double& min_y, const double& max_y){
  double tmp_min_x = min_x;
  double tmp_max_x = max_x;
  double tmp_min_y = min_y;
  double tmp_max_y = max_y;

  if(min_x > max_x){
    double tmp = min_x;
    tmp_min_x = max_x;
    tmp_max_x = tmp;
  }

  if(min_y > max_y){
    double tmp = min_y;
    tmp_min_y = max_y;
    tmp_max_y = tmp;
  }

  bool min_max_not_same = (tmp_min_x != tmp_max_x) && (tmp_min_y != tmp_max_y);
  bool valid_min_max = validMin(tmp_min_y) && validMin(tmp_min_x) && validMax(tmp_max_x) && validMax(tmp_max_y);
  /*std::cout <<(min_max_not_same && valid_min_max) << "\n";*/
  if(min_max_not_same && valid_min_max){
    mMinX = tmp_min_x;
    mMinY = tmp_min_y;
    mMaxX = tmp_max_x;
    mMaxY = tmp_max_y;
    setDeltas(calculateDeltaX(), calculateDeltaY());
  }
}

double ComplexFractal::getDeltaX( ) const{ return mDelta_X; }
double ComplexFractal::getDeltaY( ) const{ return mDelta_Y; }

void ComplexFractal::setDeltas(const double& delta_x, const double& delta_y){
  if(valid_delta(delta_x) && valid_delta(delta_y)){
    mDelta_X = delta_x;
    mDelta_Y = delta_y;
  }
}

bool ComplexFractal::valid_delta(double delta){ return delta > 0;}
bool ComplexFractal::validMin(double min){ return min >= -2.0; }
bool ComplexFractal::validMax(double max){ return max <= 2.0; }


double ComplexFractal::calculateDeltaX( ) const{ return (getMaxX() - getMinX()) / (getWidth() - 1);}
double ComplexFractal::calculateDeltaY( ) const{ return (getMaxY() - getMinY()) / (getHeight() - 1);}


void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates(const int& row, const int& column, double& x, double& y) const{
  double new_y = calculatePlaneYFromPixelRow(row);
  double new_x = calculatePlaneXFromPixelColumn(column);

  if(new_x == 0.0 || new_y == 0.0){
    x = 0.0;
    y = 0.0;
  }
  else{
    x = new_x;
    y = new_y;
  }
}

double ComplexFractal::calculatePlaneXFromPixelColumn(const int& column) const{
  if (column < getWidth() && column >= 0){
    return getMinX() + column * getDeltaX();
  }
  else {
    return 0;
  }
}

double ComplexFractal::calculatePlaneYFromPixelRow(const int& row) const{

  if (row < getHeight() && row >= 0){
    return getMaxY() - row * getDeltaY();
  }
  else {
    return 0;
  }
}
