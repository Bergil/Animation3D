
PROJECT(CLShallowWater)

############################## LES OPTIONS
SET( CMAKE_BUILD_TYPE Debug)			# used only by make
#SET( CMAKE_BUILD_TYPE RelWithDebInfo)
#SET( CMAKE_BUILD_TYPE Release)



#si vous avez besoin de spéficiez le chemin vers GLUT
SET(GLUT_HOME 		"D:\\alex\\lib\\glut-3.7.6-bin")

IF(WIN32)
	SET(GLEW_HOME 		"D:\\alex\\lib\\glew-1.9.0")
ELSE(WIN32)
	SET(GLEW_HOME 		"/home/pers/alexandre.meyer/lib/Linux/glew-1.9.0")
ENDIF(WIN32)

SET(WITH_OPENCL "YES")
IF(WITH_OPENCL)
        IF(WIN32)
                #SET(OPENCL_HOME         "C:\\ProgramData\\NVIDIA Corporation\\NVIDIA GPU Computing SDK 4.1\\OpenCL\\common")
                SET(OPENCL_HOME         "C:\\Program Files (x86)\\AMD APP\\")
        ELSE(WIN32)
                SET(OPENCL_HOME         "/opt/AMDAPP")
        ENDIF(WIN32)
        add_definitions(-DUSE_OPENCL)
ENDIF(WITH_OPENCL)

###################################################


cmake_minimum_required(VERSION 2.4)
if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

###### Dependencies
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/")

######## OPENGL
FIND_PACKAGE(OpenGL REQUIRED)
MESSAGE(STATUS "OPENGL_FOUND=${OPENGL_FOUND}")
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
   MESSAGE( STATUS "    OPENGL_INCLUDE_DIR=${OPENGL_INCLUDE_DIR}" )
   MESSAGE( STATUS "    OPENGL_LIBRARIES=${OPENGL_LIBRARIES}" )

######## GLUT
FIND_PACKAGE(GLUT REQUIRED)
MESSAGE(STATUS "GLUT_FOUND=${GLUT_FOUND}")
INCLUDE_DIRECTORIES(${GLUT_INCLUDE_DIR})
   MESSAGE( STATUS "    GLUT_INCLUDE_DIR=${GLUT_INCLUDE_DIR}" )
   MESSAGE( STATUS "    GLUT_LIBRARIES=${GLUT_LIBRARIES}" )

######## GLEW
FIND_PACKAGE(GLEW REQUIRED)
INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIR})
  MESSAGE( STATUS "GLEW_FOUND=${GLEW_FOUND}")
  MESSAGE( STATUS "    GLEW_INCLUDE_DIR=${GLEW_INCLUDE_DIR}" )
  MESSAGE( STATUS "    GLEW_LIBRARIES=${GLEW_LIBRARIES}" )

######## OPENCL
IF(WITH_OPENCL)
        FIND_PACKAGE(OPENCL)
        MESSAGE(STATUS "OpenCL found")
        #SET(CMAKE_INCLUDE_DIRECTORIES_BEFORE on)
        #INCLUDE_DIRECTORIES(AFTER SYSTEM ${OPENCL_INCLUDE_DIR})  # -idirafter
	IF(CMAKE_COMPILER_IS_GNUCXX)
		ADD_DEFINITIONS(-idirafter${OPENCL_INCLUDE_DIR})
	ELSE(CMAKE_COMPILER_IS_GNUCXX)
		INCLUDE_DIRECTORIES(AFTER ${OPENCL_INCLUDE_DIR})  # -idirafter
	ENDIF(CMAKE_COMPILER_IS_GNUCXX)
        MESSAGE( STATUS "    OPENCL_INCLUDE_DIR=${OPENCL_INCLUDE_DIR}" )
        MESSAGE( STATUS "    OPENCL_LIBRARIES=${OPENCL_LIBRARIES}" )
ENDIF(WITH_OPENCL)

####### BOOST
#FIND_PACKAGE( Boost 1.45.0 COMPONENTS system date_time filesystem program_options regex signals serialization thread unit_test_framework REQUIRED )
#include_directories ( ${Boost_INCLUDE_DIRS} )
#link_directories( ${Boost_LIBRARY_DIRS} )



INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CAMath)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CL)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CLUtil)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/CAViewer)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src/tools)


MESSAGE("*************** OGLPLUS ******************")
SET(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})
include(CMakeListsOGL.txt)
MESSAGE("*************** END: OGLPLUS ******************")


SET( CLShallowWater_FILES
	./src/CAMath/Mat4.h
	./src/CAMath/Vec4.h
	./src/CAMath/Vec3.h
	./src/CAMath/Vec2.h
	./src/CAMath/Quaternion.h

	./src/CAViewer/Camera.h
	./src/CAViewer/Viewer.h
	./src/CAViewer/Viewer.cpp
	./src/CAViewer/CAViewer.h
	./src/CAViewer/CAViewer.cpp
	./src/CAViewer/main.cpp

	./src/CLUtil/SDKBitMap.cpp
	./src/CLUtil/SDKCommon.cpp
	./src/CLUtil/SDKFile.cpp
	./src/CLUtil/SDKThread.cpp
	./src/CLUtil/SDKApplication.cpp
	./src/CLUtil/SDKCommandArgs.cpp
	./src/CLUtil/SDKBitMap.hpp
	./src/CLUtil/SDKFile.hpp
	./src/CLUtil/SDKCommon.hpp
	./src/CLUtil/SDKApplication.hpp
	./src/CLUtil/SDKThread.hpp
	./src/CLUtil/SDKCommandArgs.hpp

	./src/CL/CLWater.h
	./src/CL/CLWater.cpp

	./src/CLWater.cl
	./src/fragment.glsl
	./src/vertex.glsl

	./src/oglplus//uniform_block.hpp
	./src/oglplus//color_buffer.hpp
	./src/oglplus//uniform_subroutines.hpp
	./src/oglplus//array.hpp
	./src/oglplus//one_of.hpp
	./src/oglplus//glfunc.hpp
	./src/oglplus//context.hpp
	./src/oglplus//blend_func.hpp
	./src/oglplus//provoke_mode.hpp
	./src/oglplus//framebuffer.hpp
	./src/oglplus//opt/shader_literals.hpp
	./src/oglplus//opt/debug_output.hpp
	./src/oglplus//opt/smart_enums.hpp
	./src/oglplus//opt/list_init.hpp
	./src/oglplus//opt/application.hpp
	./src/oglplus//opt/resources.hpp
	./src/oglplus//opt/ranges.hpp
	./src/oglplus//image.hpp
	./src/oglplus//bound.hpp
	./src/oglplus//interop/glm.hpp
	./src/oglplus//object.hpp
	./src/oglplus//hint.hpp
	./src/oglplus//all.hpp
	./src/oglplus//pixel_data.hpp
	./src/oglplus//error.hpp
	./src/oglplus//program.hpp
	./src/oglplus//compare_func.hpp
	./src/oglplus//images/sphere_bmap.hpp
	./src/oglplus//images/filtered.hpp
	./src/oglplus//images/normal_map.hpp
	./src/oglplus//images/cloud.hpp
	./src/oglplus//images/transformed.hpp
	./src/oglplus//images/random.hpp
	./src/oglplus//images/png.hpp
	./src/oglplus//images/squares.hpp
	./src/oglplus//images/gradient.hpp
	./src/oglplus//images/newton.hpp
	./src/oglplus//images/brushed_metal.hpp
	./src/oglplus//images/load.hpp
	./src/oglplus//doc.hpp
	./src/oglplus//limited_value.hpp
	./src/oglplus//bitfield.hpp
	./src/oglplus//curve.hpp
	./src/oglplus//fwd.hpp
	./src/oglplus//matrix.hpp
	./src/oglplus//transform_feedback.hpp
	./src/oglplus//glsl_source.hpp
	./src/oglplus//texture_unit.hpp
	./src/oglplus//shapes/blender_mesh.hpp
	./src/oglplus//shapes/revolve.hpp
	./src/oglplus//shapes/spiral_sphere.hpp
	./src/oglplus//shapes/draw.hpp
	./src/oglplus//shapes/wicker_torus.hpp
	./src/oglplus//shapes/torus.hpp
	./src/oglplus//shapes/tetrahedrons.hpp
	./src/oglplus//shapes/plane.hpp
	./src/oglplus//shapes/sky_box.hpp
	./src/oglplus//shapes/cube.hpp
	./src/oglplus//shapes/sphere.hpp
	./src/oglplus//shapes/icosahedron.hpp
	./src/oglplus//shapes/wrapper.hpp
	./src/oglplus//shapes/vert_attr_info.hpp
	./src/oglplus//buffer.hpp
	./src/oglplus//sync.hpp
	./src/oglplus//vertex_attrib.hpp
	./src/oglplus//angle.hpp
	./src/oglplus//face_mode.hpp
	./src/oglplus//shader.hpp
	./src/oglplus//auxiliary/strings.hpp
	./src/oglplus//auxiliary/endian.hpp
	./src/oglplus//auxiliary/tp_mat_vec.hpp
	./src/oglplus//auxiliary/uniform_init.hpp
	./src/oglplus//auxiliary/shader_data.hpp
	./src/oglplus//auxiliary/base_array.hpp
	./src/oglplus//auxiliary/program.hpp
	./src/oglplus//auxiliary/glsl_source.hpp
	./src/oglplus//auxiliary/prog_pl_stages.hpp
	./src/oglplus//auxiliary/base_iter.hpp
	./src/oglplus//auxiliary/info_log.hpp
	./src/oglplus//auxiliary/binding_query.hpp
	./src/oglplus//auxiliary/ct_math.hpp
	./src/oglplus//auxiliary/enum_class.hpp
	./src/oglplus//auxiliary/named.hpp
	./src/oglplus//auxiliary/base_range.hpp
	./src/oglplus//auxiliary/varpara_fns.hpp
	./src/oglplus//auxiliary/utf8.hpp
	./src/oglplus//auxiliary/utf8/conversion.hpp
	./src/oglplus//auxiliary/utf8/validator.hpp
	./src/oglplus//auxiliary/filesystem.hpp
	./src/oglplus//link_error.hpp
	./src/oglplus//vertex_array.hpp
	./src/oglplus//math.hpp
	./src/oglplus//compile_error.hpp
	./src/oglplus//config.hpp
	./src/oglplus//gl.hpp
	./src/oglplus//bound/framebuffer.hpp
	./src/oglplus//bound/buffer.hpp
	./src/oglplus//bound/renderbuffer.hpp
	./src/oglplus//bound/texture.hpp
	./src/oglplus//access_specifier.hpp
	./src/oglplus//program_interface.hpp
	./src/oglplus//plane.hpp
	./src/oglplus//vector.hpp
	./src/oglplus//color_log_op.hpp
	./src/oglplus//limit_query.hpp
	./src/oglplus//blit_filter.hpp
	./src/oglplus//sampler.hpp
	./src/oglplus//renderbuffer.hpp
	./src/oglplus//buffer_select_bit.hpp
	./src/oglplus//primitive_type.hpp
	./src/oglplus//text/bitmap_glyph.hpp
	./src/oglplus//text/unicode.hpp
	./src/oglplus//text/pango_cairo.hpp
	./src/oglplus//text/bitmap_glyph/pager.hpp
	./src/oglplus//text/bitmap_glyph/font.hpp
	./src/oglplus//text/bitmap_glyph/page_storage.hpp
	./src/oglplus//text/bitmap_glyph/fwd.hpp
	./src/oglplus//text/bitmap_glyph/layout_storage.hpp
	./src/oglplus//text/bitmap_glyph/renderer.hpp
	./src/oglplus//text/bitmap_glyph/layout.hpp
	./src/oglplus//text/pango_cairo/font.hpp
	./src/oglplus//text/pango_cairo/fwd.hpp
	./src/oglplus//text/pango_cairo/layout_storage.hpp
	./src/oglplus//text/pango_cairo/renderer.hpp
	./src/oglplus//text/pango_cairo/handle.hpp
	./src/oglplus//text/pango_cairo/layout.hpp
	./src/oglplus//text/common.hpp
	./src/oglplus//lib.hpp
	./src/oglplus//string_query.hpp
	./src/oglplus//pixel_storage_mode.hpp
	./src/oglplus//data_type.hpp
	./src/oglplus//ext/ATI_meminfo.hpp
	./src/oglplus//ext/ARB_compatibility.hpp
	./src/oglplus//ext/ARB_debug_output.hpp
	./src/oglplus//ext/AMD_performance_monitor.hpp
	./src/oglplus//ext/EXT_direct_state_access.hpp
	./src/oglplus//ext/NV_path_rendering.hpp
	./src/oglplus//exposed.hpp
	./src/oglplus//extension.hpp
	./src/oglplus//enumerations.hpp
	./src/oglplus//capability.hpp
	./src/oglplus//query.hpp
	./src/oglplus//auto_bind.hpp
	./src/oglplus//string.hpp
	./src/oglplus//memory_barrier.hpp
	./src/oglplus//friend_of.hpp
	./src/oglplus//context/clear_buffers.hpp
	./src/oglplus//context/computing.hpp
	./src/oglplus//context/stencil_test.hpp
	./src/oglplus//context/limit_queries.hpp
	./src/oglplus//context/errors.hpp
	./src/oglplus//context/viewport.hpp
	./src/oglplus//context/string_queries.hpp
	./src/oglplus//context/blending.hpp
	./src/oglplus//context/pixel_ops.hpp
	./src/oglplus//context/synchronization.hpp
	./src/oglplus//context/rasterization.hpp
	./src/oglplus//context/capabilities.hpp
	./src/oglplus//context/buffer_masking.hpp
	./src/oglplus//context/scissor_test.hpp
	./src/oglplus//context/logical_ops.hpp
	./src/oglplus//context/drawing.hpp
	./src/oglplus//context/hints.hpp
	./src/oglplus//context/buffer_selection.hpp
	./src/oglplus//context/depth_test.hpp
	./src/oglplus//imports/blend_file/block.hpp
	./src/oglplus//imports/blend_file/block_data.hpp
	./src/oglplus//imports/blend_file/reader_client.hpp
	./src/oglplus//imports/blend_file/sdna.hpp
	./src/oglplus//imports/blend_file/utils.hpp
	./src/oglplus//imports/blend_file/info.hpp
	./src/oglplus//imports/blend_file/pointer.hpp
	./src/oglplus//imports/blend_file/reader.hpp
	./src/oglplus//imports/blend_file/type.hpp
	./src/oglplus//imports/blend_file/structure.hpp
	./src/oglplus//imports/blend_file/flattened.hpp
	./src/oglplus//imports/blend_file/range.hpp
	./src/oglplus//imports/blend_file/struct_block_data.hpp
	./src/oglplus//imports/blend_file.hpp
	./src/oglplus//texture.hpp
	./src/oglplus//uniform.hpp
	./src/oglplus//program_pipeline.hpp
	./src/oglplus//stencil_op.hpp
	./src/oglplus//polygon_mode.hpp

)


ADD_EXECUTABLE( CLShallowWater  ${CLShallowWater_FILES})
TARGET_LINK_LIBRARIES( CLShallowWater  	${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${OPENCL_LIBRARIES} )
SET_TARGET_PROPERTIES( CLShallowWater PROPERTIES DEBUG_POSTFIX _d)
SET_TARGET_PROPERTIES( CLShallowWater PROPERTIES COMPILE_FLAGS -D_CRT_SECURE_NO_WARNINGS)
SET_TARGET_PROPERTIES( CLShallowWater PROPERTIES PROJECT_LABEL _app_CLShallowWater)
SET(TARGET ${TARGET}  CLShallowWater)
MESSAGE(STATUS "Building app CLShallowWater")
