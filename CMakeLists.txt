cmake_minimum_required(VERSION 3.12)
project(StudentuRusiavimas CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/O2 /W4)
else()
    add_compile_options(-O3 -Wall)
endif()

set(SOURCES
    main.cpp
    pagalbine.cpp
    studentas.cpp
)

set(HEADERS
    pagalbine.h
    studentas.h
)

add_executable(programa ${SOURCES} ${HEADERS})