cmake_minimum_required( VERSION 3.6 )

project( HDK_Examples )

# CMAKE_PREFIX_PATH must contain the path to the toolkit/cmake subdirectory of
# the Houdini installation. See the "Compiling with CMake" section of the HDK
# documentation for more details, which describes several options for
# specifying this path.
if(WIN32)
	set( HOUDINI_ROOT "C:/Program Files/Side Effects Software/Houdini 18.5.351 Python3" )
elseif(UNIX)
	set( HOUDINI_ROOT "/opt/hfs18.5.351" )
endif()

#list( APPEND CMAKE_PREFIX_PATH "$ENV{HFS}/toolkit/cmake" )
list( APPEND CMAKE_PREFIX_PATH "${HOUDINI_ROOT}/toolkit/cmake" )

# Locate Houdini's libraries and header files.
# Registers an imported library target named 'Houdini'.
find_package( Houdini REQUIRED )

# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()


add_subdirectory(sop_star)
add_subdirectory(standalone)