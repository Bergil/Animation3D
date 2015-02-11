

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <time.h>
#include "CAViewer.h"
#include <BVH.h>
#include <BVHChannel.h>
#include <Mat4.h>
#include <Quaternion.h>

using namespace chara;
using namespace std;


void CAViewer::help()
{
	printf("Animation:\n");
	printf("   n: Next character pose\n");
	printf("   b: Back(Previous) character pose");
	printf("   shift+arrows: Move the target point");
	Viewer::help();
}


CAViewer::~CAViewer()
{
}



void CAViewer::init(int argc, char **argv)
{
	Viewer::init();

	int largeur = 50;
	int longueur = 50;
	water.init(longueur, largeur, 10, 0.01);
	for(int i = longueur/2-5; i < longueur/2+5; i++){
		for(int j = largeur/2-5; j < largeur/2+5; j++){
			water.setN(i,j, 15);
		}
	}
	if(argc > 1 && strcmp(argv[1], "NF") == 0)
	for(int i = 0; i < longueur; i++){
		for(int j = 0; j < largeur; j++){
			water.setG(i,j, sin((i+j)*3.1415926/longueur/2)*10);
			
		}
	}
}



void CAViewer::draw()
{
	glPushMatrix();
	//if (m_skel) m_skel->render();
	animate();
    water.draw();
	
	glPopMatrix();
}



void CAViewer::keyPressed(unsigned char key, int x, int y)
{
	bool handled = false;
	if ((key=='z'))
	{
		animate();
		//m_skel->setPostureFromBVH( *m_bvh, m_bvhFrame);
		handled = true;
	}
	else
	if ((key=='b'))
	{
		--m_bvhFrame;
		//m_skel->setPostureFromBVH( *m_bvh, m_bvhFrame);
		handled = true;
	}
	else
	if (key=='w')
	{
		bWireframe = !bWireframe;
		if (bWireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		handled = true;
	}

	if (!handled)
	{
		Viewer::keyPressed(key,x,y);
	}
	updateGL();
}


void CAViewer::specialKeyPressed(int key, int x, int y)
{
	bool handled = false;

	if (glutGetModifiers()==GLUT_ACTIVE_SHIFT)
	{
		switch (key)
		{
		case GLUT_KEY_UP:
			m_target.y += 1;
			handled=true;
			break;
		case GLUT_KEY_DOWN:
			m_target.y -= 1;
			handled=true;
			break;
		case GLUT_KEY_LEFT:
			m_target.x -= 1;
			handled=true;
			break;
		case GLUT_KEY_RIGHT:
			m_target.x += 1;
			handled=true;
			break;
		case GLUT_KEY_PAGE_UP:
			m_target.z += 1;
			handled=true;
			break;
		case GLUT_KEY_PAGE_DOWN:
			m_target.z -= 1;
			handled=true;
			break;
		}
	}


	if (!handled)
	{
        Viewer::specialKeyPressed(key,x,y);
	}
	updateGL();
}



void CAViewer::animate()
{
	//for (int i=0; i< 100; i++)
		water.ShallowWaterStep();
		
}



