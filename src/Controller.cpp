#include "Controller.h"
#include "Player.h"
#include <vector>
#include "ThreadSafeQueue.cpp"

Controller::Controller(
        std::shared_ptr<PhaserBlastQueuePointer> phaserBlasts,
        std::shared_ptr<Player> player) :
        _phaserBlasts(phaserBlasts), _player(player) {}

void Controller::doKeyDown(SDL_KeyboardEvent *event) {

    switch (event->keysym.scancode) {
        case SDL_SCANCODE_UP:
            _player->moveUp();
            break;
        case SDL_SCANCODE_DOWN:
            _player->moveDown();
            break;
        case SDL_SCANCODE_LEFT:
            _player->moveLeft();
            break;
        case SDL_SCANCODE_RIGHT:
            _player->moveRight();
            break;
        case SDL_SCANCODE_D:
            _player->rotateClockwise();
            break;
        case SDL_SCANCODE_A:
            _player->rotateCounterClockwise();
            break;
        case SDL_SCANCODE_SPACE:
            _phaserBlasts->push(std::move(_player->fire()));
            break;
        default:
            break;
    }
}

void Controller::handleInput(Renderer &renderer, bool& running) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
            case SDL_KEYDOWN:
                doKeyDown(&event.key);
                renderer.wrapEntityCoordinates(_player.get());
                break;
            default:
                break;
        }
    }
}