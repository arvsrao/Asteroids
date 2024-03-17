#include "RenderableEntity.h"

#include "util.h"

RenderableEntity::RenderableEntity() : _x(0), _y(0), _angle(0) {}

RenderableEntity::RenderableEntity(int x, int y, int angle, EntityType type)
    : _type(type), _x(x), _y(y), _angle(angle){};

int RenderableEntity::getX() const { return _x; }

int RenderableEntity::getY() const { return _y; }

int RenderableEntity::getAngle() const { return _angle; }

void RenderableEntity::setX(int x) { _x = x; }

void RenderableEntity::setY(int y) { _y = y; }

void RenderableEntity::setAngle(int angle) { _angle = math::modulo(angle, 360); }

SDL_Point *RenderableEntity::getRotationCenter() const { return center_.get(); }

bool RenderableEntity::collidesWith(RenderableEntity &other) {
  auto noXOverlap = getX() > other.getX() + other.getWidth() || getX() + getWidth() < other.getX();
  auto noYOverlap =
      getY() > other.getY() + other.getHeight() || getY() + getHeight() < other.getY();
  return !noXOverlap && !noYOverlap;
}

EntityType RenderableEntity::getEntityType() const { return _type; }

void RenderableEntity::setEntityType(EntityType e) { _type = e; }

RenderableEntity::~RenderableEntity() {}
