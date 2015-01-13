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
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <CAViewer.h>


int main(int argc, char **argv)
{
	int window;		// glut windows

	// Initialize GLUT
	glutInit(&argc, argv);

	/* Select type of Display mode:	 Double buffer	 RGBA color	 Depth buffer	 Alpha blending */
	//glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);
	//glutInitDisplayMode(GLUT_RGB);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// demande une fenetre de 640 x 480 à la position 0,0
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);

	// Creer une fenetre
    window = glutCreateWindow("GLUT GL4");
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		exit(1);
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    CAViewer Viewer;

	// La fonction d'affichage est GLDraw
    glutDisplayFunc(Viewer::GLUpdate);

	// Plein écran
	//glutFullScreen();

	// Quand il n'y a aucun évenement, on affiche quand même la scène
    //glutIdleFunc(CAViewer::GLAnimate);

	// Quand la fenetre change de taille
    glutReshapeFunc(Viewer::GLResize);

	// quand une touche est pressee
    glutKeyboardFunc(Viewer::GLKeyPressed);

	// quand une touche speciale est pressee
    glutSpecialFunc(Viewer::GLSpecialKeyPressed);

	// mouse
    glutMouseFunc(Viewer::GLProcessMouse);
    glutMotionFunc(Viewer::GLProcessMouseActiveMotion);
    glutPassiveMotionFunc(Viewer::GLProcessMousePassiveMotion);
    //    glutEntryFunc(Viewer::processMouseEntry);

    // init
    Viewer::GLInit(640, 480);

	// La boucle principale
	glutMainLoop();

	return 0;
}













#if 0


/** 
  OpenGL 3.3 / OpenCL 1.1 texture sharing
  - need a platform/device supporting gl_sharing_khr extension
*/

//#define BUILD_WINDOWS
#define BUILD_UNIX

#ifdef BUILD_UNIX
  //#define GL_GLEXT_PROTOTYPES
  #include <GL/glew.h>
  #include <GL/gl.h> // need a recent glext.h checkout the one on the khronos registry
  #include <GL/glx.h>
  #include <X11/Xlib.h>
#endif

#ifdef BUILD_WINDOWS
  #include <windows.h>
  #include <GL/glew.h> // need glex 1.5.5
#endif

#include <GL/glut.h> // available for many platforms

#include <CL/cl.h>     // Need an OpenCL SDK (from nVidia or AMD). .h can be downloaded on khronos registry.
#include <CL/cl_gl.h>

#include <string>
#include <iostream>

// Glut callback
void display();
void reshape(int width, int height); ///< windows size changes
void idle();

// initialization
void init_gl();
void init_cl();

// Destruction
void destroy_gl();
void destroy_cl();

//platform/device choice
bool use_this_cl_platform(cl_platform_id const & platform);
bool use_this_cl_device(cl_device_id const & device);

//error management
void print_cl_error ( cl_int code, std::string const & message );
void print_gl_error ();

size_t const TEXTURE_WIDTH = 1024;
size_t const TEXTURE_HEIGHT = 1024;
  

namespace gl
{
  GLuint positionBuffer = 0;
  GLuint texcoordBuffer = 0;
  GLuint texture = 0;
  GLuint vertexShader = 0;
  GLuint fragmentShader = 0;
  GLuint program = 0;
  GLuint vertexArray = 0;
  GLuint sampler = 0;
  
  float const positionData[] = { -1,-1,0, -1,1,0, 1,1,0, 1,-1,0 };
  float const texcoordData[] = { 0,0,   0,1,   1,1,   1,0   };
  
  //char const * const vertexShaderSrc = "\
  //  #version 330 core \n\
  //  \n\
  //  in Vertex{ \n\
  //    vec3 position; \n\
  //    vec2 texcoord; \n\
  //  } vertex; \n\
  //  \n\
  //  out vec2 texcoord; \n\
  //  \n\
  //  void main() \n\
  //  { \n\
  //    texcoord = vertex.texcoord; \n\
  //    gl_Position = vec4(vertex.position, 1); \n\
  //  } \n\
  //";
  char const * const vertexShaderSrc = "\
    #version 330 core \n\
    \n\
    \n\
    in vec3 vertexposition; \n\
    in vec2 vertextexcoord; \n\
    \n\
    \n\
    out vec2 texcoord; \n\
    \n\
    void main() \n\
    { \n\
      texcoord = vertextexcoord; \n\
      gl_Position = vec4(vertexposition, 1); \n\
    } \n\
  ";

  char const * const fragmentShaderSrc = "\
    #version 330 core \n\
    \n\
    uniform sampler2D texture; \n\
    \n\
    in vec2 texcoord; \n\
    \n\
    out vec4 fragColor; \n\
    \n\
    void main() \n\
    { \n\
      fragColor = texture2D( texture, texcoord ); \n\
    } \n\
  ";
  
  GLuint positionAttrib;
  GLuint texcoordAttrib;
  GLuint samplerLocation;
}

namespace cl
{
  cl_device_type const DEVICE_TYPE = CL_DEVICE_TYPE_GPU;
  cl_platform_id platform = 0;
  cl_device_id device = 0;
  cl_context context = 0;
  cl_mem texture = 0;
  cl_command_queue command_queue = 0;
  cl_program program = 0;
  cl_kernel kernel = 0;
  
  char const * programSrc = "\
   float m1_1_to_0_1( float val ) \n\
  { \n\
    return (val + 1.f ) / 2.f; \n\
  } \n\
  \n\
  __kernel void writeTexture( __write_only image2d_t image, float t ) \n\
  { \n\
    int2 coordi = (int2)( get_global_id(0), get_global_id(1) ); \n\
    float2 coordf = convert_float2(coordi) / (float2)( get_global_size(0), get_global_size(1) ); \n\
    float4 color = (float4)( \n\
      m1_1_to_0_1 ( cos( (coordf.x+0.5f) * 3.14f * 10.f ) * sin( coordf.y * 3.14f * 5.f ) * tan( (coordf.y * coordf.x) * 3.14f * 2.f + t ) ), \n\
     1.f -  m1_1_to_0_1 ( cos( (coordf.x+0.5f) * 3.14f * 10.f ) * sin( coordf.y * 3.14f * 5.f ) * tan( (coordf.y * coordf.x) * 3.14f * 2.f + t ) ), \n\
      0.f, \n\
      1.f \n\
    ); \n\
    \n\
    write_imagef( \n\
      image, \n\
      coordi, \n\
      color \n\
    );\n\
  } \n\
  ";
  
  char const * build_options = "";
  
  size_t const GLOBAL_WORK_SIZE[2] = {TEXTURE_WIDTH, TEXTURE_HEIGHT};
}

int main(int argc, char * argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL);
  
  glutCreateWindow("clgl_sharing");
  //glutSetOption( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS );
  
  glutDisplayFunc( display );
  glutReshapeFunc( reshape );
  glutIdleFunc( idle );
  
//#ifdef BUILD_WINDOWS
  glewInit();
//#endif
  
  init_gl();
  glFinish(); //Wait until all opengl commands are processed
  init_cl();
  
  glutMainLoop();
  
  destroy_gl();
  destroy_cl();
}

GLuint create_shader(GLenum type, char const * sources)
{
  GLuint shader = glCreateShader( type );  
  glShaderSource( shader, 1, &sources, NULL );
  glCompileShader( shader );
  
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  
  if( status == GL_FALSE )
  {
    GLint length;
    glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &length);
    GLchar * infoLog = new GLchar[length];
    glGetShaderInfoLog(	shader, length, NULL, infoLog);
    
    std::cout << "shader compilation log : " << infoLog << std::endl;
    
    delete[] infoLog;
  }
  
  return shader;
}

void init_gl()
{
  std::cout << "OpenGL version : " << glGetString(GL_VERSION) << std::endl;
  
// Buffers
  glGenBuffers(1, &gl::positionBuffer);
  glGenBuffers(1, &gl::texcoordBuffer);
  
  glBindBuffer( GL_ARRAY_BUFFER, gl::positionBuffer );
  glBufferData( GL_ARRAY_BUFFER, sizeof(gl::positionData), gl::positionData, GL_STATIC_DRAW );
  
  glBindBuffer( GL_ARRAY_BUFFER, gl::texcoordBuffer );
  glBufferData( GL_ARRAY_BUFFER, sizeof(gl::texcoordData), gl::texcoordData, GL_STATIC_DRAW );
 
  glBindBuffer( GL_ARRAY_BUFFER, 0 );
  
// Texture
  glActiveTexture( GL_TEXTURE0 );

  glGenTextures(1, &gl::texture);
  glBindTexture( GL_TEXTURE_2D, gl::texture );
  
  GLfloat * textureData = new GLfloat[TEXTURE_WIDTH * TEXTURE_HEIGHT];
  memset( textureData, 0, TEXTURE_WIDTH * TEXTURE_HEIGHT);
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, TEXTURE_WIDTH, TEXTURE_HEIGHT, 0, GL_RED, GL_FLOAT, textureData );
  delete textureData;
  glGenerateMipmap( GL_TEXTURE_2D );

  glBindTexture( GL_TEXTURE_2D, 0 );

  print_gl_error();

// Sampler
  glGenSamplers(1, &gl::sampler );
  glSamplerParameterf( gl::sampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
  glSamplerParameterf( gl::sampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST );  
  
// Shaders
  gl::vertexShader = create_shader( GL_VERTEX_SHADER, gl::vertexShaderSrc );
  gl::fragmentShader = create_shader( GL_FRAGMENT_SHADER, gl::fragmentShaderSrc );
  
  gl::program = glCreateProgram();
  
  glAttachShader( gl::program, gl::vertexShader );
  glAttachShader( gl::program, gl::fragmentShader );
  
  glLinkProgram( gl::program );
  
  GLint status;
  glGetProgramiv( gl::program, GL_LINK_STATUS, &status ); 
  
  if( status == GL_FALSE)
  {
    GLint length;
    glGetProgramiv( gl::program, GL_INFO_LOG_LENGTH, &length );
    
    GLchar * infoLog = new GLchar[length];
    
    glGetProgramInfoLog( gl::program, length, NULL, infoLog);

    std::cout << "shader link log : " << infoLog << std::endl;
  }
  
//Attribute
  gl::positionAttrib = glGetAttribLocation( gl::program, "Vertex.position" );
  gl::texcoordAttrib = glGetAttribLocation( gl::program, "Vertex.texcoord" );
  
// Uniform
  gl::samplerLocation = glGetUniformLocation( gl::program, "texture" );
  
  glUseProgram( gl::program );
  
  glUniform1i( gl::samplerLocation, 0 );
  
  glUseProgram( 0 );
  
// Vertex array
  glGenVertexArrays( 1, &gl::vertexArray );
   
  glBindVertexArray( gl::vertexArray );
  
  glBindBuffer( GL_ARRAY_BUFFER, gl::positionBuffer );
  glVertexAttribPointer( gl::positionAttrib, 3, GL_FLOAT, false, 0, 0);
  
  glBindBuffer( GL_ARRAY_BUFFER, gl::texcoordBuffer );
  glVertexAttribPointer( gl::texcoordAttrib, 2, GL_FLOAT, false, 0, 0);
  
  glEnableVertexAttribArray( gl::positionAttrib );
  glEnableVertexAttribArray( gl::texcoordAttrib );
  
  glBindBuffer( GL_ARRAY_BUFFER, 0 );
  
  glBindVertexArray( 0 );
  
  print_gl_error();
  return;
}

void destroy_gl()
{
  glDeleteBuffers( 1, &gl::positionBuffer );
  glDeleteBuffers( 1, &gl::texcoordBuffer );
  glDeleteTextures( 1, &gl::texture );

  glDeleteShader( gl::vertexShader );
  glDeleteShader( gl::fragmentShader );
  glDeleteProgram( gl::program );
  
  glDeleteVertexArrays( 1, &gl::vertexArray );
 
  glDeleteSamplers( 1, &gl::sampler );
   
  print_gl_error();
}

void init_cl()
{
  cl_int errcode_ret = 0;
    
//Platforms
  cl_uint num_platforms;
  cl_platform_id * platforms;
   	
  clGetPlatformIDs( 0, NULL, &num_platforms);
  
  platforms = new cl_platform_id[num_platforms];
   
  clGetPlatformIDs( num_platforms, platforms, NULL);
  
  std::cout << "OpenCL platforms & devices" << std::endl;
  
  for(size_t p=0; p<num_platforms; ++p)
  {
    char * version;
    size_t version_size;
    clGetPlatformInfo( platforms[p], CL_PLATFORM_VERSION, 0, NULL, &version_size);
    version = new char[ version_size ];
    clGetPlatformInfo( platforms[p], CL_PLATFORM_VERSION, version_size, version, NULL);
    
    std::cout << "\t* " << version << std::endl;
   
    bool use_this_platform = false;
    if( cl::platform == 0 && use_this_cl_platform( platforms[p] ) )
    {
      cl::platform = platforms[p];
      use_this_platform = true;
    }
    
//Devices
    cl_uint num_devices;
    cl_device_id *devices;
    clGetDeviceIDs( platforms[p], cl::DEVICE_TYPE, 0, NULL, &num_devices);
    devices = new cl_device_id[num_devices];
    clGetDeviceIDs( platforms[p], cl::DEVICE_TYPE, num_devices, devices, NULL);
    
    for(size_t d=0; d<num_devices; ++d)
    {
      size_t name_size;
      char * name;
      clGetDeviceInfo( devices[d], CL_DEVICE_NAME, 0, NULL, &name_size);
      name = new char[name_size];
      clGetDeviceInfo( devices[d], CL_DEVICE_NAME, name_size, name, NULL);
     
      bool use_this_device = false;
      if( use_this_platform && cl::device == 0 && use_this_cl_device( devices[d] ) )
      {
	cl::device = devices[d];
	use_this_device = true;
      }
      
      std::cout << "\t\t- " << name << (use_this_device ? " (will be used)" : "") << std::endl;
      delete[] name;
    }
    
    delete[] devices;
    delete[] version;
  }
  
  delete[] platforms;
  
  if( cl::platform == 0 )
  {
    std::cout << "no cl platform found with  cl_khr_gl_sharing extension" << std::endl;
    exit( 1 );
  }
  
  if( cl::device == 0 )
  {
    std::cout << "no cl device found with  cl_khr_gl_sharing extension" << std::endl;
    exit( 2 );
  }
  
//Context
#ifdef BUILD_UNIX
  Display * display = XOpenDisplay(NULL);
#endif

  cl_context_properties properties[] =
  {
    CL_CONTEXT_PLATFORM, reinterpret_cast<cl_context_properties>(cl::platform),
#ifdef BUILD_UNIX
    CL_GL_CONTEXT_KHR, reinterpret_cast<cl_context_properties>(glXGetCurrentContext()),
    CL_GLX_DISPLAY_KHR, reinterpret_cast<cl_context_properties>(display),
#endif
#ifdef BUILD_WINDOWS
    CL_GL_CONTEXT_KHR, reinterpret_cast<cl_context_properties>( wglGetCurrentContext() ),
    CL_WGL_HDC_KHR, reinterpret_cast<cl_context_properties>( wglGetCurrentDC() ),
#endif
    0
  };
  
  cl::context = clCreateContext( properties, 1, &cl::device, NULL, NULL, &errcode_ret);
  print_cl_error( errcode_ret, "clCreateContext" );
  
#ifdef BUILD_UNIX
  XCloseDisplay(display);
#endif
  
//Texture 2D
  cl::texture = clCreateFromGLTexture2D ( cl::context, CL_MEM_WRITE_ONLY, GL_TEXTURE_2D, 0, gl::texture, &errcode_ret);
  print_cl_error( errcode_ret, "clCreateFromGLTexture2D" );
 
//Command queue
  cl::command_queue = clCreateCommandQueue( cl::context, cl::device, 0, &errcode_ret); 
  print_cl_error( errcode_ret, "clCreateCommandQueue" );


#if 1
  int i;
  cl_int err;
  cl_float* m_Dinit = new cl_float[TEXTURE_WIDTH * TEXTURE_HEIGHT];
  for(i=0;i<TEXTURE_WIDTH * TEXTURE_HEIGHT;++i) m_Dinit[i]=0.f;

  glFlush();
  glFinish();
  clFlush(cl::command_queue);
  clFinish(cl::command_queue);
  // Acquire ownership of GL texture for OpenCL Image
  err = clEnqueueAcquireGLObjects(cl::command_queue, 1, &cl::texture, 0, 0, 0);
  print_cl_error( err, "alex clEnqueueAcquireGLObjects" );

  err = clEnqueueWriteBuffer( cl::command_queue, cl::texture, CL_TRUE, 0, TEXTURE_WIDTH * TEXTURE_HEIGHT, m_Dinit, 0, NULL, NULL);
  print_cl_error( err, "alex clEnqueueWriteBuffer" );

  err = clFlush(cl::command_queue);
  clFinish(cl::command_queue);
  glFlush();
  glFinish();

  // Release ownership of GL texture for OpenCL Image
  err = clEnqueueReleaseGLObjects(cl::command_queue, 0, &cl::texture, 0, 0, 0);
  print_cl_error( err, "alex clEnqueueReleaseGLObjects" );


#endif


//Program
  cl::program = clCreateProgramWithSource  ( cl::context, 1, &cl::programSrc, NULL, &errcode_ret);
  print_cl_error( errcode_ret, "clCreateProgramWithSource" );
    
  print_cl_error(
    clBuildProgram ( cl::program, 1, &cl::device, cl::build_options, NULL, NULL ),
    "clBuildProgram"
  );

  cl_build_status buildStatus;
  print_cl_error(
    clGetProgramBuildInfo ( cl::program, cl::device, CL_PROGRAM_BUILD_STATUS, sizeof( cl_build_status ), &buildStatus, NULL),
    "clGetProgramBuildInfo"
  );
  
  if( buildStatus != CL_BUILD_SUCCESS )
  {
    std::cout << "Build status : " << buildStatus << std::endl;
    char * log = NULL;
    size_t logSize;
    clGetProgramBuildInfo ( cl::program, cl::device, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
    log = new char[logSize];
    clGetProgramBuildInfo ( cl::program, cl::device, CL_PROGRAM_BUILD_LOG, logSize, log, NULL);
    
    std::cout << "Build log : " << log << std::endl;
    
    delete[] log;
  }
   
//Kernel
  cl::kernel = clCreateKernel( cl::program, "writeTexture", &errcode_ret);
  print_cl_error( errcode_ret, "clCreateKernel" );

  print_cl_error(
    clSetKernelArg( cl::kernel, 0, sizeof( cl_mem), &cl::texture ),
    "clCreateKernel"
  );
}

void destroy_cl()
{
  print_cl_error(
    clReleaseMemObject( cl::texture ),
    "clReleaseMemObject"
  );
  print_cl_error(
    clReleaseKernel( cl::kernel ),
    "clReleaseKernel"
  );
  print_cl_error(
    clReleaseProgram( cl::program ),
    "clReleaseProgram"
  );
  print_cl_error(
    clReleaseCommandQueue( cl::command_queue ),
    "clReleaseCommandQueue"
  );
  print_cl_error(
    clReleaseContext( cl::context ),
    "clReleaseContext"
  );
}

bool use_this_cl_platform(cl_platform_id const & platform)
{
  size_t extensions_size;
  char * extensions;
  
  print_cl_error(
    clGetPlatformInfo( platform, CL_PLATFORM_EXTENSIONS, 0, NULL, &extensions_size),
    "clGetPlatformInfo"
  );
  
  extensions = new char[extensions_size];
  
  print_cl_error(
    clGetPlatformInfo( platform, CL_PLATFORM_EXTENSIONS, extensions_size, extensions, NULL),
    "clGetPlatformInfo"
  );
  
  std::string ext = extensions;
  
  bool use_this_platform = ext.find("cl_khr_gl_sharing") != std::string::npos;
  
  delete[] extensions;
  
  return use_this_platform;
}

bool use_this_cl_device(cl_device_id const & device)
{
  size_t exensions_size;
  char * extensions;
  
  print_cl_error(
    clGetDeviceInfo( device, CL_DEVICE_EXTENSIONS, 0, NULL, &exensions_size),
    "clGetDeviceInfo"
  );

  extensions = new char[exensions_size];

  print_cl_error(
    clGetDeviceInfo( device, CL_DEVICE_EXTENSIONS, exensions_size, extensions, NULL),
    "clGetDeviceInfo"
  );
  
  std::string ext = extensions;
  
  bool use_this_device = ext.find("cl_khr_gl_sharing") != std::string::npos;
  
  delete[] extensions;
  
  return use_this_device;
}

void display()
{
  static float time = 0;
  time += 0.01f;

//OPENCL
//Acquire shared objects
  print_cl_error(
    clEnqueueAcquireGLObjects ( cl::command_queue, 1, &cl::texture, 0, NULL, NULL),
    "clEnqueueAcquireGLObjects"
  );
  
  print_cl_error(
    clSetKernelArg( cl::kernel, 1, sizeof( cl_float ), &time ),
    "clCreateKernel"
  );

//Run OpenCL
  print_cl_error(
    clEnqueueNDRangeKernel(
      cl::command_queue,
      cl::kernel,
      2,
      NULL, cl::GLOBAL_WORK_SIZE, NULL,
      0, NULL, NULL),
    "clEnqueueNDRangeKernel"
  );
 
//Release shared Objects
  print_cl_error(
    clEnqueueReleaseGLObjects ( cl::command_queue, 1, &cl::texture, 0, NULL, NULL),
    "clEnqueueReleaseGLObjects"
  );
  
//Wait until all OpenCL commands are processed
  print_cl_error(
    clFinish( cl::command_queue ),
    "clFinish"
  );

//OPENGL
  glClearColor(0.2, 0.4, 0.7,1.0);
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glUseProgram( gl::program );
  
  glActiveTexture( GL_TEXTURE0 + 0 );
  glBindTexture( GL_TEXTURE_2D, gl::texture );
  glBindSampler( 0, gl::sampler );
  
  glBindVertexArray( gl::vertexArray );
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  glBindVertexArray( 0 );
  
  glBindTexture( GL_TEXTURE_2D, 0 );
  
  glutSwapBuffers();  //After this all OpenGL commands are processed
  
  print_gl_error();
}

void idle()
{
  glutPostRedisplay();
}

void reshape(int width, int height)
{
  glViewport(0, 0, width, height);
}

void print_gl_error ()
{
  GLuint error = glGetError();
  if( error != 0 )
  {
    std::cout << "GL error : " << error << std::endl;
  }
}

void print_cl_error ( cl_int code, std::string const & message )
{
  if( code != 0)
  {
    std::cout << message << " : " << code << std::endl;
  }
}

#endif
