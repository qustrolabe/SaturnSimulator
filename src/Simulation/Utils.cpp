#include "Utils.hpp"

template <typename T>
T v2length(const sf::Vector2<T>& v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

template <typename T>
inline T& v2rotate(T& vec, double angle) {
    const double newX = vec.x * cos(angle) - vec.y * sin(angle);
    const double newY = vec.x * sin(angle) + vec.y * cos(angle);
    vec.x = newX;
    vec.y = newY;

    return vec;
}

float RandNum(float a, float b) {
    static std::random_device rd;
    static std::default_random_engine gen(rd());
    std::uniform_real_distribution<float> distrib(a, b);

    return distrib(gen);
}