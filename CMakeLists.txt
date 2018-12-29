cmake_minimum_required (VERSION 3.1.2)

project (PigeonBound CXX)

include_directories(${PROJECT_NAME} include)

if (WIN32)
	include_directories(${PROJECT_NAME} glew-2.1.0/include)
	link_directories(${PROJECT_NAME} glew-2.1.0/lib)
	
	include_directories(${PROJECT_NAME} SDL2-2.0.9/include)
	link_directories(${PROJECT_NAME} SDL2-2.0.9/build-windows)

	include_directories(${PROJECT_NAME} stb)
endif (WIN32)

# Add all files in src/
file (GLOB SOURCES src/*)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} mingw32)
target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
target_link_libraries(${PROJECT_NAME} opengl32 glew32)