#ifndef ASTEROIDS_RANDOMNUMBERBETWEEN_H
#define ASTEROIDS_RANDOMNUMBERBETWEEN_H

#include <random>

class RandomNumberBetween {
public:
    RandomNumberBetween(int low, int high);

    int operator()();

private:
    std::mt19937 _random_engine;
    std::uniform_int_distribution<int> _distribution;
};

#endif //ASTEROIDS_RANDOMNUMBERBETWEEN_H
