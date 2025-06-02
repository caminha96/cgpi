cmake_minimum_required(VERSION 3.10)
project(CGPI)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

# Incluindo manualmente GLUT
find_package(GLUT REQUIRED)

include_directories(
        ${OPENGL_INCLUDE_DIR}
        ${GLUT_INCLUDE_DIR}
        include
)

file(GLOB SOURCES "src/*.cpp")

add_executable(CGPI ${SOURCES}
        src/Cores.cpp
        src/Cores.h
        src/AlienBoss.cpp
        src/Nave.cpp
        src/AlienBoss.h)

target_link_libraries(CGPI
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARIES}
)