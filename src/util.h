#ifndef ASTEROIDS_UTIL_H
#define ASTEROIDS_UTIL_H

#include <cmath>

namespace math {

    /**
     * @param a,b must be positive integers
     */
    inline int modulo(const int a, const int b) {
        return ((a % b) + b) % b;
    }

    /**
     * @param angle is an integer representative of a degree \in [0,360]
     */
    inline double toRadians(const int angle) {
        return M_PI * static_cast<double>(angle) / 180.0;
    }
}

#endif //ASTEROIDS_UTIL_H
