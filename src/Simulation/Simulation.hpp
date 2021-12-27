#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "imgui-SFML.h"
#include "imgui.h"

#include <random>
#include <vector>


#include "Scene.hpp"


class Simulation {

    int framerate = 60;

    sf::RenderWindow window;
    sf::Clock deltaClock;

    sf::Color bg_color = {100, 100, 100};

    sf::Vector2f camera_pos = {5000, 5000};
    sf::View camera;
    float zoom_factor = 1.0f;

    Scene scene;

    entt::registry registry;

   public:
   	Simulation();
    
    ~Simulation();

    void start();
};