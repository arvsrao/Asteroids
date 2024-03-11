#ifndef ASTEROIDS_RENDERABLEENTITY_H
#define ASTEROIDS_RENDERABLEENTITY_H

#include <memory>
#include <algorithm>
#include <SDL.h>

enum EntityType { ASTEROID, ASTEROID_FRAGMENTS, PHASER_BLAST, EXPLOSION, PLAYER };

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

    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);

    int getAngle() const;
    virtual void setAngle(int angle);

protected:
    EntityType _type;

private:
    int x_, y_, angle_;
    static inline const std::unique_ptr<SDL_Point> center_;

};


#endif //ASTEROIDS_RENDERABLEENTITY_H
