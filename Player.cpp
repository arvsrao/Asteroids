#include <string>
#include "util.h"
#include "Player.h"

Player::Player(const int move_increment, const int rotation_increment):
        RenderableEntity(50,250, 0),
        MOVE_INCREMENT_(move_increment),
        ROTATION_INCREMENT_DEGREES_(rotation_increment){}

std::unique_ptr<PhaserBlast> Player::fire() const {
    return std::make_unique<PhaserBlast>(
            (getX() + 55) + static_cast<int>(42.0 * cos(math::toRadians(360 - getAngle()))),
            (getY() + 55) - static_cast<int>(45.0 * sin(math::toRadians(360 - getAngle()))),
            getAngle() );
}

void Player::rotateClockwise() {
    setAngle(getAngle() + ROTATION_INCREMENT_DEGREES_);
}

void Player::rotateCounterClockwise() {
    setAngle(getAngle() - ROTATION_INCREMENT_DEGREES_);
}

std::string Player::toString() const {
    return "(" + std::to_string(getX()) + ", " + std::to_string(getX()) +")";
}

void Player::moveUp() { setY(getY() - MOVE_INCREMENT_); }

void Player::moveDown() { setY(getY() + MOVE_INCREMENT_); }

void Player::moveLeft() { setX(getX() - MOVE_INCREMENT_); }

void Player::moveRight() { setX(getX() + MOVE_INCREMENT_); }

int Player::getWidth() const {
    return w;
}

int Player::getHeight() const {
    return h;
}

int Player::getScore() const { return score_; }

int Player::getHealth() const { return health_; }

bool Player::collidesWith(RenderableEntity &other) {

    if (RenderableEntity::collidesWith(other)) {
        health_ -= 1;
        return true;
    }
    return false;
}

void Player::incrementScore() { ++score_; }
