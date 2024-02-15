#include "node.h"

namespace onik {
    Node::Node() : uuid(omni::types::UUID::gen()) {

    }

    Node::~Node() {
        free_gate(this);
    }

    ImVec2 Node::get_pos() {
        return pos;
    }

    ImVec2 Node::get_input_slot_pos(int index) const {
        return { pos.x, pos.y + size.y * ((float)index + 1) / ((float)inputs_count + 1) };
    }

    ImVec2 Node::get_output_slot_pos(int index) const {
        return { pos.x + size.x, pos.y + size.y * ((float)index + 1) / ((float)outputs_count + 1) };
    }

    void Node::draw(ImDrawList* drawList, const ImVec2& offset) {
        ImGui::PushID(uuid.to_string().c_str());

        static const float NODE_SLOT_RADIUS = 5.0f;
        static const ImVec2 NODE_WINDOW_PADDING(8.0f, 8.0f);
        ImVec2 node_rect_min = offset + get_pos();

        // Foreground
        drawList->ChannelsSetCurrent(1);
        ImGui::SetCursorScreenPos(node_rect_min + NODE_WINDOW_PADDING);
        ImGui::BeginGroup();
        // ImGui::Text("Not gate");
        ImGui::EndGroup();

        ImVec2 node_rect_max = node_rect_min + size;

        // Background
        drawList->ChannelsSetCurrent(0);

        ImGui::SetCursorScreenPos(node_rect_min);
        ImGui::InvisibleButton("node", size);
        if (ImGui::IsItemHovered()) { }

        if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
            pos = pos + ImGui::GetIO().MouseDelta;

        drawList->AddRectFilled(node_rect_min, node_rect_max, IM_COL32(75, 75, 75, 255), 4.0f);
        ImGui::SetCursorScreenPos(node_rect_min);
        drawList->AddRectFilled(node_rect_min, node_rect_max, IM_COL32(75, 75, 75, 255), 4.0f);
        drawList->AddRect(node_rect_min, node_rect_max, IM_COL32(100, 100, 100, 255), 4.0f);

        static ImU32 PIN_VALUE_COLOR[] = {
            IM_COL32(0, 255, 0, 150),
            IM_COL32(0, 150, 0, 150),
            IM_COL32(100, 100, 255, 150),
            IM_COL32(255, 0, 0, 150)
        };

        for(int i = 0; i < inputs_count; ++i) {
            auto& color = PIN_VALUE_COLOR[inputs[i].value];
            drawList->AddCircleFilled(offset + get_input_slot_pos(i), NODE_SLOT_RADIUS, color);
        }

        for(int i = 0; i < outputs_count; ++i) {
            auto& color = PIN_VALUE_COLOR[outputs[i].value];

            const auto p1 = offset + get_output_slot_pos(i);

            drawList->AddCircleFilled(p1, NODE_SLOT_RADIUS, color);
        }

        ImGui::PopID();
    }
};
