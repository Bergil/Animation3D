/**
 *  @file oglplus/images/sphere_bmap.hpp
 *  @brief Generator of a normal/depth map with "imprinted" sphere
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2010-2011 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef OGLPLUS_IMAGES_SPHERE_BMAP_1107121519_HPP
#define OGLPLUS_IMAGES_SPHERE_BMAP_1107121519_HPP

#include <oglplus/image.hpp>
#include <oglplus/texture.hpp>
#include <oglplus/vector.hpp>

#include <cassert>
#include <cmath>

namespace oglplus {
namespace images {

class SphereBumpMap
 : public Image<GLfloat>
{
public:
	SphereBumpMap(
		GLsizei width,
		GLsizei height,
		GLsizei xrep = 1,
		GLsizei yrep = 1
	): Image<GLfloat>(width, height, 1)
	{
		assert(width != 0 && height != 0);
		assert(xrep != 0 && yrep != 0);
		_data.resize(width*height*4);

		typedef double number;
		number one = number(1);
		number invw = (2.0f*xrep)/width;
		number invh = (2.0f*yrep)/height;
		GLsizei hi = number(width)/xrep;
		GLsizei hj = number(height)/yrep;

		auto p = _data.begin(), e = _data.end();
		for(GLsizei j=0; j!=height; ++j)
		{
			number y = number((j % hj) - hj/2)*invh;
			for(GLsizei i=0; i!=width; ++i)
			{
				number x = number((i % hi) - hi/2)*invw;
				number l = std::sqrt(x*x + y*y);
				number d = sqrt(one-l*l);
				Vector<number, 3> z(0.0, 0.0, one);
				Vector<number, 3> n(-x, -y, d);
				Vector<number, 3> v = (l >= one)?
					z:
					Normalized(z+n);
				if(l >= one) d = 0;
				assert(p != e);
				*p = v.x(); ++p;
				*p = v.y(); ++p;
				*p = v.z(); ++p;
				*p = d; ++p;
			}
		}
		OGLPLUS_FAKE_USE(e);
		assert(p == e);
		_type = PixelDataType::Float;
		_format = PixelDataFormat::RGBA;
		_internal = PixelDataInternalFormat::RGBA16F;
	}
};

} // images
} // oglplus

#endif // include guard