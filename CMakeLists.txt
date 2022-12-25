cmake_minimum_required(VERSION 3.7)
project(Pathfinder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH /usr/share/cmake-3.22/Modules)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2TTF REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/header/")
include_directories("${PROJECT_SOURCE_DIR}/scripts/header/")
include_directories("${PROJECT_SOURCE_DIR}/config/")

file(GLOB_RECURSE Pathfinder_SOURCES CONFIGURE_DEPENDS "*.cpp")
list(FILTER Pathfinder_SOURCES EXCLUDE REGEX ".*cmake-build-debug.*")
add_executable(Pathfinder ${Pathfinder_SOURCES})

target_link_libraries(Pathfinder ${SDL2_LIBRARIES} ${SDL2TTF_LIBRARY} Threads::Threads)