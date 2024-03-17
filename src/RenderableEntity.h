#ifndef ASTEROIDS_RENDERABLEENTITY_H
#define ASTEROIDS_RENDERABLEENTITY_H

#include <memory>
#include <algorithm>
#include <SDL.h>

/** type of the entity being rendered. */
enum EntityType { ASTEROID, ASTEROID_FRAGMENTS, PHASER_BLAST, EXPLOSION, PLAYER };

/** Trait for all entities that are rendered to the screen. */
class RenderableEntity {

public:
    RenderableEntity();
    RenderableEntity(int x, int y, int angle, EntityType type);
    virtual ~RenderableEntity();

    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

    EntityType getEntityType() const;
    void setEntityType(EntityType e);

    virtual bool collidesWith(RenderableEntity& other);

    SDL_Point* getRotationCenter() const;

    virtual int getX() const;
    virtual int getY() const;
    void setX(int x);
    void setY(int y);

    int getAngle() const;
    virtual void setAngle(int angle);

protected:
    EntityType _type;

private:
    int _x, _y, _angle;
    static inline const std::unique_ptr<SDL_Point> center_;

};


#endif //ASTEROIDS_RENDERABLEENTITY_H
