 
#include "ShallowWater.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

ShallowWater::ShallowWater(){
	init(10, 10);
}

ShallowWater::ShallowWater(const int DIMX, const int DIMY){
	init(DIMX, DIMY);
}

ShallowWater::ShallowWater(const int DIMX, const int DIMY, const int hauteurWater, float Dtnew){
	init(DIMX, DIMY, hauteurWater, Dtnew);
}

void ShallowWater::init(const int DIMX, const int DIMY)
{
	m_g.init(DIMX, DIMY);
	m_h.init(DIMX, DIMY);
	m_n.init(DIMX, DIMY);
	m_vX.init(DIMX, DIMY);
	m_vY.init(DIMX, DIMY);
	vyprim.init(DIMX, DIMY);
	vxprim.init(DIMX, DIMY);
	Dt = 0.1;
	for (int i = 0; i < DIMX; i++){
		for(int j = 0; j < DIMY; j++){
			m_g(i,j) = 0;
			m_h(i,j) = 10;
			m_n(i,j) = m_g(i,j) + m_h(i,j);
			m_vX(i,j) = 0;
			m_vY(i,j) = 0;
		}
	}
}

void ShallowWater::init(const int DIMX, const int DIMY, const int hauteurWater, float Dtnew)
{
	m_g.init(DIMX, DIMY);
	m_h.init(DIMX, DIMY);
	m_n.init(DIMX, DIMY);
	m_vX.init(DIMX, DIMY);
	m_vY.init(DIMX, DIMY);
	vyprim.init(DIMX, DIMY);
	vxprim.init(DIMX, DIMY);
	Dt = Dtnew;
	for (int i = 0; i < DIMX; i++){
		for(int j = 0; j < DIMY; j++){
			m_g(i,j) = 0;
			m_h(i,j) = hauteurWater;
			m_n(i,j) = m_g(i,j) + m_h(i,j);
			m_vX(i,j) = 0;
			m_vY(i,j) = 0;
		}
	}
	
}

void ShallowWater::ShallowWaterStep()
{
	Advect(m_n, m_n);
	Advect(m_vX, vxprim);
	Advect(m_vY, vyprim);
	m_vX = vxprim;      
	m_vY = vyprim;   
	UpdateHeight();
	for (int i = 0; i< m_g.dimX(); i++){
		for (int j = 0; j< m_g.dimY(); j++){
			m_h(i,j) = m_n(i,j) + m_g(i,j);
		}
	}
	UpdateVelocities(); 
}

void ShallowWater::Advect(const Array2D& src, Array2D& dst)
{
	float x, y;
	for(int i = 1; i < src.dimX()-1; i++){
		for(int j = 1; j < src.dimY()-1; j++){
			x = i - Dt * m_vX(i,j);
			y = j - Dt * m_vY(i,j);
			dst(i,j) = dst.interpolate(x, y);
		}
	}
}

void ShallowWater::UpdateHeight()
{
	for(int i=1; i < m_n.dimX()-1; i++){
		for(int j=1; j < m_n.dimY()-1; j++){
			m_n(i,j) = m_n(i,j) - m_n(i,j) * Dt * ((m_vX(i+1,j) - m_vY(i, j)) / watersize + (m_vY(i, j+1) - m_vY(i, j)) / watersize);
		}
	}
}

void ShallowWater::UpdateVelocities()
{
	float a = -9.81;
	for(int j = 1; j < m_n.dimY() -1; j++){
		for(int i = 2; i < m_n.dimX() -1; i++){
			m_vX(i, j) += a* Dt * (m_h(i-1,j) - m_h(i, j)) / watersize;
		}
	}
	for(int j = 2; j < m_n.dimY() -1; j++){
		for(int i = 1; i < m_n.dimX() -1; i++){
			m_vY(i, j) += a* Dt * (m_h(i,j-1) - m_h(i, j)) / watersize;
		}
	}
}

void ShallowWater::draw() const  {
	glPointSize(1.0);
	glBegin(GL_POINTS);
	glColor3f(0.0,0.0,1.0);
	for(int i = 0; i < m_h.dimX(); i++){
		for(int j = 0; j < m_h.dimY(); j++){
			glVertex3f(i, m_h(i,j), j);
		}
	}
	glEnd();	
	
}
  
