#ifndef GATE_LIBRARY_WINDOW
#define GATE_LIBRARY_WINDOW

#include <functional>
#include "common_window.h"

namespace onik {
    class GateLibraryWindow : public CommonWindow {
        private:

        public:
            GateLibraryWindow();
            ~GateLibraryWindow() override;

            void run();
    };
}

#endif