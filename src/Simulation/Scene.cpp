#include "Scene.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "Factories.hpp"
#include "Renders.hpp"

Scene::Scene() {
    for (auto i = 0u; i < 10u; ++i) {
        makeCity(m_Reg);
    }

    for (auto i = 0u; i < 100u; ++i) {
        makeTrader(m_Reg);
    }
}

void Scene::update() {
	updateTrader(m_Reg);
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    renderTrader(target, m_Reg);
    renderCity(target, m_Reg);
}
