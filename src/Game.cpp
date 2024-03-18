#include "Game.h"

#include <chrono>
#include <iostream>

#include "ThreadSafeQueue.cpp"

using namespace std::chrono;

Game::Game(std::shared_ptr<Player> &player, std::shared_ptr<PhaserBlastQueuePointer> phaserBlasts)
    : _running(std::make_shared<bool>(true)),
      _player(player),
      _explosions(std::make_shared<ExplosionQueue>()),
      _phaserBlasts(phaserBlasts),
      generateWaitTime{RandomNumberBetween(1, 3)} {}

Game::Game(const int player_increment, const int rotation_increment)
    : _running(std::make_shared<bool>(true)),
      _explosions(std::make_shared<ExplosionQueue>()),
      _phaserBlasts(std::make_shared<PhaserBlastQueuePointer>()),
      generateWaitTime{RandomNumberBetween(1, 3)} {
  _player = std::make_shared<Player>(player_increment, rotation_increment, _phaserBlasts);
}

/** Spawn Asteroids.
 * @param renderer is a reference to the Renderer. Used
 * */
void Game::spawn(Renderer &renderer) {
  int waitTime = this->generateWaitTime();
  auto start   = high_resolution_clock::now();
  int idx      = 0;

  while (*_running) {
    auto timeDelta = duration_cast<seconds>(high_resolution_clock::now() - start);
    if (timeDelta.count() > waitTime) {
      // spawn a new asteroid on its own thread with reference to the player so it can detect
      // collisions. The asteroid would move with each frame but the detection thread would wait
      // until a collision is registered.
      auto asteroid =
          std::make_shared<Asteroid>(idx++, 4.0 * M_PI / (double)renderer.getScreenWidth(),
                                     renderer.getScreenWidth(), renderer.generateY());

      // kick off asteroid collision checking.
      asteroid->detectCollision(_phaserBlasts, _explosions, _player, _running,
                                [&](Asteroid &rock) { return !renderer.outsideScreen(rock); });
      _asteroids.push(std::move(asteroid));

      waitTime = generateWaitTime();
      start    = high_resolution_clock::now();
    }

    std::this_thread::sleep_for(std::chrono::microseconds(100));
  }
}

/** Render and move Asteroids. */
void Game::renderAsteroids(const Renderer &renderer) {
  _asteroids.foreach ([&](std::shared_ptr<Asteroid> &rock) {
    rock->move();
    renderer.renderTexture(*rock);
  });
  _asteroids.filter([&](std::shared_ptr<Asteroid> &rock) { return renderer.outsideScreen(*rock); });
}

/** Move and render PhaserBlasts */
void Game::renderPhaserBlasts(const Renderer &renderer) {
  _phaserBlasts->foreach ([&](std::unique_ptr<PhaserBlast> &b) {
    b->move();
    renderer.renderTexture(*b);
  });
  _phaserBlasts->filter(
      [&](std::unique_ptr<PhaserBlast> &b) { return renderer.outsideScreen(*b); });
}

/** Move and render　Explosions */
void Game::renderExplosions(const Renderer &renderer) {
  _explosions->filter([&](Explosion &ex) { return !ex.isFrameCountPositive(); });
  _explosions->foreach ([&](Explosion &ex) { renderer.renderTexture(ex); });
}

/** The main game loop. */
void Game::run(Renderer &renderer, const std::shared_ptr<Controller> &controller,
               uint32_t target_frame_duration) {
  // display score in orange
  SDL_Color color = {255, 165, 25};

  uint32_t frame_start, frame_end, frame_duration;

  // start asteroid spawning on its own thread.
  _threads.emplace_back(&Game::spawn, this, std::ref(renderer));

  while (*_running && _state == RUNNING) {
    frame_start = SDL_GetTicks();

    renderer.clear();
    controller->handleInput(renderer, *_running);
    renderer.drawBackground();
    renderer.renderHealth(_player->getHealth());
    renderer.renderTexture(*_player);

    // move & render asteroids, phaser blasts, and explosions
    renderAsteroids(renderer);
    renderPhaserBlasts(renderer);
    renderExplosions(renderer);
    renderer.renderScore("score:" + std::to_string(_player->getScore()), color);

    // GAME OVER if player has no more health
    if (_player->getHealth() < 1) {
      renderer.gameOverMessage(color);
    }

    renderer.present((int)_threads.size() + _asteroids.size());

    // Keep track of how long each loop through the input/update/render cycle takes.
    frame_end      = SDL_GetTicks();
    frame_duration = frame_end - frame_start;

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

Game::~Game() {
  *_running = false;
  for (auto &th : _threads) th.join();
}
