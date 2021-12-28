#include "Scene.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

#include "Factories.hpp"
#include "Renders.hpp"
#include "imgui-SFML.h"
#include "imgui.h"

Scene* Scene::sInstance = nullptr;

Scene::Scene() {
    if (sInstance == nullptr) sInstance = this;

    for (auto i = 0u; i < 10u; ++i) {
        CityFactory::Create();
    }

    for (auto i = 0u; i < 100u; ++i) {
        TraderFactory::Create();
    }

    for (auto i = 0u; i < 100u; ++i) {
        // TreeFactory::Create();
    }
}

void Scene::update() { updateTrader(m_Reg); }

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    renderTrader(target, m_Reg);
    renderCity(target, m_Reg);

    ImGui::Begin("EnTT Window");
    ImGui::Text("Entites:");

    m_Reg.each([](auto entity) { ImGui::Text("Entity:%d", (int)entity); });

    ImGui::End();
}
