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
        circle.setFillColor({100,200,200});

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
        circle.setFillColor({200,200,100});

        target.draw(circle);
    }
}

// MOVE THIS TO ANOTHER PLACE
void updateTrader(entt::registry& reg) {
    auto view = reg.view<Position, Velocity, const Trader>();
    for (auto e : view) {
    	auto& pos = view.get<Position>(e);
    	const auto& vel = view.get<Velocity>(e);

    	pos.x += vel.dx;
    	pos.y += vel.dy;
    }
}