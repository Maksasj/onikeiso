#ifndef GATE_LIBRARY_WINDOW
#define GATE_LIBRARY_WINDOW

#include <functional>
#include "common_window.h"

namespace onik {
    class GateLibraryWindow : public CommonWindow {
        private:

        public:
            GateLibraryWindow() : CommonWindow("Main Dockspace") {

            }

            ~GateLibraryWindow() override {

            }

            void run() {
                static bool open = true;

                ImGui::Begin("Gate Library", &open);

                ImGui::End();
            }
    };
}

#endif