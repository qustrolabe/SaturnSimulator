#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <random>

template <typename T>
T v2length(const sf::Vector2<T>& v);
template <typename T>
inline T& v2rotate(T& vec, double angle);

float RandNum(float a, float b);