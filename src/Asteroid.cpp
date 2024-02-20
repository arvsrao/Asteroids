#include "Asteroid.h"
#include "cmath"
#include <iostream>
#include <future>

Asteroid::Asteroid(const int idx, const double period, int x, int y):
        RenderableEntity(x, y,0),
        GameObject(),
        _identifier(idx),
        _PERIOD(period),
        _START_Y((double)y) {
    _type = EntityType::ASTEROID;
}

Asteroid::Asteroid(const Asteroid& other):
        RenderableEntity(other.getX(), other.getY(), 0),
        GameObject(),
        _identifier(other.getIdentifier()),
        _PERIOD(other.getPeriod()),
        _START_Y((double)other.getY()){
    _type = EntityType::ASTEROID;
}

Asteroid::Asteroid(const Asteroid&& other):
        RenderableEntity(other.getX(), other.getY(), 0),
        GameObject(),
        _identifier(other.getIdentifier()),
        _PERIOD(other.getPeriod()),
        _START_Y((double)other.getY()){
    _type = EntityType::ASTEROID;
}

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

Explosion Asteroid::checkForCollision(const std::shared_ptr<Player> player, std::deque<std::shared_ptr<PhaserBlast>>& blasts) {

    while(true) {

        std::lock_guard<std::mutex> lock(_mutex);

        // register player hit by reducing health.
        if (this->collidesWith(*player)) player->registerHit();

         for (size_t idy = 0; idy < blasts.size(); idy++) {
            auto blast = std::move(blasts.front());
            blasts.pop_front();
            if (this->collidesWith(*blast)) {
                player->incrementScore();
                _hit = true;
            } else blasts.push_back(std::move(blast));
        }

        if (this->isHit()) return {this->getY(), this->getY()};
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
}

bool Asteroid::isHit() { return _hit; }

bool Asteroid::collidesWith(RenderableEntity& other) {
     _hit = RenderableEntity::collidesWith(other);
     return _hit;
}
