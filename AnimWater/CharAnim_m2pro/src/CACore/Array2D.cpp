#include "Array2D.h"

float& Array2D::operator()(const int x, const int y) 
   { 
      assert( x>=0 && x<m_dimX && y>=0 && y<m_dimY);
      return m_data[ y*m_dimX+x ]; 
   }
   
float Array2D::operator()(const int x, const int y) const
   { 
      assert( x>=0 && x<m_dimX && y>=0 && y<m_dimY);
      return m_data[ y*m_dimX+x ]; 
   }

float Array2D::interpolate(const float x, const float y) 
{ 
	if ((x<0) || (x>m_dimX) || (y<0) || (y>m_dimY)) return 0.f;
      int X = int(x);
      int Y = int(y);
      if ((X+1>=m_dimX) || (Y+1>=m_dimY)) return operator()(X,Y);
      float IX_b = (x-X)*operator()(X+1,Y) + (X+1-x)*operator()(X,Y);
      float IX_h = (x-X)*operator()(X+1,Y+1) + (X+1-x)*operator()(X,Y+1);
      return (y-Y)*IX_h + (Y+1-y)*IX_b;
}
