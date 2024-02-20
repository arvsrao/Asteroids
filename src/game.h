#ifndef ASTEROIDS_GAME_H
#define ASTEROIDS_GAME_H

#include <list>
#include <deque>
#include <thread>
#include <future>
#include "controller.h"
#include "Asteroid.h"

class Explosion;

class RandomNumberBetween
{
public:
    RandomNumberBetween(int low, int high);
    int operator()();
private:
    std::mt19937 random_engine_;
    std::uniform_int_distribution<int> distribution_;
};

class Game : public GameObject {
public:

    Game(const int player_increment, const int rotation_increment); //, const int blast_increment_);
    ~Game();

    void run(Renderer &renderer, Controller& controller, int target_frame_duration);

private:
    std::shared_ptr<Player> _player;
    bool _running{true};

    std::vector<std::thread> _threads;

    RandomNumberBetween _randomNumberBetweenZeroAndTwo;
    std::deque<std::shared_ptr<PhaserBlast>> _blasts;
    std::deque<std::shared_ptr<Asteroid>> _asteroids;
    std::deque<Explosion> _explosions;
    std::deque<std::future<Explosion>> _futures;

    void renderAsteroids(Renderer &renderer, SDL_Texture *texture);
    void renderPhaserBlasts(Renderer& renderer, SDL_Texture* texture);
    void spawn(Renderer& renderer);

    void renderExplosions(Renderer &renderer, SDL_Texture *texture);

    void detectPlayerEnemyCollision();
};


#endif //ASTEROIDS_GAME_H
