#ifndef ONIKEISO_DESKTOP_APP_H
#define ONIKEISO_DESKTOP_APP_H

#include "node/nodes.h"

namespace onik {
    class OnikeisoApp {
        private:
            std::shared_ptr<bebone::gfx::Window> window;

            std::vector<std::shared_ptr<Node>> gates;

            ImVec2 scrolling = ImVec2(0.0f, 0.0f);

            void draw_grid(ImDrawList* drawList);
            void draw_nodes(ImDrawList* drawList);

            bool showGrid = true;

        public:
            void init();
            void load();
            void run();
            void cleanup();
            void terminate();
    };
}


#endif