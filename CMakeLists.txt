cmake_minimum_required(VERSION 3.24)
project(asteroids)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Find all executables
file(GLOB PROJECT_SRC src/*.cpp) #src/*.h

# Add project executable
add_executable(asteroids ${PROJECT_SRC})
include_directories("/usr/local/Cellar/sdl2_image/2.6.3_1/include/SDL2/")
target_link_libraries(asteroids ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} "/usr/local/Cellar/sdl2_image/2.6.3_1/lib/libSDL2_image.dylib")
