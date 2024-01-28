#include "util.h"
#include "PhaserBlast.h"

PhaserBlast::PhaserBlast(int _x, int _y, const int _angle):
    RenderableEntity(_x, _y,_angle),
    X_INCREMENT(computeXIncrement(_angle)),
    Y_INCREMENT(computeYIncrement(_angle)) {}

PhaserBlast::PhaserBlast(const PhaserBlast& other):
            RenderableEntity(other.getX(), other.getY(),other.getAngle()),
            X_INCREMENT(computeXIncrement(other.getAngle())),
            Y_INCREMENT(computeYIncrement(other.getAngle())) {}

PhaserBlast::PhaserBlast(const PhaserBlast&& other) noexcept :
        RenderableEntity(other.getX(), other.getY(),other.getAngle()),
        X_INCREMENT(computeXIncrement(other.getAngle())),
        Y_INCREMENT(computeYIncrement(other.getAngle())) {}

void PhaserBlast::move() {
    setX(getX() + X_INCREMENT);
    setY(getY() + Y_INCREMENT);
}

int PhaserBlast::computeXIncrement(const int angle) {
    return static_cast<int>(INCREMENT * cos(math::toRadians(angle)));
}

int PhaserBlast::computeYIncrement(const int angle) {
    return static_cast<int>(INCREMENT * sin(math::toRadians(angle)));
}

int PhaserBlast::getWidth() const {
    return w;
}

int PhaserBlast::getHeight() const {
    return h;
}
