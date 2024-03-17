# Asteroids Game

## Submission for C++ Nanodegree Capstone

<img src="resources/readme-pic.png"  width="50%" height="50%" alt="example game play">

### How to Play

* Use arrow keys to move starship: :up_arrow:, :down_arrow:, :left_arrow:, and :right_arrow:
* Rotate the ship clockwise by pressing $\textcolor{orange}{D}$.
* Rotate the ship counterclockwise by pressing $\textcolor{orange}{A}$.
* To fire phaser blasts press the $\textcolor{orange}{space bar}$.

### Build the Project

#### Get the SDL2 dependencies.

On Ubuntu run
```
apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```

On Mac OS with [Homebrew](https://formulae.brew.sh/formula/sdl2)

```
brew install sdl2 sdl2_image sdl2_ttf
```

## Rubric Points Met

### Concurrency (2 of 5)

#### _Multithreading_
Threads are created in a few places.

* On line `102` of `Game.cpp`, Asteroids are spawned on a thread separate from main.  `Game::Spawn` is 
```c++
    // start asteroid spawning on its own thread.
    _threads.emplace_back(&Game::spawn, this, std::ref(renderer));
```     

* In the function `Game::Spawn`, collision detection is started for each new asteroid on a thread owned / managed by the asteroid.

```c++
    /** Launch checkForCollision on its own thread.  */
void Asteroid::detectCollision(...) {
this->_thread = std::thread(&Asteroid::checkForCollision, this, phaserBlasts, explosions, player, running, isInsideWindow);
}
```     

#### _Use of mutexes & locks_

* I defined `ThreadSafeQueue` to manage `PhaserBlast`, `Explosion`, and `Asteroid` collections. `ThreadSafeQueue` guarantees safe access by blocking access to the underlying queue with `lock_guard` and the mutex member `_mutex`. For example the `push` method,
```c++
template<typename T>
void ThreadSafeQueue<T>::push(T&& t) {
    std::lock_guard<std::mutex> lock(_mutex);
    _queue.emplace_back(std::move(t));
}
```
