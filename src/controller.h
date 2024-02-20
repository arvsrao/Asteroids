#ifndef ASTEROIDS_CONTROLLER_H
#define ASTEROIDS_CONTROLLER_H

#include <SDL.h>
#include "renderer.h"
#include <deque>

class Controller {

public:
    void handleInput(Renderer& renderer, Player &player, std::deque<std::shared_ptr<PhaserBlast>>& blasts, bool& running);

private:
    void doKeyDown(SDL_KeyboardEvent *event, Renderer& renderer, Player &player, std::deque<std::shared_ptr<PhaserBlast>>& blasts);

};
#endif //ASTEROIDS_CONTROLLER_H
