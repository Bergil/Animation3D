#ifndef __Array2D_H__
#define __Array2D_H__

#include <string>
#include <vector>
#include <cassert>
#include <fstream>
#include <iostream>


class Array2D
	{
	public:
	   Array2D() { m_dimX=m_dimY=0; }
	   void init(const int DIMX, const int DIMY) { m_dimX=DIMX; m_dimY=DIMY; m_data.resize(m_dimX*m_dimY); }
	   const int dimX() const { return m_dimX; }
	   const int dimY() const { return m_dimY; }
	   float& operator()(const int x, const int y); 
	  
	   float operator()(const int x, const int y) const ;

	   float interpolate(const float x, const float y);

	   
	protected:
	   std::vector<float> m_data; // OU float* m_data
	   int m_dimX, m_dimY;
	};

#endif
