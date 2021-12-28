#include "Factories.hpp"

#include <entt/entity/registry.hpp>

#include "Components.hpp"
#include "Scene.hpp"
#include "Utils.hpp"

entt::entity CityFactory::Create() {
    auto& reg = Scene::instance()->GetRegistry();
    const entt::entity e = reg.create();
    reg.emplace<City>(e);
    reg.emplace<Position>(e, RandNum(1000.f, 9000.f), RandNum(1000.f, 9000.f));
    reg.emplace<Radius>(e, RandNum(100.f, 300.f));
    return e;
}

entt::entity TraderFactory::Create() {
    auto& reg = Scene::instance()->GetRegistry();
    const entt::entity e = reg.create();
    reg.emplace<Trader>(e);
    reg.emplace<Position>(e, RandNum(1000.f, 9000.f), RandNum(1000.f, 9000.f));
    reg.emplace<Velocity>(e, RandNum(5.f, -5.f), RandNum(5.f, -5.f));
    reg.emplace<Acceleration>(e, 0, 0);
    reg.emplace<Friction>(e, 0.99);
    reg.emplace<Radius>(e, 20.f);
    return e;
}


// entt::entity TreeFactory::Create() {
//     auto& reg = Scene::instance()->GetRegistry();
// }