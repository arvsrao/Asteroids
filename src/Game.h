#ifndef ASTEROIDS_GAME_H
#define ASTEROIDS_GAME_H

#include <vector>
#include <deque>
#include <thread>
#include <future>
#include "Controller.h"
#include "Asteroid.h"
#include "RandomNumberBetween.h"

class Explosion;

enum GameState { RUNNING, PAUSE, GAME_OVER };

class Game {
public:

    Game(std::shared_ptr<Player>& player, std::shared_ptr<PhaserBlastQueuePointer> phaserBlasts);
    Game(const int player_increment, const int rotation_increment);
    ~Game();

    void run(Renderer &renderer, const std::shared_ptr<Controller>& controller, uint32_t target_frame_duration);
    void end();

private:

    GameState _state;

    std::shared_ptr<bool> _running;
    std::shared_ptr<Player> _player;
    std::vector<std::thread> _threads;

    ThreadSafeQueue<std::shared_ptr<Asteroid>> _asteroids;
    std::shared_ptr<ExplosionQueue> _explosions;
    std::shared_ptr<PhaserBlastQueuePointer> _phaserBlasts;

    RandomNumberBetween generateWaitTime;

    void spawn(Renderer& renderer);
    void renderExplosions(Renderer &renderer);
    void renderAsteroids(Renderer& renderer);
    void renderPhaserBlasts(Renderer& renderer);
};


#endif //ASTEROIDS_GAME_H
