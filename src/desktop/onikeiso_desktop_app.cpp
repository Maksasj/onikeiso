#include "onikeiso_desktop_app.h"

namespace onik {
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    void OnikeisoApp::init() {
        GLFWContext::init();

        window = WindowFactory::create_window("Onikeiso", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

        GLContext::load_opengl();
        GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

        // Loading and setting up imgui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_None;

        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window->get_backend(), true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void OnikeisoApp::load() {
        gates.push_back(std::make_shared<NotNode>());
        gates.push_back(std::make_shared<NotNode>());

        gates[0]->inputs[0].value = TRUE;
        gates[0]->inputs[0].self = gates[0].get();
        gates[0]->inputs[0].target = NULL;

        gates[0]->outputs[0].value = UNDEFINED;
        gates[0]->outputs[0].self = gates[0].get();
        gates[0]->outputs[0].target = &gates[1]->inputs[0];

        gates[1]->inputs[0].value = UNDEFINED;
        gates[1]->inputs[0].self = gates[1].get();
        gates[1]->inputs[0].target = NULL;

        gates[1]->outputs[0].value = UNDEFINED;
        gates[1]->outputs[0].self = gates[1].get();
        gates[1]->outputs[0].target = NULL;
    }

    void OnikeisoApp::draw_grid(ImDrawList* drawList) {
        const auto gridColor = IM_COL32(200, 200, 200, 40);
        const auto gridSize = 64.0f;
        const auto winPos = ImGui::GetCursorScreenPos();
        const auto canvasSz = ImGui::GetWindowSize();

        for (float x = fmodf(scrolling.x, gridSize); x < canvasSz.x; x += gridSize)
            drawList->AddLine(ImVec2(x, 0.0f) + winPos, ImVec2(x, canvasSz.y) + winPos, gridColor);
        for (float y = fmodf(scrolling.y, gridSize); y < canvasSz.y; y += gridSize)
            drawList->AddLine(ImVec2(0.0f, y) + winPos, ImVec2(canvasSz.x, y) + winPos, gridColor);
    }

    void OnikeisoApp::draw_nodes(ImDrawList* drawList) {
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

    void OnikeisoApp::run() {
        while (!window->closing()) {
            GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
            GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::SetNextWindowSize(ImVec2(700, 600), ImGuiCond_FirstUseEver);
            if (ImGui::Begin("Example: Custom Node Graph")) {

                // Initialization
                ImGuiIO& io = ImGui::GetIO();

                ImGui::SameLine();
                ImGui::BeginGroup();

                // Create our child canvas
                ImGui::Text("Hold middle mouse button to scroll (%.2f,%.2f)", scrolling.x, scrolling.y);
                ImGui::Checkbox("Show grid", &showGrid);

                if(ImGui::Button("Propogate")) {
                    propagate(gates[0].get());
                }

                if(ImGui::Button("Summon Not gate")) {
                    gates.push_back(std::make_shared<NotNode>());
                }

                if(ImGui::Button("Summon And gate")) {
                    gates.push_back(std::make_shared<AndNode>());
                }

                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
                ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(60, 60, 70, 200));
                ImGui::BeginChild("scrolling_region", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
                ImGui::PopStyleVar(); // WindowPadding
                ImGui::PushItemWidth(120.0f);

                ImDrawList* drawList = ImGui::GetWindowDrawList();

                if (showGrid) draw_grid(drawList);

                draw_nodes(drawList);

                if (ImGui::IsWindowHovered() && !ImGui::IsAnyItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Middle, 0.0f))
                    scrolling = scrolling + io.MouseDelta;

                ImGui::PopItemWidth();
                ImGui::EndChild();
                ImGui::PopStyleColor();
                ImGui::PopStyleVar();
                ImGui::EndGroup();

                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            GLFWContext::swap_buffers(*window);
            GLFWContext::poll_events();
        }
    }

    void OnikeisoApp::cleanup() {

    }

    void OnikeisoApp::terminate() {
        GLFWContext::terminate();
    }
}
