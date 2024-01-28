#ifndef ASTEROIDS_ASTEROID_H
#define ASTEROIDS_ASTEROID_H

#include <random>
#include "RenderableEntity.h"
#include "PhaserBlast.h"

class Asteroid : public RenderableEntity {
public:
    Asteroid(const int idx, const double period, int x, int y);

    // copy constructor
    Asteroid(const Asteroid &rhs);

    // move constructor
    Asteroid(const Asteroid &&rhs);

    // copy assignment operator
    Asteroid& operator=(const Asteroid& rhs);

    // move assignment operator
    Asteroid& operator=(const Asteroid&& rhs);

    virtual void move();
    int getWidth() const;
    int getHeight() const;
    int getIdentifier() const;
    double getPeriod() const;

    bool collidesWith(RenderableEntity& other);
    void setCollision();
    bool isHit();

private:

    // constants representing size of asteroid image.
    static constexpr int w = 74;
    static constexpr int h = 75;
    static constexpr int _MOVE_INCREMENT = 2;

    bool _hit{false};
    int _identifier;
    double _PERIOD, _START_Y;

};

#endif //ASTEROIDS_ASTEROID_H
