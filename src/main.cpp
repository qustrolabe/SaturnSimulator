#include <iostream>

#include "Engine/Engine.hpp"

int COL = 0;

class Simulation : public Engine {
 public:
  void setup() override { createWindow(); }

  void draw() override {
    background((COL++) % 255);

    ImGui::Begin("Control Window");
    ImGui::End();

    rect(0, 0, 500, 500);
    circle(COL % 900, 0, 100);
    
  }
};

int main() {
  Simulation s;
  s.Start();

  return 0;
}

// ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

// const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
// ImGui::SetNextWindowPos(ImVec2(0, 0));
// ImGui::SetNextWindowSize(ImVec2(400, main_viewport->Size.y));

// // if (false)
// {
//   ImGuiWindowFlags window_flags = 0;
//   window_flags |= ImGuiWindowFlags_NoTitleBar |
//                   ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove |
//                   ImGuiWindowFlags_NoResize;

//   // ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

//   ImGui::Begin("My window", nullptr, window_flags);
//   ImGui::Text("SDQsfihasfgasfhakj");
//   ImGui::End();
// }

// // ImGui::ShowDemoWindow();