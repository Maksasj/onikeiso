#ifndef ONIKEISO_VISUAL_GATE_H
#define ONIKEISO_VISUAL_GATE_H

#include "bebone/bebone.h"

extern "C" {
    #include "onikeiso.h"
}

namespace onik {
    class VisualGate : public Gate {
        private:

        public:
            ImVec2 pos = {0.0, 0.0};

            virtual void draw(ImDrawList* drawList, const ImVec2& offset) = 0;

            ImVec2 get_pos() {
                return pos;
            }
    };
};

#endif