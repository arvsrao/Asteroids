#include <iostream>
#include "Game.h"

// Screen dimension constants
constexpr int kFramesPerSecond{60};
constexpr int kMsPerFrame{1000 / kFramesPerSecond};
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 700;
constexpr int PLAYER_MOVE_INCREMENT = 8;
constexpr int ROTATION_INCREMENT_DEGREES = 15;

auto renderer = Renderer { SCREEN_HEIGHT, SCREEN_WIDTH };
auto player = std::make_shared<Player>(PLAYER_MOVE_INCREMENT, ROTATION_INCREMENT_DEGREES);
auto phaserBlasts = std::make_shared<PhaserBlastQueuePointer>();
auto game = std::make_shared<Game>(player, phaserBlasts);
auto controller = std::make_shared<Controller>(phaserBlasts, player);

int main(int argc, char* args[]) {
    game->run(renderer, controller, kMsPerFrame);
    std::cout << "Game Over !!" << "\n";
    return 0;
}
