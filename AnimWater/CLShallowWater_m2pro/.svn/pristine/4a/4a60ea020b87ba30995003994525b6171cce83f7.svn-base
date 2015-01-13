#-*-cmake-*-
#
# Test for OpenCL libraries
#
# Once loaded this will define
#  OPENCL_FOUND        - system has libOpenCl.so
#  OPENCL_INCLUDE_DIR  - include directory
#  OPENCL_LIBRARIES    - libraries you need to link to
#

SET(OPENCL_FOUND   "NO" )

FIND_PATH( OPENCL_INCLUDE_DIR CL/opencl.h
        "${OPENCL_HOME}/"
        "${OPENCL_HOME}/include"
        "${OPENCL_HOME}/include/CL"
		"${OPENCL_HOME}/inc"
		"${OPENCL_HOME}/inc/CL"
        /usr/include/GL
	/usr/include/
  )


IF( CMAKE_SIZEOF_VOID_P EQUAL 8 )       # 64bits
    FIND_LIBRARY(OPENCL_LIBRARIES
      NAMES OPENCL OpenCL
      PATHS
            "${OPENCL_HOME}/"
            "${OPENCL_HOME}/lib"
            "${OPENCL_HOME}/lib/x86_64"
            "${OPENCL_HOME}/lib"
            /usr/lib
        NO_DEFAULT_PATH
            )
  ELSE( CMAKE_SIZEOF_VOID_P EQUAL 8 )       # 32 bits
    FIND_LIBRARY(OPENCL_LIBRARIES
      NAMES OPENCL OpenCL
      PATHS
            "${OPENCL_HOME}/"
            "${OPENCL_HOME}/lib"
            "${OPENCL_HOME}/lib/x86"
            "${OPENCL_HOME}/lib/x86_32"
            "${OPENCL_HOME}/lib"
            /usr/lib
        NO_DEFAULT_PATH
            )
  ENDIF( CMAKE_SIZEOF_VOID_P EQUAL 8 )



IF (OPENCL_INCLUDE_DIR)
  IF(OPENCL_LIBRARIES)
    SET(OPENCL_FOUND "YES")
    GET_FILENAME_COMPONENT(OPENCL_LIBRARY_DIR ${OPENCL_LIBRARIES}   PATH)
  ENDIF(OPENCL_LIBRARIES)
ENDIF(OPENCL_INCLUDE_DIR)

#MESSAGE( OPENCL_LIBRARIES=${OPENCL_LIBRARIES} )

IF(NOT OPENCL_FOUND)
        MESSAGE( OPENCL_HOME=${OPENCL_HOME} )
        MESSAGE( OPENCL_INCLUDE_DIR=${OPENCL_INCLUDE_DIR} )
        MESSAGE( OPENCL_LIBRARIES=${OPENCL_LIBRARIES} )
        MESSAGE(FATAL_ERROR "OPENCL required, please specify it's location with OPENCL_HOME")
ENDIF(NOT OPENCL_FOUND)

#####
