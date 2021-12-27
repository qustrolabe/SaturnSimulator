#include "Factories.hpp"

#include <entt/entity/registry.hpp>

#include "Components.hpp"
#include "Utils.hpp"

entt::entity makeCity(entt::registry &reg) {
    const entt::entity e = reg.create();
    reg.emplace<City>(e);
    reg.emplace<Position>(e, RandNum(1000.f, 9000.f), RandNum(1000.f, 9000.f));
    reg.emplace<Radius>(e, RandNum(100.f, 300.f));
    return e;
}

entt::entity makeTrader(entt::registry &reg) {
    const entt::entity e = reg.create();
    reg.emplace<Trader>(e);
    reg.emplace<Position>(e, RandNum(1000.f, 9000.f), RandNum(1000.f, 9000.f));
    reg.emplace<Velocity>(e, RandNum(5.f, -5.f), RandNum(5.f, -5.f));
    reg.emplace<Acceleration>(e, 0, 0);
    reg.emplace<Friction>(e, 0.99);
    reg.emplace<Radius>(e, 20.f);
    return e;
}