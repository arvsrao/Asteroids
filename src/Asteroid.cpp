#include "cmath"
#include <thread>
#include <iostream>

#include "Asteroid.h"


Asteroid::Asteroid(const int idx, const double period, int x, int y):
        RenderableEntity(x, y, 0, ASTEROID),
        _identifier(idx),
        _PERIOD(period),
        _START_Y((double)y) {}

Asteroid::Asteroid(const Asteroid& other):
        RenderableEntity(other.getX(), other.getY(), 0, ASTEROID),
        _identifier(other.getIdentifier()),
        _PERIOD(other.getPeriod()),
        _START_Y((double)other.getY()){}

Asteroid::Asteroid(const Asteroid&& other):
        RenderableEntity(other.getX(), other.getY(), 0, ASTEROID),
        _identifier(other.getIdentifier()),
        _PERIOD(other.getPeriod()),
        _START_Y((double)other.getY()){}

Asteroid& Asteroid::operator=(const Asteroid& rhs) {
    if (this != &rhs) {
        _identifier = rhs.getIdentifier();
        _PERIOD = rhs.getPeriod();
        _START_Y = (double) rhs.getY();
        _type = EntityType::ASTEROID;
    }
    return *this;
}

Asteroid& Asteroid::operator=(const Asteroid&& rhs) {
    if (this != &rhs) {
        _identifier = rhs.getIdentifier();
        _PERIOD = rhs.getPeriod();
        _START_Y = (double) rhs.getY();
        _type = EntityType::ASTEROID;
    }
    return *this;
}

void Asteroid::move() {
    setX(getX() - _MOVE_INCREMENT);
    setY((int)_START_Y + (double) getHeight() * cos(_PERIOD * getX()));
}

int Asteroid::getWidth() const {
    return w;
}

int Asteroid::getHeight() const {
    return h;
}

int Asteroid::getIdentifier() const {
    return _identifier;
}

double Asteroid::getPeriod() const {
    return _PERIOD;
}

/**
 * Detect collisions with a specific Asteroid instance.
 *
 * @param phaserBlasts is a collection owned by the function because it may remove phaser blasts that collide with this.
 * @param player is not owned by the function and is used only check for collision with the Ásteroid.
 * @param running is boolean representing the state of the game. True if the game is being played, false otherwise.
 * @param isInsideWindow is a predicate for determining if the Asteroid is visible; if not no need to check for collisions.
 * @return an Explosion in case of a collision, None otherwise.
 */
std::optional<Explosion> Asteroid::checkForCollision(
        const std::shared_ptr<PhaserBlastQueuePointer> phaserBlasts,
        const std::shared_ptr<Player> player, // shouldn't own the player
        const std::shared_ptr<bool> running, // shouldn't own the ref
        const std::function<bool(Asteroid&)>& isInsideWindow) {

    while(isInsideWindow(*this) && *running) {

        // register player hit by reducing health.
        if (this->collidesWith(*player)) player->registerHit(this->getIdentifier());

        if (phaserBlasts->filter([&](std::unique_ptr<PhaserBlast>& b) { return !this->collidesWith(*b); })) {
            player->incrementScore();
        }

        if (this->isHit()) {
            this->setEntityType(ASTEROID_FRAGMENTS);
            return Explosion {this->getX(), this->getY() };
        }
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
    return {};
}

Asteroid::~Asteroid() {
    std::cout << "destructing asteroid: " << _identifier << "\n";
}

bool Asteroid::isHit() const {
    return _hit;
}

bool Asteroid::collidesWith(RenderableEntity& other) {
     _hit = RenderableEntity::collidesWith(other);
     return _hit;
}
