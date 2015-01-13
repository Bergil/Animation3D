/*
 *  .file oglplus/enums/color_buffer_range.ipp
 *
 *  Automatically generated header file. DO NOT modify manually,
 *  edit 'source/enums/color_buffer.txt' instead.
 *
 *  Copyright 2010-2012 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

OGLPLUS_LIB_FUNC aux::CastIterRange<
	const GLenum*,
	ColorBuffer
> EnumValueRange(ColorBuffer*)
OGLPLUS_NOEXCEPT(true)
#if OGLPLUS_LINK_LIBRARY && !defined(OGLPLUS_IMPLEMENTING_LIBRARY)
;
#else
{
static const GLenum _values[] = {
#if defined GL_NONE
GL_NONE,
#endif
#if defined GL_FRONT_LEFT
GL_FRONT_LEFT,
#endif
#if defined GL_FRONT_RIGHT
GL_FRONT_RIGHT,
#endif
#if defined GL_BACK_LEFT
GL_BACK_LEFT,
#endif
#if defined GL_BACK_RIGHT
GL_BACK_RIGHT,
#endif
#if defined GL_FRONT
GL_FRONT,
#endif
#if defined GL_BACK
GL_BACK,
#endif
#if defined GL_LEFT
GL_LEFT,
#endif
#if defined GL_RIGHT
GL_RIGHT,
#endif
#if defined GL_FRONT_AND_BACK
GL_FRONT_AND_BACK,
#endif
0
};
return aux::CastIterRange<
	const GLenum*,
	ColorBuffer
>(_values, _values+sizeof(_values)/sizeof(_values[0])-1);
}
#endif

