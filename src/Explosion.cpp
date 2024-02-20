#include "Explosion.h"

Explosion::Explosion(int x, int y) : RenderableEntity(x, y, 0) {}

bool Explosion::isFrameCountPositive() {
    return frame_count-- > 0;
}

int Explosion::getWidth() const { return 0; }
int Explosion::getHeight() const { return 0;}