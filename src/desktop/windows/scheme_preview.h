#ifndef SCHEME_PREVIEW_WINDOW
#define SCHEME_PREVIEW_WINDOW

#include <functional>
#include "common_window.h"

#include "../node/nodes.h"

namespace onik {
    class SchemePreviewWindow : public CommonWindow {
        private:
            bool showGrid = true;
            ImVec2 scrolling = ImVec2(0.0f, 0.0f);

            void draw_grid(std::vector<std::shared_ptr<Node>>& gates, ImDrawList* drawList);
            void draw_nodes(std::vector<std::shared_ptr<Node>>& gates, ImDrawList* drawList);

        public:
            SchemePreviewWindow();
            ~SchemePreviewWindow() override;

            void run(std::vector<std::shared_ptr<Node>>& gates);
    };
}

#endif