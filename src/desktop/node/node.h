#ifndef ONIKEISO_NODE_H
#define ONIKEISO_NODE_H

#include "bebone/bebone.h"

extern "C" {
    #include "onikeiso.h"
}

static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

namespace onik {
    using Vec2f = bebone::core::Vec2f;

    class Node : public Gate {
        private:
            omni::types::UUID uuid;

            ImVec2 pos = {0.0, 0.0};
            ImVec2 size = {100, 50};

        public:
            Node();
            virtual ~Node();

            ImVec2 get_pos();

            ImVec2 get_input_slot_pos(int slot_no) const;
            ImVec2 get_output_slot_pos(int slot_no) const;

            virtual void draw(ImDrawList* drawList, const ImVec2& offset);
    };
};

#endif