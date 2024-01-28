#include "Asteroid.h"
#include "cmath"
#include <iostream>

Asteroid::Asteroid(const int idx, const double period, int x, int y):
        RenderableEntity(x, y,0),
        _identifier(idx),
        _PERIOD(period),
        _START_Y((double)y){
    //std::cout << "creating Asteroid #: " + std::to_string(idx) << "\n";
}

Asteroid::Asteroid(const Asteroid& other):
        RenderableEntity(other.getX(), other.getY(), 0),
        _identifier(other.getIdentifier()),
        _PERIOD(other.getPeriod()),
        _START_Y((double)other.getY()){}

Asteroid::Asteroid(const Asteroid&& other):
        RenderableEntity(other.getX(), other.getY(), 0),
        _identifier(other.getIdentifier()),
        _PERIOD(other.getPeriod()),
        _START_Y((double)other.getY()){}

Asteroid& Asteroid::operator=(const Asteroid& rhs) {
    if (this != &rhs) {
        _identifier = rhs.getIdentifier();
        _PERIOD = rhs.getPeriod();
        _START_Y = (double) rhs.getY();
    }
    return *this;
}

Asteroid& Asteroid::operator=(const Asteroid&& rhs) {
    if (this != &rhs) {
        _identifier = rhs.getIdentifier();
        _PERIOD = rhs.getPeriod();
        _START_Y = (double) rhs.getY();
    }
    return *this;
}

void Asteroid::move() {
    setX(getX() - _MOVE_INCREMENT);
    setY(_START_Y + (double) getHeight() * cos(_PERIOD * getX()));
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

bool Asteroid::isHit() { return _hit; }

bool Asteroid::collidesWith(RenderableEntity& other) {
     _hit = RenderableEntity::collidesWith(other);
     return _hit;
}
