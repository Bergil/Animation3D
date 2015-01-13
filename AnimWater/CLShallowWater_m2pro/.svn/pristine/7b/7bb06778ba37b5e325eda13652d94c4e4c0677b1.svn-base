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

#ifndef _CLWATER_H
#define _CLWATER_H

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include <GL/glew.h>
#include <oglplus/all.hpp>
#include <oglplus/shapes/plane.hpp>

#define CL_USE_DEPRECATED_OPENCL_1_1_APIS
#include <SDKFile.hpp>
#include <SDKCommon.hpp>
#include <SDKApplication.hpp>

#include <CL/cl.h>

#include <Timer.h>


namespace clwater
{

class CLWater
{
public:
    CLWater(oglplus::Context _gl, oglplus::Program& _prog);
    ~CLWater();
    int init();
    int animate();
    int draw();
    int reset();
    int debug();
    void performance(const int n=200);

protected :
    // ************* CL
    cl_program m_program;
    cl_context m_context;
    cl_device_id* m_devices;
    cl_device_id m_device;
	cl_command_queue m_queue;
    cl_kernel m_kernelShallowWater;
    cl_kernel m_kernelShallowWaterInit;

    int nIte;

	float m_dt;					//!< \brief Integration time

    size_t m_clLocalWorkSize;
	int m_densityDim;			//!< \brief Dimension of the density map
	cl_mem m_D0;				//!< \brief Density map 0

    Timer m_clock;
    int m_nComputation;
    int m_nComputationEvery;


    // ************* GL
    oglplus::Context gl;
    oglplus::Program& prog;

    GLuint grid_side;
    oglplus::shapes::Plane make_plane;                       //!< helper object building plane vertex attributes
    oglplus::shapes::DrawingInstructions plane_instr;       //!< helper object encapsulating plane drawing instructions
    oglplus::shapes::Plane::IndexArray plane_indices;       //!< indices pointing to plane primitive elements
    oglplus::VertexArray plane;                             //!< A vertex array object for the rendered plane
    oglplus::Buffer verts, texcoords;                       //!< VBOs for the plane's vertex attributes
    oglplus::Texture tex;                                   //! the heightmap texture
};


} // namespace

#endif
