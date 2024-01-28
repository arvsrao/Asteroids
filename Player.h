#ifndef ASTEROIDS_PLAYER_H
#define ASTEROIDS_PLAYER_H

#include <SDL.h>
#include "PhaserBlast.h"
#include "Explosion.h"

#include <list>

class Player : public RenderableEntity {

public:
    SDL_Texture* texture;

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
    int getScore() const;
    int getHealth() const;

    bool collidesWith(RenderableEntity& other);

    std::string toString() const;

private:
    const int MOVE_INCREMENT_, ROTATION_INCREMENT_DEGREES_;
    static constexpr int w = 111;
    static constexpr int h = 111;

    int health_, score_;
    std::list<std::unique_ptr<Explosion>> _explosions;

};

#endif //ASTEROIDS_PLAYER_H