#include "dynamicworld.h"

using namespace math; 
using namespace std;

DynamicWorld::DynamicWorld()
{
	//init(0,0);
}

DynamicWorld::DynamicWorld(int dimX,int dimY)
{
	init(dimX,dimY);
}
		
void DynamicWorld::init(int dimX, int dimY)
{
	/*for (int i = 0; i < dimY; i++)
	{
		for (int j = 0; j < dimX; j++)
		{
			Particle p(1.0, Vec3f(i,j, 0.0));
			m_p.push_back(p);
		}
	}*/
	gravity = Vec3f(0.0, -1.0, 0.0);
	Particle p(1.0, Vec3f(dimX,dimY, 0.0));
	m_p.push_back(p);
}

void DynamicWorld::computeOneStep(const float dt)     // à appeler depus la fonction animate de la class Viewer
{
	for(unsigned int i = 0; i < m_p.size(); i++)
	{
		m_p[i].addForce(gravity);
		m_p[i].computeOneStep(dt);
	}
}

void DynamicWorld::draw()const
{
	for(unsigned int i = 0; i < m_p.size(); i++)
	{
		glPushMatrix();
		glTranslatef(m_p[i].getP().x, m_p[i].getP().y, m_p[i].getP().z);
		draw_cube();
		glPopMatrix();
	}

}     
