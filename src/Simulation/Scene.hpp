#pragma once

#include <Components.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <Utils.hpp>
#include <entt/entt.hpp>
#include <string>

class Scene : public sf::Drawable {
   public:
    Scene();
    // ~Scene();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update();

   private:
    entt::registry m_Reg;
};
