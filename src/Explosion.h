#ifndef ASTEROIDS_EXPLOSION_H
#define ASTEROIDS_EXPLOSION_H

#include "RenderableEntity.h"

class Explosion : public RenderableEntity {
public:

    Explosion(const int x, const int y);

    // copy constructor
    Explosion(const Explosion &rhs);

    // move constructor
    Explosion(const Explosion &&rhs);

    // copy assignment operator
    Explosion &operator=(const Explosion &rhs);

    // move assignment operator
    Explosion &operator=(const Explosion &&rhs);

    int getWidth() const;

    int getHeight() const;

    /** The explosion glyph is rendered for 30 frames, approx. 1/2 seconds. */
    bool isFrameCountPositive();

private:
    int frame_count{30};
};

#endif //ASTEROIDS_EXPLOSION_H
