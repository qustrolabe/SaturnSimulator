#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <entt/entt.hpp>

#include "Components.hpp"
#include "Utils.hpp"

void renderCity(sf::RenderTarget& target, const entt::registry& reg) {
    const auto view = reg.view<const City, const Position, const Radius>();

    sf::CircleShape circle;

    for (const auto e : view) {
        const auto& pos = view.get<const Position>(e);
        const auto& radius = view.get<const Radius>(e);

        circle.setRadius(radius);
        circle.setPosition(pos.x, pos.y);
        circle.setOrigin(radius, radius);
        circle.setFillColor({100, 200, 200});

        target.draw(circle);
    }
}

void renderTrader(sf::RenderTarget& target, const entt::registry& reg) {
    const auto view = reg.view<const Trader, const Position, const Radius>();

    sf::CircleShape circle;

    for (const auto e : view) {
        const auto& pos = view.get<const Position>(e);
        const auto& radius = view.get<const Radius>(e);

        circle.setRadius(radius);
        circle.setPosition(pos.x, pos.y);
        circle.setOrigin(radius, radius);
        circle.setFillColor({200, 200, 100});

        target.draw(circle);
    }
}

// MOVE THIS TO ANOTHER PLACE
void updateTrader(entt::registry& reg) {
    auto view = reg.view<Position, Velocity, Acceleration, Friction, Radius,
                         const Trader>();
    for (auto e : view) {
        auto& pos = view.get<Position>(e);
        auto& vel = view.get<Velocity>(e);
        auto& acc = view.get<Acceleration>(e);
        auto& friction = view.get<Friction>(e);
        auto& radius = view.get<Radius>(e);

        pos.x += vel.dx;
        pos.y += vel.dy;

        if (pos.x + radius > 10000.f) {
            pos.x = 10000.f - radius;
        }
        if (pos.x < radius) {
            pos.x = radius;
        }
        if (pos.y + radius > 10000.f) {
            pos.y = 10000.f - radius;
        }
        if (pos.y < radius) {
            pos.y = radius;
        }

        vel.dx += acc.ddx;
        vel.dy += acc.ddy;

        vel.dx *= friction;
        vel.dy *= friction;

        auto cities = reg.view<Position, const City>();
        Position nearest{100000, 100000};
        for (auto city : cities) {
            const auto& city_pos = cities.get<Position>(city);
            if ((city_pos.x - pos.x) * (city_pos.x - pos.x) +
                    (city_pos.y - pos.y) * (city_pos.y - pos.y) <
                (nearest.x - pos.x) * (nearest.x - pos.x) +
                    (nearest.y - pos.y) * (nearest.y - pos.y)) {
                nearest.x = city_pos.x;
                nearest.y = city_pos.y;
            }
        }

        if ((nearest.x - pos.x) * (nearest.x - pos.x) +
                (nearest.y - pos.y) * (nearest.y - pos.y) <
            90000) {
            pos.x = RandNum(1000, 9000);
            pos.y = RandNum(1000, 9000);
        } else {
            acc.ddx = (nearest.x - pos.x) * 0.001;
            acc.ddy = (nearest.y - pos.y) * 0.001;
        }
    }
}