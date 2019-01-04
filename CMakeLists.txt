cmake_minimum_required (VERSION 3.1.2)

project (PigeonBound CXX)

include_directories(${PROJECT_NAME} include)

if (WIN32)
	include_directories(${PROJECT_NAME} glew-2.1.0/include)
	link_directories(${PROJECT_NAME} glew-2.1.0/lib)
	
	include_directories(${PROJECT_NAME} SDL2-2.0.9/include)
	link_directories(${PROJECT_NAME} SDL2-2.0.9/build-windows)

	include_directories(${PROJECT_NAME} SDL2_mixer-2.0.4-windows/i686-w64-mingw32/include)
	link_directories(${PROJECT_NAME} SDL2_mixer-2.0.4-windows/i686-w64-mingw32/lib)

	include_directories(${PROJECT_NAME} stb)

	include_directories(${PROJECT_NAME} freetype-2.9.1/include)
	link_directories(${PROJECT_NAME} freetype-2.9.1/build-windows)

	SET (CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE} -Wl,-subsystem,windows -static-libgcc -static-libstdc++)
	SET (CMAKE_EXE_LINKER_FLAGS_RELEASE ${CMAKE_EXE_LINKER_FLAGS_RELEASE} -mwindows)

endif (WIN32)

# Add all files in src/
file (GLOB SOURCES src/*)

SET (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} mingw32)
target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_mixer)
target_link_libraries(${PROJECT_NAME} freetype)
target_link_libraries(${PROJECT_NAME} opengl32 glu32 glew32)
