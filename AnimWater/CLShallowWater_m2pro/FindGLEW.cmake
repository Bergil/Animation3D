#-*-cmake-*-
#
# Test for GLEW libraries
#
# Once loaded this will define
#  GLEW_FOUND        - system has libGLEW
#  GLEW_INCLUDE_DIR  - include directory
#  GLEW_LIBRARIES    - libraries you need to link to
#

SET(GLEW_FOUND   "NO" )

FIND_PATH(GLEW_INCLUDE_DIR GL/glew.h 
	"${GLEW_HOME}"
	"${GLEW_HOME}/include"
	"${GLEW_HOME}/include/GL"
	"/usr/include/GL"
	"C:\\Program Files\\Microsoft Visual Studio 8\\VC\\PlatformSDK\\Include\\gl"
	NO_DEFAULT_PATH
  )

FIND_LIBRARY(GLEW    NO_DEFAULT_PATH
  NAMES glew32 glew32s libGLEW.a libGLEW.so
  PATHS
	"${GLEW_HOME}/lib"
	"/usr/lib"
	"C:\\Program Files\\Microsoft Visual Studio 8\\VC\\PlatformSDK\\lib"
	)
SET(GLEW_LIBRARIES ${GLEW} )
#MESSAGE( GLEW_LIBRARIES=${GLEW_LIBRARIES} )


IF (GLEW_INCLUDE_DIR)
  IF(GLEW_LIBRARIES)
    SET(GLEW_FOUND "YES")
    GET_FILENAME_COMPONENT(GLEW_LIBRARY_DIR ${GLEW}   PATH)
  ENDIF(GLEW_LIBRARIES)
ENDIF(GLEW_INCLUDE_DIR)

#MESSAGE( GLEW_LIBRARIES=${GLEW_LIBRARIES} )

IF(NOT GLEW_FOUND)
	MESSAGE( GLEW_HOME=${GLEW_HOME} )
	MESSAGE( GLEW_INCLUDE_DIR=${GLEW_INCLUDE_DIR} )
	MESSAGE( GLEW_LIBRARIES=${GLEW_LIBRARIES} )
	MESSAGE(FATAL_ERROR "GLEW required, please specify it's location with GLEW_HOME")
ENDIF(NOT GLEW_FOUND)

#####
