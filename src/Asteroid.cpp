#include "Asteroid.h"

#include <iostream>

#include "ThreadSafeQueue.cpp"
#include "cmath"

Asteroid::Asteroid(const int idx, const double period, int x, int y)
    : RenderableEntity(x, y, 0, ASTEROID), _identifier(idx), _PERIOD(period), _START_Y((double)y) {
  std::cout << "creating asteroid #: " + std::to_string(_identifier) << "\n";
}

Asteroid::Asteroid(const Asteroid &other)
    : RenderableEntity(other.getX(), other.getY(), 0, ASTEROID),
      _identifier(other.getIdentifier()),
      _PERIOD(other.getPeriod()),
      _START_Y((double)other.getY()) {}

Asteroid::Asteroid(const Asteroid &&other)
    : RenderableEntity(other.getX(), other.getY(), 0, ASTEROID),
      _identifier(other.getIdentifier()),
      _PERIOD(other.getPeriod()),
      _START_Y((double)other.getY()) {}

Asteroid &Asteroid::operator=(const Asteroid &rhs) {
  if (this != &rhs) {
    _identifier = rhs.getIdentifier();
    _PERIOD     = rhs.getPeriod();
    _START_Y    = (double)rhs.getY();
    _type       = EntityType::ASTEROID;
  }
  return *this;
}

Asteroid &Asteroid::operator=(const Asteroid &&rhs) {
  if (this != &rhs) {
    _identifier = rhs.getIdentifier();
    _PERIOD     = rhs.getPeriod();
    _START_Y    = (double)rhs.getY();
    _type       = EntityType::ASTEROID;
  }
  return *this;
}

void Asteroid::move() {
  setX(getX() - _MOVE_INCREMENT);
  setY((int)(_START_Y + (double)getHeight() * cos(_PERIOD * getX())));
}

int Asteroid::getWidth() const { return w; }

int Asteroid::getHeight() const { return h; }

int Asteroid::getIdentifier() const { return _identifier; }

double Asteroid::getPeriod() const { return _PERIOD; }

/**
 * Detect collisions with a specific Asteroid instance.
 *
 * @param phaserBlasts is a collection owned by the function because it may remove phaser blasts
 * that collide with this.
 * @param player is not owned by the function and is used only check for collision with the
 * Ásteroid.
 * @param running is boolean representing the state of the game. True if the game is being played,
 * false otherwise.
 * @param isInsideWindow is a predicate for determining if the Asteroid is visible; if not no need
 * to check for collisions.
 * @return an Explosion in case of a collision, None otherwise.
 */
void Asteroid::checkForCollision(const std::shared_ptr<PhaserBlastQueuePointer> phaserBlasts,
                                 const std::shared_ptr<ExplosionQueue> explosions,
                                 const std::shared_ptr<Player> player,  // shouldn't own the player
                                 const std::shared_ptr<bool> running,   // shouldn't own the ref
                                 const std::function<bool(Asteroid &)> &isInsideWindow) {
  while (isInsideWindow(*this) && *running) {
    // register player hit by reducing health.
    if (this->collidesWith(*player)) {
      player->registerHit();
      explosions->push({this->getX(), this->getY()});

      // return eagerly so that multiple hits by this asteroid are not registered.
      return;
    }

    // any phaser blast hitting this asteroid are removed and the player's score is incremented.
    if (phaserBlasts->filter(
            [&](std::unique_ptr<PhaserBlast> &pb) { return this->collidesWith(*pb); })) {
      player->incrementScore();
      explosions->push({this->getX(), this->getY()});

      // return eagerly so that multiple hits on the same asteroid are not registered.
      return;
    }

    std::this_thread::sleep_for(std::chrono::microseconds(5));
  }
}

/** Launch checkForCollision on its own thread.  */
void Asteroid::detectCollision(const std::shared_ptr<PhaserBlastQueuePointer> &phaserBlasts,
                               const std::shared_ptr<ExplosionQueue> &explosions,
                               const std::shared_ptr<Player> &player,  // shouldn't own the player
                               const std::shared_ptr<bool> &running,   // shouldn't own the ref
                               const std::function<bool(Asteroid &)> &isInsideWindow) {
  this->_thread = std::thread(&Asteroid::checkForCollision, this, phaserBlasts, explosions, player,
                              running, isInsideWindow);
}

Asteroid::~Asteroid() {
  if (_thread.joinable()) _thread.join();
  std::cout << "destructing asteroid: " << this->getIdentifier() << "\n";
}

bool Asteroid::isHit() const { return _hit; }

bool Asteroid::collidesWith(RenderableEntity &other) {
  _hit = RenderableEntity::collidesWith(other);
  if (_hit) {
    this->setEntityType(ASTEROID_FRAGMENTS);
  }
  return _hit;
}
