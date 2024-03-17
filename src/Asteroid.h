#ifndef ASTEROIDS_ASTEROID_H
#define ASTEROIDS_ASTEROID_H

#include <functional>
#include <optional>

#include "Player.h"
#include "RenderableEntity.h"
#include "ThreadSafeQueue.h"

/** Type alias for the phaser blast queue. It is meant to be shared. */
using PhaserBlastPointer      = std::unique_ptr<PhaserBlast>;
using PhaserBlastQueuePointer = ThreadSafeQueue<PhaserBlastPointer>;

/** Type alias for the explosion queue. It is meant to be shared. */
using ExplosionQueue = ThreadSafeQueue<Explosion>;

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

    // desctructor
    ~Asteroid();

    void move();
    int getWidth() const override;
    int getHeight() const override;
    int getIdentifier() const;
    double getPeriod() const;

    bool collidesWith(RenderableEntity& other) override;

    void checkForCollision(
            const std::shared_ptr<PhaserBlastQueuePointer> phaserBlasts,
            const std::shared_ptr<ExplosionQueue> explosions,
            const std::shared_ptr<Player> player,
            const std::shared_ptr<bool> running,
            const std::function<bool(Asteroid&)>& isInsideWindow);

    void detectCollision(
            const std::shared_ptr<PhaserBlastQueuePointer>& phaserBlasts,
            const std::shared_ptr<ExplosionQueue>& explosions,
            const std::shared_ptr<Player>& player,
            const std::shared_ptr<bool>& running,
            const std::function<bool(Asteroid&)>& isInsideWindow);

    bool isHit() const;

private:

    // constants representing size of asteroid image.
    static constexpr int w = 74;
    static constexpr int h = 75;
    static constexpr int _MOVE_INCREMENT = 2;

    bool _hit{false};
    int _identifier;
    std::thread _thread;
    double _PERIOD, _START_Y;

};

#endif //ASTEROIDS_ASTEROID_H
