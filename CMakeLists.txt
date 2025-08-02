cmake_minimum_required(VERSION 3.26)
project(test)
#find_package(luajit)
find_package(PkgConfig)
pkg_search_module(LUAJIT REQUIRED luajit)

set(SOL_INCLUDE_DIR ./3rdparty/sol2/include)

include_directories(${LUAJIT_INCLUDE_DIRS} ${SOL_INCLUDE_DIR})
link_directories(${LUAJIT_LIBRARY_DIRS})

add_subdirectory(./cpp)