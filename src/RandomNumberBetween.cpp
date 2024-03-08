#include "RandomNumberBetween.h"

RandomNumberBetween::RandomNumberBetween(int low, int high): random_engine_(std::random_device{}()), distribution_(low,high) {}

int RandomNumberBetween::operator()()
{
    return distribution_(random_engine_);
}
