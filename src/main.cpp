#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "imgui-SFML.h"
#include "imgui.h"

// #include <iostream>
// using std::cout;
// using std::cin;
#include <vector>

class Entity : public sf::Drawable {
public:
    virtual ~Entity() = default;
};

class Wiggler : public Entity {
    sf::RectangleShape shape;

public:
    Wiggler()
        : shape({ 100.f, 100.f })
    {
        shape.setFillColor(sf::Color::Green);
        shape.move(50, 50);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(shape, states);
    }
};

class Grid : public sf::Drawable {
    sf::VertexArray grid;

public:
    Grid(int rows, int cols)
    {
        float gridH = 4000;
        float gridW = 4000;

        float rowH = gridH / rows;
        float colW = gridW / cols;

        cols++;
        rows++;
        int numLines = rows + cols;
        grid = sf::VertexArray(sf::Lines, 2 * (numLines));

        int i;
        for (i = 0; i < rows; ++i) {
            grid[i * 2].position = { 0, rowH * i };
            grid[i * 2 + 1].position = { gridW, rowH * i };
        }

        for (; i < numLines; ++i) {
            grid[i * 2].position = { colW * (i - rows), 0 };
            grid[i * 2 + 1].position = { colW * (i - rows), gridH };
        }
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(grid, states);
    }
};

class Field : public sf::Drawable {
    int rows = 1024;
    int cols = 1024;

    Grid grid;

    std::vector<Entity*> entity_array;

public:
    Field()
        : grid(rows, cols)
    {
        entity_array.push_back(new Wiggler());
        entity_array.push_back(new Wiggler());
    }

    ~Field()
    {
        for (auto& e : entity_array)
            delete e;
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(grid, states);

        for (auto& e : entity_array)
            target.draw(*e, states);
    }

    void update() { }
};

class Simulation {
    sf::RenderWindow window;
    sf::Clock deltaClock;

    sf::Color bg_color = { 100, 100, 100 };

    sf::Vector2f camera_pos = { 0, 0 };
    sf::View camera;
    float zoom_factor = 1.0f;

    Field field;

public:
    Simulation()
        : window(sf::VideoMode::getDesktopMode(), "SaturnSimulator")
    {
        window.setFramerateLimit(60);
        ImGui::SFML::Init(window);

        camera.setSize((float)window.getSize().x * zoom_factor,
            (float)window.getSize().y * zoom_factor);
    }
    ~Simulation() { ImGui::SFML::Shutdown(); }

    void start()
    {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                ImGui::SFML::ProcessEvent(window, event);

                if (event.type == sf::Event::Resized) {
                    camera.setSize(event.size.width * zoom_factor,
                        event.size.height * zoom_factor);
                }

                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            {
                ImGui::SFML::Update(window, deltaClock.restart());

                ImGui::Begin("Control Window");

                if (ImGui::BeginTable("split", 3,
                        ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ContextMenuInBody | ImGuiTableFlags_NoHostExtendX)) {
                    auto size = ImVec2(40, 40);

                    ImGui::TableNextColumn();
                    ImGui::Dummy(size);

                    ImGui::TableNextColumn();
                    if (ImGui::Button("Up", size)) {
                        camera_pos.y -= 50;
                    }

                    ImGui::TableNextColumn();
                    ImGui::Dummy(size);

                    ImGui::TableNextColumn();
                    if (ImGui::Button("Left", size)) {
                        camera_pos.x -= 50;
                    }

                    ImGui::TableNextColumn();
                    ImGui::Dummy(size);

                    ImGui::TableNextColumn();
                    if (ImGui::Button("Right", size)) {
                        camera_pos.x += 50;
                    }

                    ImGui::TableNextColumn();
                    ImGui::Dummy(size);

                    ImGui::TableNextColumn();
                    if (ImGui::Button("Down", size)) {
                        camera_pos.y += 50;
                    }

                    ImGui::TableNextColumn();
                    ImGui::Dummy(size);

                    ImGui::EndTable();
                }

                ImGui::SliderFloat("pos_x", &camera_pos.x, -100.0f, 10100.0f,
                    "pos_x = %.3f");
                ImGui::SliderFloat("pos_y", &camera_pos.y, -100.0f, 10100.0f,
                    "pos_y = %.3f");

                if (ImGui::SliderFloat("zoom", &zoom_factor, 10.0f, 0.0f,
                        "zoom = %.3f")) {
                    camera.setSize((float)window.getSize().x * zoom_factor,
                        (float)window.getSize().y * zoom_factor);
                }

                if (ImGui::Button("Zoom in")) {
                    zoom_factor *= 0.5f;

                    camera.setSize((float)window.getSize().x * zoom_factor,
                        (float)window.getSize().y * zoom_factor);
                }

                if (ImGui::Button("Zoom out")) {
                    zoom_factor *= 2.0f;

                    camera.setSize((float)window.getSize().x * zoom_factor,
                        (float)window.getSize().y * zoom_factor);
                }

                ImGui::End();
            }

            window.setView(camera);

            window.clear(bg_color);

            field.update();
            window.draw(field);

            camera.setCenter(camera_pos);
            ImGui::SFML::Render(window);
            window.display();
        }
    }
};

int main()
{
    Simulation s;
    s.start();
}
