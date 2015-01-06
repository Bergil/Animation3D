#ifndef _DYNAMICWORLD_H_
#define _DYNAMICWORLD_H_

#include "particle.h"
#include "spring.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Viewer.h>

class DynamicWorld
{
	protected:
		std::vector<Particle> m_p;
		std::vector<Spring> m_s;
		math::Vec3f gravity;

	public:
		DynamicWorld();
		DynamicWorld(int dimX,int dimY);
		void init(int dimX,int dimY);
		void computeOneStep(const float dt);     // à appeler depus la fonction animate de la class Viewer
		void draw() const;                       // à appeler depuis la fonction draw de la class Viewer
};

#endif
