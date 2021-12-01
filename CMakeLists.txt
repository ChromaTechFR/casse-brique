cmake_minimum_required(VERSION 3.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY .)

project(CB)

# Crée des variables avec les fichiers à compiler
file(GLOB SRC ./*.c ./*.h)

set(SRCS 
    ${SRC}
)

# On indique que l'on veut un exécutable "hello" compilé à partir des fichiers décrits par les variables SRCS et HEADERS
add_executable(CB ${SRCS})
target_link_libraries(CB raylib)