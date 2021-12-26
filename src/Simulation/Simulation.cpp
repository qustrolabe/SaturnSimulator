#include "Simulation.hpp"

Simulation::Simulation()
    : window(sf::VideoMode::getDesktopMode(), "SaturnSimulator") {
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    camera.setSize((float)window.getSize().x * zoom_factor,
                   (float)window.getSize().y * zoom_factor);
}

Simulation::~Simulation() { ImGui::SFML::Shutdown(); }

void Simulation::start() {
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
                                  ImGuiTableFlags_SizingFixedFit |
                                      ImGuiTableFlags_ContextMenuInBody |
                                      ImGuiTableFlags_NoHostExtendX)) {
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

            ImGui::SameLine();
            if (ImGui::Button("Zoom out")) {
                zoom_factor *= 2.0f;

                camera.setSize((float)window.getSize().x * zoom_factor,
                               (float)window.getSize().y * zoom_factor);
            }

            // if (ImGui::Button("Delete all entities")) {
            //     field.delete_entities();
            // }

            ImGui::End();
        }


        scene.update();

        window.setView(camera);

        window.clear(bg_color);

        window.draw(scene);

        camera.setCenter(camera_pos);
        ImGui::SFML::Render(window);
        window.display();
    }
}