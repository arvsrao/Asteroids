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

class Game {
public:

    Game(std::shared_ptr<Player>& player, std::shared_ptr<PhaserBlastQueuePointer> phaserBlasts);
    Game(const int player_increment, const int rotation_increment);
    ~Game();

    void run(Renderer &renderer, const std::shared_ptr<Controller>& controller, int target_frame_duration);
    void end();

private:

    std::shared_ptr<bool> _running;
    std::shared_ptr<Player> _player;

    std::mutex _mutex;
    ThreadSafeQueue<std::shared_ptr<Asteroid>> _asteroids;
    ThreadSafeQueue<Explosion> _explosions;
    std::shared_ptr<PhaserBlastQueuePointer> _phaserBlasts;

    std::vector<std::thread> _threads;
    RandomNumberBetween generateWaitTime;

    void spawn(Renderer& renderer);
    void renderExplosions(Renderer &renderer, SDL_Texture *texture);
    void renderAsteroids(Renderer& renderer, std::function<void(Asteroid* rock)> render);
    void renderPhaserBlasts(Renderer& renderer, SDL_Texture* texture);
    void detectCollision(std::future<std::optional<Explosion>>&& ftr);
};


#endif //ASTEROIDS_GAME_H
