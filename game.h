#ifndef ASTEROIDS_GAME_H
#define ASTEROIDS_GAME_H

#include <list>
#include <deque>
#include <thread>
#include <mutex>
#include "controller.h"
#include "Asteroid.h"
#include "Explosion.h"

class RandomNumberBetween
{
public:
    RandomNumberBetween(int low, int high);
    int operator()();
private:
    std::mt19937 random_engine_;
    std::uniform_int_distribution<int> distribution_;
};

class Game {
public:

    Game(const int player_increment, const int rotation_increment); //, const int blast_increment_);
    ~Game();
    Player& getPlayer();

    void run(Renderer &renderer, Controller& controller, int target_frame_duration);

private:
    Player _player;
    int move_increment_;
    bool _running{true};

    std::mutex _mutex;
    std::thread _th;

    RandomNumberBetween _randomNumberBetweenZeroAndTwo;
    std::deque<std::unique_ptr<PhaserBlast>> _blasts;
    std::deque<std::unique_ptr<Asteroid>> _asteroids;
    std::list<Explosion> _explosions;

    void renderAsteroids(Renderer &renderer, SDL_Texture *texture);
    void renderPhaserBlasts(Renderer& renderer, SDL_Texture* texture);
    void spawn(Renderer& renderer);


    void renderExplosions(Renderer &renderer, SDL_Texture *texture);

    void detectPlayerEnemyCollision();
};


#endif //ASTEROIDS_GAME_H
