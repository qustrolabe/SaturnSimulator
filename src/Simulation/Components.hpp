#pragma once

#include <string>

struct City {
    std::string name = "default_city_name";
};

struct Position {
    float x;
    float y;
};

struct Velocity {
    float dx;
    float dy;
};
struct Radius {
    float radius;

    operator float() { return radius; }
    operator float() const { return radius; }
};



struct Trader {

};