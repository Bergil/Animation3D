/****************************************************************************
 Copyright (C) 2010-2013 Alexandre Meyer

 This file is part of CLWater.

 CLWater is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Sami is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Sami.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glew.h>
//#include <GL/gl.h>
//#include <GL/glu.h>

#include "CAViewer.h"
#include <Mat4.h>
#include <Quaternion.h>

#include <cstdio>
#include <cstdlib>
#include <iostream>



using namespace std;


void CAViewer::help()
{
    //	printf("Animation:\n");
    //	printf("   n : Next character pose\n");
    //	printf("   b : Previous character pose");
    //	printf("   p : Toggles physics");
    Viewer::help();
}


CAViewer::~CAViewer()
{
}



void CAViewer::init()
{
    Viewer::init();
    m_water.init();
}



void CAViewer::draw()
{
    glPushMatrix();

    m_water.draw();

    glPopMatrix();
}



void CAViewer::keyPressed(unsigned char key, int x, int y)
{
    bool handled = false;
    if (key=='w')
    {
        bWireframe = !bWireframe;
        if (bWireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        handled = true;
    }
    else if (key=='z')
    {
        animate();
        handled = true;
    }
    else if (key=='p')
    {
        m_water.performance();
        handled = true;
    }
    else if (key=='r')
    {
        m_water.reset();
        handled = true;
    }
    else if (key=='d')
    {
        m_water.debug();
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
    Viewer::specialKeyPressed(key,x,y);
}



void CAViewer::animate()
{
    m_water.animate();
}



