#include "RandomNumberBetween.h"

RandomNumberBetween::RandomNumberBetween(int low, int high)
    : _random_engine(std::random_device{}()), _distribution(low, high) {}

int RandomNumberBetween::operator()() { return _distribution(_random_engine); }
