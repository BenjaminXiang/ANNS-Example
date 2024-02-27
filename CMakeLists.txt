cmake_minimum_required(VERSION 3.23)

# set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ANNS-Example LANGUAGES CXX)

find_package(OpenMP REQUIRED)
# if(OpenMP_FOUND)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}${OpenMP_CXX_FLAGS}")
#     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}${OpenMP_EXE_LINKER_FLAGS}")
# endif()

add_subdirectory(utils)
add_subdirectory(hnswlib)
add_subdirectory(SSG)
add_subdirectory(main)
