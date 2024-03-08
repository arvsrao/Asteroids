#ifndef ASTEROIDS_PLAYER_H
#define ASTEROIDS_PLAYER_H

#include <set>
#include <SDL.h>
#include "PhaserBlast.h"
#include "Explosion.h"

#include <list>

class Player : public RenderableEntity {

public:
    //SDL_Texture* texture;

    Player(const int move_increment, const int rotation_increment);

    std::unique_ptr<PhaserBlast> fire() const;
    void rotateClockwise();
    void rotateCounterClockwise();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    int getWidth() const;
    int getHeight() const;

    void incrementScore();
    void registerHit(int identifier);
    int getScore() const;
    int getHealth() const;

    bool collidesWith(RenderableEntity& other);

    std::string toString() const;

private:
    const int MOVE_INCREMENT_, ROTATION_INCREMENT_DEGREES_;
    static constexpr int w = 111;
    static constexpr int h = 111;

    std::set<int> asteroidIdentifiers;

    int _health{3}, score_{0};
};

#endif //ASTEROIDS_PLAYER_H
