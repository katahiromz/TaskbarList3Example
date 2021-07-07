# CMakeLists.txt --- CMake project settings
#    ex) cmake -G "Visual Studio 9 2008" .
#    ex) cmake -DCMAKE_BUILD_TYPE=Release -G "MSYS Makefiles" .
##############################################################################

# CMake minimum version
cmake_minimum_required(VERSION 3.0)

# project name and languages
project(TaskbarList3Example CXX RC)

##############################################################################

# TaskbarList3Example.exe
add_executable(TaskbarList3Example WIN32 TaskbarList3Example.cpp TaskbarList3Example_res.rc)
target_link_libraries(TaskbarList3Example comctl32)

##############################################################################
