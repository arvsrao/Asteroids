#include "RenderableEntity.h"
#include "util.h"

RenderableEntity::RenderableEntity() : x_(0), y_(0), angle_(0) {}

RenderableEntity::RenderableEntity(int x, int y, int angle, EntityType type) : _type(type), x_(x), y_(y), angle_(angle) {};

int RenderableEntity::getX() const { return x_; }

int RenderableEntity::getY() const { return y_; }

int RenderableEntity::getAngle() const { return angle_; }

void RenderableEntity::setX(int x) { x_ = x; }

void RenderableEntity::setY(int y) { y_ = y; }

void RenderableEntity::setAngle(int angle) {
    angle_ = math::modulo(angle, 360);
}

SDL_Point *RenderableEntity::getRotationCenter() const {
    return center_.get();
}

bool RenderableEntity::collidesWith(RenderableEntity &other) {
    auto noXOverlap = getX() > other.getX() + other.getWidth() || getX() + getWidth() < other.getX();
    auto noYOverlap = getY() > other.getY() + other.getHeight() || getY() + getHeight() < other.getY();
    return !noXOverlap && !noYOverlap;
}

EntityType RenderableEntity::getEntityType() const {
    return _type;
}

void RenderableEntity::setEntityType(EntityType e) {
     _type = e;
}

RenderableEntity::~RenderableEntity() {}
