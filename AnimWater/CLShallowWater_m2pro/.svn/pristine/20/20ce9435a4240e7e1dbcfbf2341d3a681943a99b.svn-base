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

#include "Viewer.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>



using namespace std;
using namespace oglplus;

// Code ASCII
#define ESCAPE 27
#define PAGE_UP 73
#define PAGE_DOWN 81
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77



#if _WIN32
    const std::string SHADER_PATH = "D:\\alex\\src\\CLShallowWater_m2pro\\src\\";
#else
    //const std::string SHADER_PATH = "/home/alex/src/CLShallowWater/src/";
    const std::string SHADER_PATH = "/home/pers/alexandre.meyer/src/CLShallowWater/src/";
#endif


Viewer* Viewer::theViewer = NULL;




Viewer::Viewer() :
        cube_instr(make_cube.Instructions()),
        cube_indices(make_cube.Indices()),
        bLight(true), bAxe(true), bGrid(true), bBlend(false), bWireframe(false), bAnimate(false)
{
    theViewer = this;
}





Viewer::~Viewer()
{
}


void Viewer::help()
{
	printf("\n\nCamera :\n");
	printf("   Fleches+pageup+pagedown : bouge la camera\n");
	printf("   Ctrl+Fleches ou souris+bouton gauche: tourne la camera\n");
	printf("   Souris+bouton droit : avance/recule la camera\n");
	printf("   i : reinitialise la camera\n");
	printf("Lumiere : \n");
	printf("    alt+fleches ou pageup,pagedown : bouge la mumière\n");
	printf("Touches : \n");
	printf("   a : dessine les axes\n");
	printf("   b : active blend(transparence)\n");
	printf("   f : camera Fly or Trackball\n");
	printf("   l : active la lumiere\n");
	printf("   z : animation\n");
	printf("   w : wireframe\n");
    printf("-------------------------------------------------\n");
    cout<<endl;
}



void Viewer::init()
{
    LightPosition[0] = 2.0f;
    LightPosition[1] = 2.0f;
    LightPosition[2] = 2.0f;
	LightPosition[3] = 1.0f;


    // *************************** OPENGL SHADER *************************
    try
    {
        gl.ClearColor(0.6f, 0.8f, 0.9f, 1.0f);
        gl.ClearDepth(1.0f);
        gl.Enable(Capability::DepthTest);
        //gl.Enable(Capability::CullFace);

        // Set the vertex shader source
        vs.Source( GLSLSource::FromFile(SHADER_PATH+"vertex.glsl") );
        // compile it
        vs.Compile();

        // set the fragment shader source
        fs.Source( GLSLSource::FromFile(SHADER_PATH+"fragment.glsl") );
        // compile it
        fs.Compile();

        // attach the shaders to the program
        prog.AttachShader(vs);
        prog.AttachShader(fs);
        // link and use it
        prog.Link();
        prog.Use();

        cout<<"Vertex, Fragment Shader: ok"<<endl;

        // ******************* AXIS bind the VAO for the triangle *******************
        axis.Bind();

        // bind the VBO
        axis_vert.Bind(Buffer::Target::Array);
        {
            GLfloat axis_lines[3*6] = {
                0.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f
            };
            // upload the data
            Buffer::Data(  Buffer::Target::Array, 3*6,     axis_lines    );
            // setup the vertex attribs array for the vertices
            VertexAttribArray vert_attr(prog, "Position");
            vert_attr.Setup(3, DataType::Float);
            vert_attr.Enable();
        }

        // bind the VBO for AXIS
        axis_color.Bind(Buffer::Target::Array);
        {
            GLfloat axis_line_color[3*6] = {
                1.0f, 0.0f, 0.0f,
                1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 1.0f
            };
            // upload the data
            Buffer::Data( Buffer::Target::Array, 3*6, axis_line_color );
            // setup the vertex attribs array for the vertices
            VertexAttribArray color_attr(prog, "Color");
            color_attr.Setup(3, DataType::Float);
            color_attr.Enable();
        }

        // ******************* bind the VAO for the cube ****************************
        cube.Bind();

        // bind the VBO for the cube vertices
        cube_verts.Bind(Buffer::Target::Array);
        {
            std::vector<GLfloat> data;
            GLuint n_per_vertex = make_cube.Positions(data);
            // upload the data
            Buffer::Data(Buffer::Target::Array, data);
            // setup the vertex attribs array for the vertices
            VertexAttribArray attr(prog, "Position");
            attr.Setup(n_per_vertex, DataType::Float);
            attr.Enable();
        }

        cube_normals.Bind(Buffer::Target::Array);
        {
            std::vector<GLfloat> data;
            GLuint n_per_vertex = make_cube.Normals(data);
            // upload the data
            Buffer::Data(Buffer::Target::Array, data);
            // setup the vertex attribs array for the vertices
            VertexAttribArray attr(prog, "Normal");
            attr.Setup(n_per_vertex, DataType::Float);
            attr.Enable();
        }

        // bind the VBO for the cube texture-coordinates
//        cube_texcoords.Bind(Buffer::Target::Array);
//        {
//            std::vector<GLfloat> data;
//            GLuint n_per_vertex = make_cube.TexCoordinates(data);
//            // upload the data
//            Buffer::Data(Buffer::Target::Array, data);
//            // setup the vertex attribs array for the vertices
//            VertexAttribArray attr(prog, "TexCoord");
//            attr.Setup(n_per_vertex, DataType::Float);
//            attr.Enable();
//        }

    }
//    catch( int i) {}
    catch(oglplus::ProgramBuildError& pbe)
    {
        std::cout <<
            "Program build error (in " <<
            pbe.GLSymbol() << ", " <<
            pbe.ClassName() << " '" <<
            pbe.ObjectDescription() << "'): " <<
            pbe.what() << std::endl <<
            pbe.Log() << std::endl;
        pbe.Cleanup();
        assert(0);
    }
    catch(oglplus::Error& err)
    {
        std::cout <<
            "GL error (in " << err.GLSymbol() << ", " <<
            err.ClassName() << ": '" <<
            err.ObjectDescription() << "'): " <<
            err.what() <<
            " [" << err.File() << ":" << err.Line() << "] ";
        std::cerr << std::endl;
        err.Cleanup();
        assert(0);
    }
    catch(const std::exception& se)
    {
        std::cout <<
            "General error: " <<
            se.what() << std::endl;
        assert(0);
    }

    help();
}



void Viewer::resize(GLsizei width, GLsizei height)
{
    cout<<"Viewer::resize: init perspective matrix"<<endl;
    gl.Viewport(width, height);
    prog.Use();
    Uniform<Mat4f>(prog, "ProjectionMatrix").Set(
        CamMatrixf::PerspectiveY(
                                        Degrees(40),
                                        GLfloat(width)/height,
                                        1, 10000.f
                                 )
        );
}



void Viewer::updateGL()
{
    gl.Clear().ColorBuffer().DepthBuffer();

    prog.Use();

    //cout<<"cam: Rup="<<m_cam.getRotUp()<<" Rleft="<<m_cam.getRotLeft()<<" pos="<<m_cam.getPos()<<endl;
    if (m_cam.getFlyOrTrackball()==CAMERA_FLY)
        Uniform<Mat4f>(prog, "CameraMatrix").Set(
                        ModelMatrixf::RotationX( oglplus::Degrees(m_cam.getRotUp()) ) *
                        ModelMatrixf::RotationY( oglplus::Degrees(m_cam.getRotLeft())) *
                        ModelMatrixf::Translation(-m_cam.getPos().x, -m_cam.getPos().y, -m_cam.getPos().z)
                        );
    else
        Uniform<Mat4f>(prog, "CameraMatrix").Set(
                        ModelMatrixf::Translation(-m_cam.getPos().x, -m_cam.getPos().y, -m_cam.getPos().z) *
                        ModelMatrixf::RotationX( oglplus::Degrees(m_cam.getRotUp()) ) *
                        ModelMatrixf::RotationY( oglplus::Degrees(m_cam.getRotLeft()))
                        );

    Uniform<Vec3f>(prog, "LightPos").Set( Vec3f(LightPosition[0],LightPosition[1],LightPosition[2]) );

    if (bAxe)
    {
        axis.Bind();
        Uniform<int>(prog, "NormalType").Set(0);
        Uniform<Mat4f>(prog, "ModelMatrix").Set( ModelMatrixf::Translation( 0,0,0)  );
        gl.DrawArrays(PrimitiveType::Lines, 0, 6);
    }

    cube.Bind();
    Uniform<int>(prog, "NormalType").Set(1);
    Uniform<Mat4f>(prog, "ModelMatrix").Set( ModelMatrixf::Translation( LightPosition[0],LightPosition[1],LightPosition[2]) );
    cube_instr.Draw(cube_indices);

//    cube.Bind();
//    Uniform<Mat4f>(prog, "ModelMatrix").Set( ModelMatrixf::Translation( 3,0,0) );
//    cube_instr.Draw(cube_indices);

	draw();

	// since this is double buffered, swap the buffers to display what just got drawn.
	glutSwapBuffers();
}



void Viewer::keyPressed(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	case ESCAPE: // termine
		exit(1);
		break;

	case 'h':
	case 'H':
		help();
		break;

	case 'g':
	case 'G':
		bGrid = !bGrid;
		break;

	case 'a':
	case 'A':
		bAxe = !bAxe;
		break;

	case 'z':
	case 'Z':
		bAnimate = !bAnimate;
		break;

	case 'f':
	case 'F':
        if  (m_cam.getFlyOrTrackball()==CAMERA_TRACKBALL)
            m_cam.setFlyTrackballMode(CAMERA_FLY);
		else
            m_cam.setFlyTrackballMode(CAMERA_TRACKBALL);
        printf("Camera fly or trackball : %d\n", m_cam.getFlyOrTrackball());
		break;

	case 'I':
		LightPosition[0] = 5.0f;
		LightPosition[1] = 15.0f;
		LightPosition[2] = 5.0f;
		break;
	case 'i':
        m_cam = Camera();
		break;

	case 'w':
	case 'W':
		bWireframe = !bWireframe;
		if (bWireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		printf("wireframe=%d\n", bWireframe);
		break;

	case 'b':
	case 'B': // switch the blending
		//~ printf("B/b pressed; blending is: %d\n", bBlend);
		bBlend = bBlend ? 0 : 1;              // switch the current value of blend, between 0 and 1.
		if (bBlend)
		{
			glEnable(GL_BLEND);
			glEnable(GL_ALPHA_TEST) ;
		}
		else
		{
			glDisable(GL_BLEND);
			glDisable(GL_ALPHA_TEST);
		}
		printf("Blending is now: %d\n", bBlend);
		break;

	case 'l':
	case 'L': // switch the lighting
		//~ printf("L/l pressed; lighting is: %d\n", bLight);
		bLight = bLight ? 0 : 1;              // switch the current value of light, between 0 and 1.
		if (bLight)
		{
			glEnable(GL_LIGHTING);
		}
		else
		{
			glDisable(GL_LIGHTING);
		}
		printf("Lighting is now: %d\n", bLight);
		break;

	default:
		printf ("Key %d pressed. No action there yet.\n", key);
		break;
	}
	updateGL();
}


void Viewer::specialKeyPressed(int key, int x, int y)
{
	const float stepR=2;
	const int stepL=1;

	if (glutGetModifiers()==GLUT_ACTIVE_CTRL)
	{
		switch (key)
		{
		case GLUT_KEY_UP:
            m_cam.turnUpDown( -stepR);
			break;

		case GLUT_KEY_DOWN:
            m_cam.turnUpDown( stepR);
			break;

		case GLUT_KEY_LEFT:
            m_cam.turnLeftRight( -stepR);
			break;

		case GLUT_KEY_RIGHT:
            m_cam.turnLeftRight( stepR);
			break;
		}
	}
	else
		if (glutGetModifiers()==GLUT_ACTIVE_ALT)
		{
			switch (key)
			{
			case GLUT_KEY_UP:
                LightPosition[2] -= stepL;
				break;

			case GLUT_KEY_DOWN:
                LightPosition[2] += stepL;
				break;

			case GLUT_KEY_LEFT:
                LightPosition[0] -= stepL;
				break;

			case GLUT_KEY_RIGHT:
                LightPosition[0] += stepL;
				break;

			case GLUT_KEY_PAGE_UP:
				LightPosition[1] += stepL;
				break;

			case GLUT_KEY_PAGE_DOWN:
				LightPosition[1] -= stepL;
				break;
			}
			printf("Light position= %f %f %f\n", LightPosition[0], LightPosition[1], LightPosition[2]);
		}
		else
		{
			switch (key)
			{
			case GLUT_KEY_PAGE_UP:
                m_cam.translate( UP);
				break;

			case GLUT_KEY_PAGE_DOWN:
                m_cam.translate( DOWN);
				break;
			case GLUT_KEY_UP:
                m_cam.translate( FRONT);
				break;

			case GLUT_KEY_DOWN:
                m_cam.translate( BACK);
				break;

			case GLUT_KEY_LEFT:
                m_cam.translate( LEFT);
				break;

			case GLUT_KEY_RIGHT:
                m_cam.translate( RIGHT);
				break;
			default:
				break;
			}
		}
		updateGL();
}



void Viewer::animate()
{
}


void Viewer::processMouse(int button, int state, int x, int y)
{
	int specialKey;
	specialKey = glutGetModifiers();

    m_cam.startMove( CAMERA_STOP, x, y);

	if ((state == GLUT_DOWN)) // && (specialKey == GLUT_ACTIVE_ALT))
	{
		if (button == GLUT_LEFT_BUTTON)
		{
            m_cam.startMove( CAMERA_ROTATION, x, y);
		}
		else if (button == GLUT_RIGHT_BUTTON)
		{
            m_cam.startMove( CAMERA_TRANSLATION, x, y);
		}
	}
	//updateGL();
}

void Viewer::processActiveMotion(int x, int y)
{
    m_cam.move( x, y);
	//updateGL();
}


void Viewer::draw()
{

}





