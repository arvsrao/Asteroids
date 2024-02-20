#ifndef ASTEROIDS_ASTEROID_H
#define ASTEROIDS_ASTEROID_H

#include <random>
#include <thread>
#include <deque>
#include "RenderableEntity.h"
#include "PhaserBlast.h"
#include "Player.h"
#include "GameObject.h"

class Asteroid : public RenderableEntity, GameObject {
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

    Explosion checkForCollision(const std::shared_ptr<Player> player, std::deque<std::shared_ptr<PhaserBlast>>& blasts);

    bool isHit();

private:

    // constants representing size of asteroid image.
    static constexpr int w = 74;
    static constexpr int h = 75;
    static constexpr int _MOVE_INCREMENT = 2;

    bool _hit{false};
    int _identifier;
    double _PERIOD, _START_Y;

    std::mutex _mtx;

};

#endif //ASTEROIDS_ASTEROID_H
