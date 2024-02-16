#include "gate_library.h"

namespace onik {
    GateLibraryWindow::GateLibraryWindow() : CommonWindow("Gate Library") {

    }

    GateLibraryWindow::~GateLibraryWindow() {

    }

    void GateLibraryWindow::run() {
        static bool open = true;

        ImGui::Begin("Gate Library", &open);

        ImGui::End();
    }
}
