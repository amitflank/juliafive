#include "JuliaSetFive.h"

JuliaSetFive( ) : JuliaSet(){}

JuliaSetFive::~JuliaSetFive( ){}

void JuliaSetFive::calculateNextPoint(const double x0, const double y0, double& x1, double &y1) const{
    double r = std::sqrt(x0 * x0 + y0 * y0);
    double theta = std::atan2(y0, x0);
    x1 = std::pow(r, 5) * std::cos(5 * theta) + getA();
    y1 = std::pow(r, 5) * std::sin(5 * theta) + getB();
  }
