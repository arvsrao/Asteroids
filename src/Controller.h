#ifndef ASTEROIDS_CONTROLLER_H
#define ASTEROIDS_CONTROLLER_H

#include <deque>
#include <SDL.h>
#include "Renderer.h"

class Controller {
public:
    explicit Controller(std::shared_ptr<Player> player);

    // copy constructor and copy assignment operator are deleted
    Controller& operator=(const Controller& rhs) = delete;
    Controller(const Controller& other) = delete;

    // move constructor and move assignment operator are deleted
    Controller& operator=(const Controller&& rhs) = delete;
    Controller(const Controller&& other) = delete;

    void handleInput(Renderer& renderer, bool &running);

private:
    std::shared_ptr<Player> _player;

    void doKeyDown(SDL_KeyboardEvent *event);

};
#endif //ASTEROIDS_CONTROLLER_H
