#pragma once

// STD
#include <chrono>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <thread>
#include <utility>

// SFML

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

// ImGui
#include "imgui-SFML.h"
#include "imgui.h"

class Engine {
 public:
  Engine() = default;

  void update();

  void drawThread();

 public:
  void createWindow();

  void push();
  void pop();

 public:
  // USER DEFINED FUNCTIONS
  virtual void setup() = 0;
  virtual void draw() = 0;

  void Start();

  void background(uint8_t c);
  // void background(uint8_t r,uint8_t g,uint8_t b);
  void circle(float x, float y, float r);
  void rect(float x, float y, float w, float h);

 private:
  std::unique_ptr<sf::RenderWindow> window{nullptr};

  bool isActive = false;
  sf::Clock clock;

  sf::View camera;
  sf::Vector2f camera_pos{0,0};
  float zoom_factor = 1;

 public:
  float delay = 0;

  // Painter params section
 private:
  // std::stack<sf::Transform> transformStack;
  // std::stack<SceneParams> transformStack;

  struct {
    sf::CircleShape circle;
    sf::RectangleShape rectangle;
  } primitives;

  struct {
    sf::Color fillColor{sf::Color::White};
    sf::Color strokeColor{sf::Color::Black};
    sf::Color backgroundColor{sf::Color::Black};
    float strokeWidth = 1;
  } params;
};

void Engine::createWindow() {
  if (window) throw std::logic_error("Window already exists.");

  sf::RenderWindow* render_window =
      new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "SaturnSimulator");

  window = std::unique_ptr<sf::RenderWindow>(render_window);

  window->setFramerateLimit(60);
  ImGui::SFML::Init(*window);
}

void Engine::update() {
  auto time = clock.restart();
  ImGui::SFML::Update(*window, time);
  delay = time.asSeconds();
  draw();
}

void Engine::drawThread() {
  setup();

  if (!window) {
    createWindow();
  }

  camera.setCenter(camera_pos);

  while (isActive) {
    sf::Event event;
    while (window->pollEvent(event)) {
      ImGui::SFML::ProcessEvent(*window, event);

      if (event.type == sf::Event::Resized) {
        camera.setSize(event.size.width * zoom_factor,
                       event.size.height * zoom_factor);
      }

      if (event.type == sf::Event::Closed) {
        window->close();
        return;
      }
    }

    window->setView(camera);
    update();
    ImGui::SFML::Render(*window);
    window->display();
  }

  ImGui::SFML::Shutdown();
}

void Engine::Start() {
  isActive = true;
  auto t = std::thread(&Engine::drawThread, this);

  t.join();
  isActive = false;
}

void Engine::background(uint8_t c) { window->clear({c, c, c}); }
void Engine::circle(float x, float y, float r) {
  auto& circle = primitives.circle;

  circle.setFillColor(params.fillColor);
  circle.setOutlineColor(params.strokeColor);
  circle.setOutlineThickness(params.strokeWidth);

  circle.setRadius(r);
  circle.setPosition(x, y);
  window->draw(circle);
}

void Engine::rect(float x, float y, float w, float h) {
  auto& rectangle = primitives.rectangle;

  rectangle.setFillColor(params.fillColor);
  rectangle.setOutlineColor(params.strokeColor);
  rectangle.setOutlineThickness(params.strokeWidth);

  rectangle.setPosition({x, y});
  rectangle.setSize({w, h});
  window->draw(rectangle);
}

// TODO

// ScreenWidth();
// ScreenHeight();
// createWindow(400, 400);