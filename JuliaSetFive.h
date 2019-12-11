#ifndef _JULIASET_FIVE_H_
#define _JULIASET_FIVE_H_
#include <cmath>
#include "JuliaSet.h"


class JuliaSetFive : public JuliaSet{

  public:
    JuliaSetFive( );
    virtual ~JuliaSetFive( );
    virtual void calculateNextPoint( const double x0, const double y0, double& x1, double &y1 ) const;
};

#endif
