#include <SDL.h>
#include <SDL_image.h>

#include <string>
#include <iostream>
#include "game.h"

// Screen dimension constants
constexpr int kFramesPerSecond{60};
constexpr int kMsPerFrame{1000 / kFramesPerSecond};
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 700;
constexpr int PLAYER_MOVE_INCREMENT = 8;
constexpr int ROTATION_INCREMENT_DEGREES = 15;
constexpr int BLAST_MOVE_INCREMENT = 10;

auto renderer = Renderer { SCREEN_HEIGHT, SCREEN_WIDTH };
auto game = Game { PLAYER_MOVE_INCREMENT, ROTATION_INCREMENT_DEGREES }; //, BLAST_MOVE_INCREMENT };
auto controller = Controller();

int main(int argc, char* args[]) {
    game.run(renderer, controller, kMsPerFrame);

    return 0;
}
