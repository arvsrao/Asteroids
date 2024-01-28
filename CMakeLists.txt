cmake_minimum_required(VERSION 3.24)
project(asteroids)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(asteroids main.cpp PhaserBlast.h PhaserBlast.cpp Player.h Player.cpp controller.cpp controller.h game.cpp game.h renderer.cpp renderer.h RenderableEntity.cpp RenderableEntity.h util.h
        Asteroid.h
        Asteroid.cpp
        Explosion.h
        Explosion.cpp
        MessageQueue.cpp
        MessageQueue.h
)
include_directories("/usr/local/Cellar/sdl2_image/2.6.3_1/include/SDL2/")
target_link_libraries(asteroids ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} "/usr/local/Cellar/sdl2_image/2.6.3_1/lib/libSDL2_image.dylib")
