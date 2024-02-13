#ifndef ONIKEISO_DESKTOP_APP_H
#define ONIKEISO_DESKTOP_APP_H

#include "gates/gates.h"

namespace onik {
    class OnikeisoApp {
        private:
            std::shared_ptr<bebone::gfx::Window> window;

            std::vector<std::shared_ptr<VisualGate>> gates;

        public:
            void init();
            void load();
            void run();
            void cleanup();
            void terminate();
    };
}


#endif