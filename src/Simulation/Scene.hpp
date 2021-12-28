#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <entt/entt.hpp>
#include <string>

#include "Components.hpp"
#include "Utils.hpp"

class Scene : public sf::Drawable {
   public:
    Scene();
    // ~Scene();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update();

   private:
    static Scene* sInstance;
    entt::registry m_Reg;
   public:
    entt::registry& GetRegistry() { return m_Reg; }
    static Scene* instance() { return sInstance; }

};
