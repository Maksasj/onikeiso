#ifndef ONIKEISO_APP_H
#define ONIKEISO_APP_H

#include "node/nodes.h"

#include "windows/windows.h"

namespace onik {
    class OnikeisoApp {
        private:
            std::shared_ptr<bebone::gfx::Window> window;

            std::vector<std::shared_ptr<Node>> gates;

            std::shared_ptr<MainDockspaceWindow> mainDockspaceWindow;
            std::shared_ptr<GateLibraryWindow> gateLibraryWindow;
            std::shared_ptr<SchemePreviewWindow> schemePreviewWindow;
            std::shared_ptr<SimulationInfoWindow> simulationInfoWindow;

        public:
            void init();
            void load();
            void run();
            void cleanup();
            void terminate();
    };
}


#endif