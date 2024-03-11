#ifndef ASTEROIDS_CONTROLLER_H
#define ASTEROIDS_CONTROLLER_H

#include <deque>
#include <SDL.h>
#include "renderer.h"

class Controller {
public:
    Controller(std::shared_ptr<Player> player);

    void handleInput(Renderer& renderer, bool &running);

private:
    std::shared_ptr<Player> _player;

    void doKeyDown(SDL_KeyboardEvent *event);

};
#endif //ASTEROIDS_CONTROLLER_H
