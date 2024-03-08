#ifndef ASTEROIDS_RANDOMNUMBERBETWEEN_H
#define ASTEROIDS_RANDOMNUMBERBETWEEN_H

#include <random>

class RandomNumberBetween {
public:
    RandomNumberBetween(int low, int high);
    int operator()();
private:
    std::mt19937 random_engine_;
    std::uniform_int_distribution<int> distribution_;
};

#endif //ASTEROIDS_RANDOMNUMBERBETWEEN_H
