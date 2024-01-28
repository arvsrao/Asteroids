#include <iostream>
#include <chrono>
#include "game.h"
#include "Asteroid.h"

using namespace std::chrono;

RandomNumberBetween::RandomNumberBetween(int low, int high): random_engine_(std::random_device{}()), distribution_(low,high) {}

int RandomNumberBetween::operator()()
{
    return distribution_(random_engine_);
}

Game::Game(const int player_increment, const int rotation_increment):
        move_increment_(player_increment),
        _randomNumberBetweenZeroAndTwo{RandomNumberBetween(0, 2)},
        _player(Player(player_increment, rotation_increment)) {}

SDL_Rect extractBoundingBox(SDL_Texture* texture) {
    SDL_Rect dest;
    SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);
    return dest;
}

// function which is executed in a thread
void Game::spawn(Renderer& renderer)
{
    int waitTime = this->_randomNumberBetweenZeroAndTwo();
    auto start = high_resolution_clock::now();
    int idx = 0;

    while(this->_running) {

        auto timeDelta = duration_cast<seconds>(high_resolution_clock::now() - start);
        if (timeDelta.count() > waitTime) {

            std::lock_guard<std::mutex> lock(_mutex);

            // spawn a new asteroid
            this->_asteroids.emplace_back(
                    std::make_unique<Asteroid>(idx++,4.0 * M_PI / (double) renderer.getScreenWidth(),
                                               renderer.getScreenWidth(),
                                               renderer.generateY())
            );

            waitTime = this->_randomNumberBetweenZeroAndTwo();
            start = high_resolution_clock::now();
        }

        std::this_thread::sleep_for(std::chrono::microseconds(10));
    }
}

/** Move asteroids. */
void Game::renderAsteroids(Renderer &renderer, SDL_Texture *texture) {
    std::lock_guard<std::mutex> lock(_mutex);

    for (size_t idx = 0; idx < _asteroids.size(); idx++) {
        auto rock = std::move(_asteroids.front());
        _asteroids.pop_front();
        rock->move();
        if (!renderer.outsideScreen(*rock)) {
            renderer.renderTexture(texture, *rock);
            _asteroids.emplace_back(std::move(rock));
        }
    }
}

/** Move PhaserBlasts */
void Game::renderPhaserBlasts(Renderer& renderer, SDL_Texture* texture) {
    for (size_t idx = 0; idx < _blasts.size(); idx++) {
        auto rock = std::move(_blasts.front());
        _blasts.pop_front();
        rock->move();
        if (!renderer.outsideScreen(*rock)) {
            renderer.renderTexture(texture, *rock);
            _blasts.emplace_back(std::move(rock));
        }
    }
}

void Game::renderExplosions(Renderer& renderer, SDL_Texture* texture) {
    // render the explosions
    auto it = _explosions.begin();
    while (it != _explosions.end()) {
        if (it->isFrameCountPositive()) {
            renderer.renderTexture(texture, *it);
        }
        else {
            it = _explosions.erase(it);
        }
        ++it;
    }
}

void Game::detectPlayerEnemyCollision() {
    for (auto& rock : _asteroids) {
        if (_player.collidesWith(*rock)) {
            // explosion coordinates are relative to the player texture origin
            _explosions.emplace_back(_player.getX(), _player.getY());
        }
    }
}

/**
 * The main game loop.
 */
void Game::run(Renderer& renderer, Controller& controller, int target_frame_duration) {

    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;

    auto player_texture = renderer.loadImage("../resources/starship-enterprise.png");
    auto background = renderer.loadImage("../resources/low-angle-shot-mesmerizing-starry-sky-klein.png");
    auto phaser_texture = renderer.loadImage("../resources/phaser.png");
    auto asteroid_texture = renderer.loadImage("../resources/asteroid.png");
    auto explosion_texture = renderer.loadImage("../resources/tiny-explosion.png");

    // start asteroid spawning in its own thread
    _th = std::thread(&Game::spawn, this, std::ref(renderer));

    while (_running) {

        frame_start = SDL_GetTicks();

        renderer.clear();
        controller.handleInput(renderer, _player, _blasts, _running);
        renderer.drawBackground(background);
        renderer.renderTexture(player_texture, _player);

        // move & render asteroids and phaser blasts
        renderAsteroids(renderer, asteroid_texture);
        renderPhaserBlasts(renderer, phaser_texture);

        {
            std::lock_guard<std::mutex> lock(_mutex);

            // check collisions and create explosions
            for (size_t idx = 0; idx < _asteroids.size(); idx++) {
                auto rock = std::move(_asteroids.front());
                _asteroids.pop_front();

                // iteratively filter blasts
                for (size_t idy = 0; idy < _blasts.size(); idy++) {
                    auto blast = std::move(_blasts.front());
                    _blasts.pop_front();
                    if (rock->collidesWith(*blast)) {
                        _player.incrementScore();
                        _explosions.emplace_back(Explosion(rock->getX(), rock->getY()));
                    } else _blasts.push_back(std::move(blast));
                }

                if (!rock->isHit()) _asteroids.emplace_back(std::move(rock));
            }
        }

        // check for a player enemy collision, the render the explosions
        detectPlayerEnemyCollision();
        renderExplosions(renderer, explosion_texture);

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

//        // After every second, update the window title.
//        if (frame_end - title_timestamp >= 1000) {
//            frame_count = 0;
//            title_timestamp = frame_end;
//        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration) {
            SDL_Delay(target_frame_duration - frame_duration);
        }

       // SDL_Surface* text;
        // Set color to red
        //SDL_Color color = { 250, 20, 20 };

        renderer.present(_player.getScore(), _player.getHealth());
    }
}

Player& Game::getPlayer() {
    return _player;
}

Game::~Game(){
   if (_th.joinable()) _th.join();
}

