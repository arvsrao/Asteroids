#include "Explosion.h"

Explosion::Explosion(const int x, const int y) : RenderableEntity(x, y, 0, EXPLOSION) {}

// copy constructor
Explosion::Explosion(const Explosion &rhs) : RenderableEntity(rhs.getX(), rhs.getY(), 0, EXPLOSION) {}

// move constructor
Explosion::Explosion(const Explosion &&rhs) : RenderableEntity(rhs.getX(), rhs.getY(), 0, EXPLOSION) {}

// copy assignment operator
Explosion& Explosion::operator=(const Explosion& rhs) {
    if (this != &rhs) {
        this->setX(rhs.getX());
        this->setY(rhs.getY());
        this->setAngle(0);
        this->setEntityType(EXPLOSION);
    }
    return *this;
}

// move assignment operator
Explosion& Explosion::operator=(const Explosion&& rhs) {
    if (this != &rhs) {
        this->setX(rhs.getX());
        this->setY(rhs.getY());
        this->setAngle(0);
        this->setEntityType(EXPLOSION);
    }
    return *this;
}

bool Explosion::isFrameCountPositive() {
    return frame_count-- > 0;
}

int Explosion::getWidth() const { return 0; }
int Explosion::getHeight() const { return 0;}