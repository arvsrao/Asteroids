#include "controller.h"
#include "Player.h"
#include <vector>

void Controller::doKeyDown(SDL_KeyboardEvent *event, Renderer& renderer, Player &player, std::deque<std::shared_ptr<PhaserBlast>>& blasts) {

    switch (event->keysym.scancode) {
        case SDL_SCANCODE_UP:
            player.moveUp();
            break;
        case SDL_SCANCODE_DOWN:
            player.moveDown();
            break;
        case SDL_SCANCODE_LEFT:
            player.moveLeft();
            break;
        case SDL_SCANCODE_RIGHT:
            player.moveRight();
            break;
        case SDL_SCANCODE_D:
            player.rotateClockwise();
            break;
        case SDL_SCANCODE_A:
            player.rotateCounterClockwise();
            break;
        case SDL_SCANCODE_SPACE:
            blasts.push_back(std::move(player.fire()));
            break;
        default:
            break;
    }

    renderer.wrapEntityCoordinates(player);
}

void Controller::handleInput(Renderer& renderer, Player &player, std::deque<std::shared_ptr<PhaserBlast>>& blasts, bool& running) {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                SDL_Quit();
                running = false;
                exit(0);
            case SDL_KEYDOWN:
                doKeyDown(&event.key, renderer, player, blasts);
                break;
            default:
                break;
        }
    }
}