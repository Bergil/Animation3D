#include "dynamicworld"

DynamicWorld()
{

}
		
void init(const int dimX, const int dimY)
{

}

void computeOneStep(const float dt)     // à appeler depus la fonction animate de la class Viewer
{
	for(int i = 0; i < m_p.size(); i++)
	{
		m_p.computeOneStep(dt);
	}
}

void draw() const;
{
	glBegin( GL_LINES );
	for(int i = 0; i < m_p.size(); i++)
	{
		glTranslatef(m_p.getP().x, m_p.getP().y, m_p.getP().z);
		draw_cube();
	}
	glEnd();

}     