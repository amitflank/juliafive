#ifndef _COMPLEX_FRACTAL_H_
#define _COMPLEX_FRACTAL_H_

#include <cmath>
#include "NumberGrid.h"

class ComplexFractal : public NumberGrid {
  public:
    ComplexFractal( );
    ComplexFractal(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y);
    virtual ~ComplexFractal( );
    double getMinX( ) const;
    double getMaxX( ) const;
    double getMinY( ) const;
    double getMaxY( ) const;
    virtual void setGridSize(const int& height, const int& width);
    void setPlaneSize(const double& min_x, const double& max_x, const double& min_y, const double& max_y);
    double getDeltaX( ) const;
    double getDeltaY( ) const;
    void setDeltas(const double& delta_x, const double& delta_y);
    double calculateDeltaX( ) const;
    double calculateDeltaY( ) const;
    double calculatePlaneXFromPixelColumn(const int& column) const;
    double calculatePlaneYFromPixelRow(const int& row) const;
    void calculatePlaneCoordinatesFromPixelCoordinates(const int& row, const int& column, double& x, double& y) const;
    bool valid_delta(double delta);
    bool validMin(double min);
    bool validMax(double max);


  private:
    double mMinX;
    double mMaxX;
    double mMinY;
    double mMaxY;
    double mDelta_X;
    double mDelta_Y;

};
#endif /*_Complex_Fractal_H_*/
