cmake_minimum_required(VERSION 3.13)
project(asteroids)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread -std=c++17")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Find all executables
file(GLOB PROJECT_SRC src/*.cpp) #src/*.h

# Add project executable
add_executable(asteroids ${PROJECT_SRC})
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} src)
target_link_libraries(asteroids ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
