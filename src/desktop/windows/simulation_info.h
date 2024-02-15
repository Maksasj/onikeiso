#ifndef SIMULATION_INFO_WINDOW
#define SIMULATION_INFO_WINDOW

#include <functional>
#include "common_window.h"

namespace onik {
    class SimulationInfoWindow : public CommonWindow {
        private:

        public:
            SimulationInfoWindow() : CommonWindow("Main Dockspace") {

            }

            ~SimulationInfoWindow() override {

            }

            void run() {
                static bool open = true;

                ImGui::Begin("Simulation Info", &open);

                ImGui::End();
            }
    };
}

#endif