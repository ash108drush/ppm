cmake_minimum_required(VERSION 3.16)

project(ppm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ppm main.cpp
    img_lib.cpp img_lib.h ppm_image.cpp ppm_image.h)

include(GNUInstallDirs)
install(TARGETS ppm
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
