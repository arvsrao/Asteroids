#ifndef ASTEROIDS_RENDERABLEENTITY_H
#define ASTEROIDS_RENDERABLEENTITY_H

#include <algorithm>
#include <SDL.h>

enum EntityType { PLAYER, ASTEROID, BLAST };

class RenderableEntity {

public:
    RenderableEntity();
    RenderableEntity(int x, int y, int angle);

    int getX() const;
    int getY() const;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual bool collidesWith(RenderableEntity& other);

    int getAngle() const;
    SDL_Point* getRotationCenter() const;

    void setX(int x);
    void setY(int y);
    virtual void setAngle(int angle);

protected:
    EntityType _type;

private:
    int x_, y_, angle_;
    static inline const std::unique_ptr<SDL_Point> center_;

};


#endif //ASTEROIDS_RENDERABLEENTITY_H
