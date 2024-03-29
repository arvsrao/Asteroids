#include "Controller.h"

#include <vector>

#include "Player.h"

Controller::Controller(std::shared_ptr<Player> player) : _player(player) {}

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
      _player->fire();
      break;
    default:
      break;
  }
}

void Controller::handleInput(const Renderer &renderer, bool &running) {
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