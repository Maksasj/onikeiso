#ifndef ONIKEISO_DESKTOP_APP_H
#define ONIKEISO_DESKTOP_APP_H

#include "onikeiso.h"
#include "bebone/bebone.h"

namespace onik {
    class OnikeisoApp {
        private:
            std::shared_ptr<bebone::gfx::Window> window;

            std::vector<std::shared_ptr<Gate>> gates;

        public:
            void init();
            void load();
            void run();
            void cleanup();
            void terminate();
    };
}


#endif