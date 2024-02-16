#include "simulation_info.h"

namespace onik {
    SimulationInfoWindow::SimulationInfoWindow() : CommonWindow("Simulation Info") {

    }

    SimulationInfoWindow::~SimulationInfoWindow() {

    }

    void SimulationInfoWindow::run() {
        static bool open = true;

        ImGui::Begin("Simulation Info", &open);

        ImGui::End();
    }
}
