#ifndef SCHEME_PREVIEW_WINDOW
#define SCHEME_PREVIEW_WINDOW

#include <functional>
#include "common_window.h"

namespace onik {
    class SchemePreviewWindow : public CommonWindow {
        private:
            bool showGrid = true;
            ImVec2 scrolling = ImVec2(0.0f, 0.0f);

            void draw_grid(std::vector<std::shared_ptr<Node>>& gates, ImDrawList* drawList) {
                const auto gridColor = IM_COL32(200, 200, 200, 40);
                const auto gridSize = 64.0f;
                const auto winPos = ImGui::GetCursorScreenPos();
                const auto canvasSz = ImGui::GetWindowSize();

                for (float x = fmodf(scrolling.x, gridSize); x < canvasSz.x; x += gridSize)
                    drawList->AddLine(ImVec2(x, 0.0f) + winPos, ImVec2(x, canvasSz.y) + winPos, gridColor);
                for (float y = fmodf(scrolling.y, gridSize); y < canvasSz.y; y += gridSize)
                    drawList->AddLine(ImVec2(0.0f, y) + winPos, ImVec2(canvasSz.x, y) + winPos, gridColor);
            }

            void draw_nodes(std::vector<std::shared_ptr<Node>>& gates, ImDrawList* drawList) {
                drawList->ChannelsSplit(2);

                const ImVec2 offset = ImGui::GetCursorScreenPos() + scrolling;
                for(auto& gate : gates) {
                    gate->draw(drawList, offset);
                }

                for(auto& gate : gates) {
                    for(int i = 0; i < gate->outputs_count; ++i) {
                        auto pin = gate->outputs[i].target;
                        if(!pin)
                            continue;

                        auto self = (Node*) gate->outputs[i].target->self;
                        if(!self)
                            continue;

                        static ImU32 PIN_VALUE_COLOR[] = {
                                IM_COL32(0, 255, 0, 150),
                                IM_COL32(0, 150, 0, 150),
                                IM_COL32(100, 100, 255, 150),
                                IM_COL32(255, 0, 0, 150)
                        };

                        auto& color = PIN_VALUE_COLOR[gate->outputs[i].value];

                        const auto p1 = offset + gate->get_output_slot_pos(0); // Todo this
                        const auto p2 = offset + self->get_input_slot_pos(0); // Todo this

                        drawList->AddBezierCubic(p1, p1 + ImVec2(+50, 0), p2 + ImVec2(-50, 0), p2, color, 3.0f);
                    }
                }

                drawList->ChannelsMerge();
            }

        public:
            SchemePreviewWindow() : CommonWindow("Main Dockspace") {

            }

            ~SchemePreviewWindow() override {

            }

            void run(std::vector<std::shared_ptr<Node>>& gates) {
                if (ImGui::Begin("Example: Custom Node Graph")) {
                    ImGui::BeginGroup();

                    ImGui::Checkbox("Show grid", &showGrid);

                    if(ImGui::Button("Propogate"))
                        propagate(gates[0].get());

                    if(ImGui::Button("Summon Not gate"))
                        gates.push_back(std::make_shared<NotNode>());

                    if(ImGui::Button("Summon And gate"))
                        gates.push_back(std::make_shared<AndNode>());

                    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
                    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(60, 60, 70, 200));
                    ImGui::BeginChild("scrolling_region", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
                    ImGui::PopStyleVar(); // WindowPadding
                    ImGui::PushItemWidth(120.0f);

                    ImDrawList* drawList = ImGui::GetWindowDrawList();

                    if (showGrid) draw_grid(gates, drawList);

                    draw_nodes(gates, drawList);

                    if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 0.0f))
                        scrolling = scrolling + ImGui::GetIO().MouseDelta;

                    ImGui::PopItemWidth();
                    ImGui::EndChild();
                    ImGui::PopStyleColor();
                    ImGui::PopStyleVar();
                    ImGui::EndGroup();

                    ImGui::End();
                }
            }
    };
}

#endif