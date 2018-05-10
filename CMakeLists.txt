cmake_minimum_required(VERSION 3.9)
project(TerrainEngine)

set(CMAKE_CXX_STANDARD 17)

add_executable(TerrainEngine src/main.cpp include/Application.hpp src/Application.cpp src/GraphicalCore.cpp include/GraphicalCore.hpp
        src/Engine.cpp include/Engine.hpp src/Skybox.cpp include/Skybox.hpp src/Terrain.cpp include/Terrain.hpp src/Water.cpp include/Water.hpp)

FIND_PATH(SOIL_INCLUDE_PATH SOIL/SOIL.h
        /usr/include
        /usr/local/include
        /sw/include
        /opt/local/include
        ${SOIL_ROOT_DIR}/include
        DOC "The directory where SOIL/SOIL.h resides")

# Prefer the static library.
FIND_LIBRARY(SOIL_LIBRARY
        NAMES libSOIL.a SOIL
        PATHS
        /usr/lib64
        /usr/lib
        /usr/local/lib64
        /usr/local/lib
        /sw/lib
        /opt/local/lib
        ${SOIL_ROOT_DIR}/lib
        DOC "The SOIL library")
SET(SOIL_FOUND "NO")
IF(SOIL_INCLUDE_PATH AND SOIL_LIBRARY)
    SET(SOIL_LIBRARIES ${SOIL_LIBRARY})
ENDIF(SOIL_INCLUDE_PATH AND SOIL_LIBRARY)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

include_directories(include/ ${OPENGL_INCLUDE_DIRS} $(SOIL_INCLUDE_PATH) ${GLUT_INCLUDE_DIRS}  ${GLEW_INCLUDE_DIRS} glm/)
target_link_libraries(TerrainEngine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${SOIL_LIBRARY} ${GLEW_LIBRARIES})

file(COPY resources DESTINATION resources)