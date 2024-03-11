#ifndef ASTEROIDS_PLAYER_H
#define ASTEROIDS_PLAYER_H

#include <set>
#include <SDL.h>
#include "PhaserBlast.h"
#include "Explosion.h"
#include "ThreadSafeQueue.h"


#include <list>

/** Type alias for the phaser blast queue. It is meant to be shared. */
using PhaserBlastPointer      = std::unique_ptr<PhaserBlast>;
using PhaserBlastQueuePointer = ThreadSafeQueue<PhaserBlastPointer>;

class Player : public RenderableEntity {

public:

    Player(const int move_increment, const int rotation_increment, std::shared_ptr<PhaserBlastQueuePointer> phaserBlasts);

    void fire() const;
    void rotateClockwise();
    void rotateCounterClockwise();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    int getWidth() const override;
    int getHeight() const override;

    void incrementScore();
    void registerHit(int identifier);
    int getScore() const;
    int getHealth() const;

    bool collidesWith(RenderableEntity& other) override;

    std::string toString() const;

private:
    const int MOVE_INCREMENT_, ROTATION_INCREMENT_DEGREES_;
    static constexpr int w = 111;
    static constexpr int h = 111;

    std::shared_ptr<PhaserBlastQueuePointer> _phaserBlasts;
    std::set<int> asteroidIdentifiers;

    int _health{3}, score_{0};
};

#endif //ASTEROIDS_PLAYER_H
