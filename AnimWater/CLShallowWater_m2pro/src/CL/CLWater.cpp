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

#include <CLWater.h>
#include <cassert>

#include <oglplus/images/newton.hpp>
#include <oglplus/images/cloud.hpp>
#include <CL/cl_gl.h>

#include <GL/gl.h>

#if _WIN32
#include <Windows.h>
#else
#include <GL/glx.h>
#include <X11/X.h>
#endif

using namespace std;
using namespace oglplus;


namespace clwater
{


#if _WIN32
    const std::string CL_SHADER_PATH = "D:\\alex\\src\\CLShallowWater_m2pro\\src\\";
#else
	//const std::string CL_SHADER_PATH = "/home/alex/src/CLShallowWater/src/";
	const std::string CL_SHADER_PATH = "/home/pers/alexandre.meyer/src/CLShallowWater/src/";
#endif


inline float frand(const float min, const float max)
{
	return min + ((static_cast<float>(rand())/RAND_MAX)*(max-min));
}






CLWater::CLWater(oglplus::Context _gl, oglplus::Program& _prog) :
        gl(_gl),
        prog( _prog),
        grid_side(128),
        make_plane(
            Vec3f(0.0f, 0.0f, 0.0f),
            Vec3f(9.0f, 0.0f, 0.0f),
            Vec3f(0.0f, 0.0f,-9.0f),
            grid_side*3, grid_side*3
           ),
        plane_instr(make_plane.Instructions()),
        plane_indices(make_plane.Indices())
{
}

CLWater::~CLWater()
{

}




int CLWater::init()
{
    cl_int err;

    cout<<"CLWater::init()..."<<endl;






    // ******************** CL PLATFORM *****************************
    // Platform info
    cl_platform_id platform_id = NULL;
    cl_platform_id* platform_ids;
    cl_uint num_platforms;

    cout << "Getting Platform Information"<<endl;
    err = clGetPlatformIDs( 0, NULL, &num_platforms);
    CHECK_OPENCL_ERROR( err, "Platform::get() failed");

    platform_ids = new cl_platform_id[num_platforms];
    err = clGetPlatformIDs( num_platforms, platform_ids, NULL);
    CHECK_OPENCL_ERROR( err, "Platform::get() failed");

    char vendor[256];
    size_t size;
    cout<<"OPENCL number of plaforms="<<num_platforms<<endl;
    for(unsigned int i=0;i<num_platforms;++i)
    {
        err = clGetPlatformInfo( platform_ids[i], CL_PLATFORM_VENDOR, 0, NULL, &size );
        CHECK_OPENCL_ERROR( err, "Platform::getInfo() failed");
        err = clGetPlatformInfo( platform_ids[i], CL_PLATFORM_VENDOR, size, vendor, NULL );
        CHECK_OPENCL_ERROR( err, "Platform::getInfo() failed");
        cout<<"Available platform: "<<vendor<<endl;

        //if (strcmp(vendor, "Advanced Micro Devices, Inc.")==0) platform_id = platform_ids[i];
        if (strcmp(vendor, "NVIDIA Corporation")==0) platform_id = platform_ids[i];
    }
    err = clGetPlatformInfo( platform_id, CL_PLATFORM_VENDOR, 0, NULL, &size );
    err = clGetPlatformInfo( platform_id, CL_PLATFORM_VENDOR, size, vendor, NULL );
    CHECK_OPENCL_ERROR( err, "Platform::getInfo() failed");
    cout<<"Used platform: "<<vendor<<" ";
    err = clGetPlatformInfo( platform_id, CL_PLATFORM_VERSION, 0, NULL, &size );
    err = clGetPlatformInfo( platform_id, CL_PLATFORM_VERSION, size, vendor, NULL );
    CHECK_OPENCL_ERROR( err, "Platform::getInfo() failed");
    cout<<"version="<<vendor<<endl;




    // ******************** CL DEVICE *****************************
    cl_uint ret_num_devices;
    err = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &m_device, &ret_num_devices);
    CHECK_OPENCL_ERROR( err, "Device failed");



    // ******************** CL CONTEXT *****************************
	// Create CL context properties, add WGL context & handle to DC 
#if _WIN32
	cl_context_properties properties[] = { 
		CL_GL_CONTEXT_KHR,   (cl_context_properties)wglGetCurrentContext(), // WGL Context 
		CL_WGL_HDC_KHR,      (cl_context_properties)wglGetCurrentDC(),      // WGL HDC
		CL_CONTEXT_PLATFORM, (cl_context_properties)platform_id,               // OpenCL platform
		0
	};
#else
    cl_context_properties properties[] = {
        CL_GL_CONTEXT_KHR, (cl_context_properties)glXGetCurrentContext(), // GLX Context
        CL_GLX_DISPLAY_KHR, (cl_context_properties)glXGetCurrentDisplay(), // GLX Display
        CL_CONTEXT_PLATFORM, (cl_context_properties)platform_id, 0
    };
#endif
	m_context = clCreateContextFromType( properties, CL_DEVICE_TYPE_GPU, NULL, NULL, &err);
	CHECK_OPENCL_ERROR( err, "Context failed");






	// ********************************** GL *************************
	// bind the VAO for the plane
	plane.Bind();

	// bind the VBO for the plane vertices
	verts.Bind(Buffer::Target::Array);
	{
		std::vector<GLfloat> data;
		GLuint n_per_vertex = make_plane.Positions(data);
		// upload the data
		Buffer::Data(Buffer::Target::Array, data);
		// setup the vertex attribs array for the vertices
		VertexAttribArray attr(prog, "Position");
		attr.Setup(n_per_vertex, DataType::Float);
		attr.Enable();
	}

	// bind the VBO for the plane texture coordinates
	texcoords.Bind(Buffer::Target::Array);
	{
		std::vector<GLfloat> data;
		GLuint n_per_vertex = make_plane.TexCoordinates(data);
		// upload the data
		Buffer::Data(Buffer::Target::Array, data);
		// setup the vertex attribs array for the vertices
		VertexAttribArray attr(prog, "TexCoord");
		attr.Setup(n_per_vertex, DataType::Float);
		attr.Enable();
	}

	// setup the texture
	oglplus::Texture::Target tex_tgt = Texture::Target::_2D;
	tex.Bind(Texture::Target::_2D);
	{
		GLfloat *data = new GLfloat[ grid_side*grid_side ];
		int c=0;
		for(int i=0;i<grid_side;++i)
			for(int j=0;j<grid_side;++j)
			{
                data[c] = 0.f; //-0.5f*cos( 0.2f*sqrtf(i*i+j*j) );          // de toute facon le kernel OpenCL va initialiser la texture à 0
				++c;
			}
        Texture::Image2D(tex_tgt, 0, oglplus::PixelDataInternalFormat::R32F, grid_side, grid_side, 0, oglplus::PixelDataFormat::Red, oglplus::PixelDataType::Float, data);
        //Texture::Image2D(tex_tgt, 0, oglplus::PixelDataInternalFormat::RGBA, grid_side, grid_side, 0, oglplus::PixelDataFormat::RGBA, oglplus::PixelDataType::UnsignedByte, data);
        Texture::MinFilter(tex_tgt, TextureMinFilter::Linear);
        Texture::MagFilter(tex_tgt, TextureMagFilter::Linear);
        Texture::WrapS(tex_tgt, TextureWrap::MirroredRepeat);
        Texture::WrapT(tex_tgt, TextureWrap::MirroredRepeat);
	}
	//
	UniformSampler(prog, "TexUnit").Set(0);

	gl.FrontFace(make_plane.FaceWinding());




    // ******************** CL PROGRAMM: compile *****************************
    cout << "Loading and compiling CL source..."<<endl;
    streamsdk::SDKFile file;
    if (!file.open( (CL_SHADER_PATH+"CLWater.cl").c_str() ))
    {
        cout << "!!!ERROR: load CL source code"<<endl;
		assert( 0 );
        exit(1);
    }

    // Create a program from the kernel source
    const char *code = file.source().data();
    m_program = clCreateProgramWithSource( m_context, 1, (const char **)&code, NULL, &err);
    CHECK_OPENCL_ERROR( err, "Program failed");

    // Build the program
    err = clBuildProgram( m_program, 1, &m_device, NULL, NULL, NULL);
    char log[1024*128];
    if (err != CL_SUCCESS)
	{
		if(err == CL_BUILD_PROGRAM_FAILURE)
		{
			size_t log_size;
			err = clGetProgramBuildInfo( m_program, m_device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
			err = clGetProgramBuildInfo( m_program, m_device, CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
			cout << " \n\t\t\tBUILD LOG"<<endl;
			cout << " ************************************************"<<endl;
			cout << log << endl;
			cout << " ************************************************"<<endl;
		}
	    cout << "Program::build() failed (" << err << ")"<<endl;
		assert(0);
	    exit(1);
	}
	cout << "Loading and compiling CL source...OK"<<endl;

	// *** Command Queue and Kernel ****************
	m_queue = clCreateCommandQueue( m_context, m_device, 0, &err);
	CHECK_OPENCL_ERROR( err, "create queue");
    m_kernelShallowWater = clCreateKernel(m_program, "shallowWater", &err);
	CHECK_OPENCL_ERROR( err, "Kernel::Kernel() failed");
    m_kernelShallowWaterInit = clCreateKernel(m_program, "shallowWaterInit", &err);
    CHECK_OPENCL_ERROR( err, "Kernel::Kernel() failed");


    // *********************** DATA for SIMULATION  ****************************
	int i;
    m_dt = 0.1f;
    m_nComputation=0;
    m_nComputationEvery = 100;
    m_clLocalWorkSize = 16;


    // **** DENSITY MAP
    m_densityDim = 128;
    m_D0 = 0;
    m_D0 = clCreateFromGLTexture2D ( m_context, CL_MEM_READ_WRITE, GL_TEXTURE_2D, 0, tex.name(), &err);                 // OpenCL 1.1
    //m_D0 = clCreateBuffer( m_context, CL_MEM_READ_WRITE, sizeof(cl_float)*m_densityDim*m_densityDim, 0, &err);        // OpenCL 1.2
    CHECK_OPENCL_ERROR( err, "clCreateBuffer failed. (density)");
    cout<<"CLWater::init: clCreateFromGLTexture2D OK"<<endl;

    // *** DENSITY MAP INIT by calling a kernel ***
    glFlush();
    glFinish();
    err = clFlush( m_queue);
    err = clFinish(m_queue);
    CHECK_OPENCL_ERROR(err, "Event::wait() failed");

    err = clEnqueueAcquireGLObjects(m_queue, 1, &m_D0, 0, 0, 0);
    CHECK_OPENCL_ERROR(err, "clEnqueueAcquireGLObjects failed. ");

    err  |= clSetKernelArg( m_kernelShallowWaterInit, 0, sizeof(m_densityDim), (void*)&m_densityDim);
    CHECK_OPENCL_ERROR( err, "Kernel::setArg() failed");
    err  |= clSetKernelArg( m_kernelShallowWaterInit, 1, sizeof(m_D0), (void*)&m_D0);
    CHECK_OPENCL_ERROR( err, "Kernel::setArg() failed");

    cl_uint workDim = 2;
    const size_t localWorkSize[] = {m_clLocalWorkSize, m_clLocalWorkSize};
    const size_t globalWorkSize[] = { static_cast<size_t>(m_densityDim), static_cast<size_t>(m_densityDim) };
    err = clEnqueueNDRangeKernel (m_queue, m_kernelShallowWaterInit, workDim, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(err, "CommandQueue::enqueueNDRangeKernel() failed");

    err = clFlush( m_queue);
    err = clFinish(m_queue);
    CHECK_OPENCL_ERROR(err, "Event::wait() failed");

    //// Release ownership of GL texture for OpenCL Image
    err = clEnqueueReleaseGLObjects(m_queue, 1, &m_D0, 0, 0, 0);
    CHECK_OPENCL_ERROR(err, "clEnqueueReleaseGLObjects failed. ");



    nIte = 0;

    cout<<"CLWater::init()...ok"<<endl;

    return 0;
}




int CLWater::draw()
{
    plane.Bind();
    tex.Bind(Texture::Target::_2D);
    Uniform<int>(prog, "NormalType").Set(2);
    Uniform<Mat4f>(prog, "ModelMatrix").Set( ModelMatrixf() );
    plane_instr.Draw(plane_indices);

    tex.Unbind(Texture::Target::_2D);
    plane.Unbind();

	return 0;
}



int CLWater::reset()
{
	cl_int err;

	nIte = 0;
	err = clFlush( m_queue);
	err |= clFinish( m_queue);
    err |= clReleaseKernel( m_kernelShallowWater);
    err |= clReleaseKernel( m_kernelShallowWaterInit);
    err |= clReleaseProgram( m_program);
	err |= clReleaseMemObject(m_D0);
	err |= clReleaseCommandQueue(m_queue);
	err |= clReleaseContext( m_context);
	CHECK_OPENCL_ERROR(err, "Release");

	err |= init();

	return err;
}


int CLWater::animate()
{
	cl_int err;

    glFlush();
    glFinish();
    err = clFlush( m_queue);
    err = clFinish(m_queue);
    CHECK_OPENCL_ERROR(err, "Event::wait() failed");

    // Normalement il faudarit faire ca d'abord (mais ca plante)
	err = clEnqueueAcquireGLObjects(m_queue, 1, &m_D0, 0, 0, 0);
    CHECK_OPENCL_ERROR(err, "clEnqueueAcquireGLObjects failed. ");

	++nIte;
    err  = clSetKernelArg(  m_kernelShallowWater, 0, sizeof(m_dt), (void*)&m_dt);
    CHECK_OPENCL_ERROR( err, "Kernel::setArg() failed");
    err  |= clSetKernelArg( m_kernelShallowWater, 1, sizeof(nIte), (void*)&nIte);
    CHECK_OPENCL_ERROR( err, "Kernel::setArg() failed");
    err  |= clSetKernelArg( m_kernelShallowWater, 2, sizeof(m_densityDim), (void*)&m_densityDim);
    CHECK_OPENCL_ERROR( err, "Kernel::setArg() failed");
    err  |= clSetKernelArg( m_kernelShallowWater, 3, sizeof(m_D0), (void*)&m_D0);
	CHECK_OPENCL_ERROR( err, "Kernel::setArg() failed");

    cl_uint workDim = 2;
    const size_t localWorkSize[] = {m_clLocalWorkSize, m_clLocalWorkSize};
    const size_t globalWorkSize[] = { static_cast<size_t>(m_densityDim), static_cast<size_t>(m_densityDim) };
    err = clEnqueueNDRangeKernel (m_queue, m_kernelShallowWater, workDim, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
    CHECK_OPENCL_ERROR(err, "CommandQueue::enqueueNDRangeKernel() failed");

	err = clFlush( m_queue);
	err = clFinish(m_queue);
	CHECK_OPENCL_ERROR(err, "Event::wait() failed");


    // Release ownership of GL texture for OpenCL Image
	err = clEnqueueReleaseGLObjects(m_queue, 1, &m_D0, 0, 0, 0);
    CHECK_OPENCL_ERROR(err, "clEnqueueReleaseGLObjects failed. ");

    //cout<<"animate done"<<endl;
	return 0;
}


void CLWater::performance(const int n)
{
	int i,j;

    cout<<"DensityMap dim="<<m_densityDim<<endl;
	m_clLocalWorkSize = 1;
	m_nComputationEvery = n;
	cout << fixed;
	double t;
    int jmax=5;
    for(j=0;j<=jmax;++j)
	{
		cout<<j+1<<"/"<<jmax<<" nIte="<<n<<" ";
		cout<<" m_clLocalWorkSize="<<m_clLocalWorkSize<<" ";

		m_nComputation=0;
		m_clock.start();
		for(i=0;i<n;++i) animate();
		m_clock.pause();
		t = m_clock.elapsedTime();
        cout<<"t="<<t<<"s => t/iteration="<<t/n<<endl;

		m_clLocalWorkSize *= 2;
	}
}



int CLWater::debug()
{

	return 0;
}


} // namespace
