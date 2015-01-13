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



#ifndef _VIEWER_H
#define _VIEWER_H

#include <iostream>
#include <cassert>

#include <GL/glew.h>

#include <oglplus/all.hpp>
#include <oglplus/shapes/cube.hpp>

#include <Camera.h>


extern const std::string SHADER_PATH;


class Viewer
{
public:
    Viewer();
	virtual ~Viewer ();
	virtual void draw();
	virtual void init();
	virtual void animate();
	virtual void keyPressed(unsigned char key, int x, int y);
	virtual void specialKeyPressed(int key, int x, int y);
	virtual void processMouse(int button, int state, int x, int y);
	virtual void processActiveMotion(int x, int y);
	virtual void updateGL();
	virtual void help();
    virtual void resize(GLsizei Width, GLsizei Height);

protected :

    Camera m_cam;
	bool bLight;           // lighting on/off
	bool bAxe;		// draw Axe X,Y,Z
	bool bGrid;		// draw Grid
	bool bBlend;
	bool bWireframe;
	bool bAnimate;
	GLfloat LightPosition[4];


    oglplus::Context gl;
    oglplus::VertexShader vs;
    oglplus::FragmentShader fs;
    oglplus::Program prog;

    oglplus::VertexArray axis;
    oglplus::Buffer axis_vert;
    oglplus::Buffer axis_color;


    oglplus::shapes::Cube make_cube;                     // helper object building cube vertex attributes
    oglplus::shapes::DrawingInstructions cube_instr;     // helper object encapsulating cube drawing instructions
    oglplus::shapes::Cube::IndexArray cube_indices;      // indices pointing to cube primitive elements
    oglplus::VertexArray cube;
    oglplus::Buffer cube_verts;
    oglplus::Buffer cube_normals;
    oglplus::Buffer cube_texcoords;

private:
    static Viewer* theViewer;
public:
    // ******************************************************************************
    static inline void GLInit(GLsizei Width, GLsizei Height);
    static inline void GLUpdate(void);
    static inline void GLKeyPressed(unsigned char key, int x, int y);
    static inline void GLSpecialKeyPressed(int key, int x, int y);
    static inline void GLProcessMouse(int button, int state, int x, int y);
    static inline void GLProcessMouseActiveMotion(int x, int y);
    static inline void GLProcessMousePassiveMotion(int x, int y);
    static inline void GLAnimate();
    static inline void GLResize(GLsizei Width, GLsizei Height);
    // *********************************************************************************************************

};



// ******************************************************************************
inline void Viewer::GLInit(GLsizei Width, GLsizei Height)
{
    theViewer->init();
}
inline void Viewer::GLUpdate(void)
{
    theViewer->updateGL();
}
inline void Viewer::GLKeyPressed(unsigned char key, int x, int y)
{
    theViewer->keyPressed(key,x,y);
}
inline void Viewer::GLSpecialKeyPressed(int key, int x, int y)
{
    theViewer->specialKeyPressed(key,x,y);
}
inline void Viewer::GLProcessMouse(int button, int state, int x, int y)
{
    theViewer->processMouse(button,state,x,y);
}
inline void Viewer::GLProcessMouseActiveMotion(int x, int y)
{
    theViewer->processActiveMotion(x,y);
    theViewer->updateGL();
}
inline void Viewer::GLProcessMousePassiveMotion(int x, int y)
{
    theViewer->updateGL();
}
inline void Viewer::GLAnimate()
{
    theViewer->animate();
}
inline void Viewer::GLResize(GLsizei Width, GLsizei Height)
{
    theViewer->resize(Width,Height);
//    if (Height==0) Height=1;

//    glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(40.0f,(GLfloat)Width/(GLfloat)Height,1.f,10000.0f);

//    glMatrixMode(GL_MODELVIEW);
}
// *********************************************************************************************************

#endif
