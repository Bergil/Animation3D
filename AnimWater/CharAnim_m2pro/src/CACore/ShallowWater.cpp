 
#include "ShallowWater.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Vec3.h>

using namespace math;

ShallowWater::ShallowWater(){
	init(32, 32, 10, 0.01);
}


ShallowWater::ShallowWater(const int DIMX, const int DIMY, const int hauteurWater, float Dtnew){
	init(DIMX, DIMY, hauteurWater, Dtnew);
}

void ShallowWater::init(const int DIMX, const int DIMY, const int hauteurWater, float Dtnew)
{
	m_g.init(DIMX, DIMY);
	m_h.init(DIMX, DIMY);
	m_n.init(DIMX, DIMY);
	m_n2.init(DIMX, DIMY);
	m_vX.init(DIMX, DIMY);
	m_vY.init(DIMX, DIMY);
	vyprim.init(DIMX, DIMY);
	vxprim.init(DIMX, DIMY);
	Dt = Dtnew;
	for (int i = 0; i < DIMX; i++){
		for(int j = 0; j < DIMY; j++){
			m_g(i,j) = 0;
			//m_h(i,j) = 0;
			m_n(i,j) = hauteurWater - m_g(i,j);
			m_n2(i,j) = hauteurWater - m_g(i,j);
			m_vX(i,j) = 0;
			m_vY(i,j) = 0;
		}
	}
	
}

void ShallowWater::ShallowWaterStep()
{
//																																														return;
	Advect(m_n, m_n2);
	m_n = m_n2;
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

void ShallowWater::Advect(Array2D& src, Array2D& dst)
{
	float x, y;
	for(int j = 1; j < src.dimY()-1; j++){
		for(int i = 1; i < src.dimX()-1; i++){
			x = float(i) - Dt * m_vX(i,j);
			y = float(j) - Dt * m_vY(i,j);
			dst(i,j) = src.interpolate(x, y);
		}
	}
}

void ShallowWater::UpdateHeight()
{
	for(int j=1; j < m_n.dimY()-1; j++){
		for(int i=1; i < m_n.dimX()-1; i++){
			m_n(i,j) = m_n(i,j) - m_n(i,j) * Dt * ((m_vX(i+1,j) - m_vX(i, j)) / watersize + (m_vY(i, j+1) - m_vY(i, j)) / watersize);
		}
	}
}

void ShallowWater::UpdateVelocities()
{
	float a = 9.81;
	for(int j = 1; j < m_h.dimY() -1; j++){
		for(int i = 2; i < m_h.dimX() -1; i++){
			m_vX(i, j) += a* Dt * ((m_h(i-1,j) - m_h(i, j)) / watersize);
		}
	}
	
	for(int j = 2; j < m_h.dimY() -1; j++){
		for(int i = 1; i < m_h.dimX() -1; i++){
			m_vY(i, j) += a* Dt * ((m_h(i,j-1) - m_h(i, j)) / watersize);
		}
	}
}

Vec3<float> normale(const Array2D & array, int i, int j){
	Vec3<float> y(Vec3<float>(i-1, array(i-1,j), j) - Vec3<float>(i+1, array(i+1, j), j)), 
				n(Vec3<float>(i, array(i,j-1), j-1) - Vec3<float>(i, array(i, j+1), j+1)), trucbizarre;
	trucbizarre = crossProduct(y, n);
	return -trucbizarre.normalize();
}

void ShallowWater::draw() const  {
	Vec3<float> n;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_QUADS);
	glColor3f(118 / 255.0f, 97 / 255.0f, 56 / 255.0f);
	for(int i = 1; i < m_g.dimX()-2; i++){
		for(int j = 1; j < m_g.dimY()-2; j++){
			n = normale(m_g, i, j);
			glNormal3f(n.x, n.y, n.z);
			glVertex3f(i, m_g(i,j), j);
			
			n = normale(m_g, i+1, j);
			glNormal3f(n.x, n.y, n.z);
			glVertex3f(i+1, m_g(i+1,j), j);
			
			n = normale(m_g, i+1, j+1);
			glNormal3f(n.x, n.y, n.z);
			glVertex3f(i+1, m_g(i+1,j+1), j+1);
			
			n = normale(m_g, i, j+1);
			glNormal3f(n.x, n.y, n.z);
			glVertex3f(i, m_g(i,j+1), j+1);
		}
	}
	glEnd();	
	
	glBegin(GL_QUADS);
	glColor4f(0.0,0.0,1.0, 0.3);	
	for(int i = 1; i < m_h.dimX()-2; i++){
		for(int j = 1; j < m_h.dimY()-2; j++){
			n = normale(m_h, i, j);
			glNormal3f(n.x, n.y, n.z);
			glVertex3f(i, m_h(i,j), j);
			
			n = normale(m_h, i+1, j);
			glNormal3f(n.x, n.y, n.z);
			glVertex3f(i+1, m_h(i+1,j), j);
			
			n = normale(m_h, i+1, j+1);
			glNormal3f(n.x, n.y, n.z);
			glVertex3f(i+1, m_h(i+1,j+1), j+1);
			
			n = normale(m_h, i, j+1);
			glNormal3f(n.x, n.y, n.z);
			glVertex3f(i, m_h(i,j+1), j+1);
		}
	}
	glEnd();	
		
}

