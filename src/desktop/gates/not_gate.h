#ifndef ONIKEISO_NOT_GATE_H
#define ONIKEISO_NOT_GATE_H

#include "visual_gate.h"

static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
static inline ImVec2 operator-(const ImVec2& lhs, const ImVec2& rhs) { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }

namespace onik {
    using Vec2f = bebone::core::Vec2f;

    class NotGate : public VisualGate {
        private:
            ImVec2 size;

            ImVec2 GetInputSlotPos(int slot_no) {
                return ImVec2(pos.x, pos.y + size.y * ((float)slot_no + 1) / ((float)inputs_count + 1));
            }
            ImVec2 GetOutputSlotPos(int slot_no) const {
                return ImVec2(pos.x + size.x, pos.y + size.y * ((float)slot_no + 1) / ((float)outputs_count + 1));
            }
        public:
            NotGate() { make_not_gate(this); }
            virtual ~NotGate() { free_gate(this); }

            void draw(ImDrawList* drawList, const ImVec2& offset) override {
                ImGui::PushID("Not gate");

                const float NODE_SLOT_RADIUS = 4.0f;
                const ImVec2 NODE_WINDOW_PADDING(8.0f, 8.0f);
                ImVec2 node_rect_min = offset + get_pos();

                // Foreground
                drawList->ChannelsSetCurrent(1);
                    ImGui::SetCursorScreenPos(node_rect_min + NODE_WINDOW_PADDING);
                    ImGui::BeginGroup();
                        ImGui::Text("Not gate");
                    ImGui::EndGroup();

                size = ImGui::GetItemRectSize() + NODE_WINDOW_PADDING + NODE_WINDOW_PADDING;
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

                    for (int slot_idx = 0; slot_idx < inputs_count; slot_idx++)
                        drawList->AddCircleFilled(offset + GetInputSlotPos(slot_idx), NODE_SLOT_RADIUS, IM_COL32(150, 150, 150, 150));
                    for (int slot_idx = 0; slot_idx <outputs_count; slot_idx++)
                        drawList->AddCircleFilled(offset + GetOutputSlotPos(slot_idx), NODE_SLOT_RADIUS, IM_COL32(150, 150, 150, 150));

                ImGui::PopID();
            }
    };
};

#endif