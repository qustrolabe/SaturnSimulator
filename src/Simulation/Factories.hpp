#pragma once
#include <entt/entity/fwd.hpp>

struct CityFactory {
    static entt::entity Create();
    CityFactory() = delete;
};

struct TraderFactory {
    static entt::entity Create();
    TraderFactory() = delete;
};

struct TreeFactory {
    static entt::entity Create();
    TreeFactory() = delete;
};