#ifndef SIMULATION_INFO_WINDOW
#define SIMULATION_INFO_WINDOW

#include <functional>
#include "common_window.h"

namespace onik {
    class SimulationInfoWindow : public CommonWindow {
        private:

        public:
            SimulationInfoWindow();
            ~SimulationInfoWindow();

            void run();
    };
}

#endif