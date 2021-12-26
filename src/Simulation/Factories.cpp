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
    reg.emplace<Velocity>(e, RandNum(2.f, -2.f), RandNum(2.f, -2.f));
    reg.emplace<Radius>(e, 100.f);
    return e;
}