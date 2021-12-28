#pragma once

#include <string>

struct City {
    std::string name = "default_city_name";
};

struct Position {
    float x = 0;
    float y = 0;
};

struct Velocity {
    float dx = 0;
    float dy = 0;
};

struct Acceleration {
    float ddx = 0;
    float ddy = 0;
};

struct Friction {
    float friction = 1.0;

    operator double() { return friction; }
};

struct Radius {
    float radius;

    operator float() { return radius; }
    operator float() const { return radius; }
};

struct Trader {};

// makeTree -> makeLeaf & makeFruit

// struct Trader {
//     Trader(Reg) {
//         Reg.emplace<Position>
//     }
// };

// struct Tree {};
