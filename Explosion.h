#ifndef ASTEROIDS_EXPLOSION_H
#define ASTEROIDS_EXPLOSION_H

#include "RenderableEntity.h"

class Explosion : public RenderableEntity {
public:

    Explosion(int x, int y);
    int getWidth() const;
    int getHeight() const;
    bool isFrameCountPositive();

private:
    int frame_count {20};
};
#endif //ASTEROIDS_EXPLOSION_H
