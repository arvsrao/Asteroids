#ifndef ASTEROIDS_CONTROLLER_H
#define ASTEROIDS_CONTROLLER_H

#include <deque>
#include <SDL.h>
#include "renderer.h"
#include "ThreadSafeQueue.h"

/** Type alias for the phaser blast queue. It is meant to be shared. */
using PhaserBlastPointer      = std::unique_ptr<PhaserBlast>;
using PhaserBlastQueuePointer = ThreadSafeQueue<PhaserBlastPointer>;

class Game;

class Controller {
public:
    Controller(std::shared_ptr<PhaserBlastQueuePointer> phaserBlasts, std::shared_ptr<Player> player);

    void handleInput(Renderer& renderer, bool &running);

private:
    std::shared_ptr<PhaserBlastQueuePointer> _phaserBlasts;
    std::shared_ptr<Player> _player;

    void doKeyDown(SDL_KeyboardEvent *event);

};
#endif //ASTEROIDS_CONTROLLER_H
