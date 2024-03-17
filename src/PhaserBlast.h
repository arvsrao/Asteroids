#ifndef ASTEROIDS_PHASERBLAST_H
#define ASTEROIDS_PHASERBLAST_H

#include <algorithm>
#include <SDL.h>

#include "RenderableEntity.h"

class PhaserBlast : public RenderableEntity {
public:
    static inline const std::unique_ptr<SDL_Point> center_ = std::make_unique<SDL_Point>(SDL_Point{0, 0});

    PhaserBlast(int _x, int _y, int _angle);

    PhaserBlast(const PhaserBlast &other);  // copy constructor
    PhaserBlast &operator=(const PhaserBlast &other) = delete; // delete copy assignment constructor

    PhaserBlast(const PhaserBlast &&other) noexcept; // move constructor
    PhaserBlast &operator=(const PhaserBlast &&other) = delete; // delete move assignment constructor

    void move();

    int getWidth() const;

    int getHeight() const;

private:
    const int X_INCREMENT, Y_INCREMENT;
    static constexpr double INCREMENT = 10.0;
    static constexpr int w = 27;
    static constexpr int h = 4;

    static int computeXIncrement(const int angle);

    static int computeYIncrement(const int angle);
};

#endif //ASTEROIDS_PHASERBLAST_H
