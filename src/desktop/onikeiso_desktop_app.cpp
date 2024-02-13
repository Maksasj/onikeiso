#include "onikeiso_desktop_app.h"

#include "imgui_node_graph_test.h"

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
        gates.push_back(std::make_shared<NotGate>());
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
                static ImVec2 scrolling = ImVec2(0.0f, 0.0f);
                static bool showGrid = true;

                // Initialization
                ImGuiIO& io = ImGui::GetIO();

                ImGui::SameLine();
                ImGui::BeginGroup();

                // Create our child canvas
                ImGui::Text("Hold middle mouse button to scroll (%.2f,%.2f)", scrolling.x, scrolling.y);
                ImGui::SameLine(ImGui::GetWindowWidth() - 100);
                ImGui::Checkbox("Show grid", &showGrid);
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(1, 1));
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
                ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(60, 60, 70, 200));
                ImGui::BeginChild("scrolling_region", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMove);
                ImGui::PopStyleVar(); // WindowPadding
                ImGui::PushItemWidth(120.0f);

                ImDrawList* drawList = ImGui::GetWindowDrawList();

                if (showGrid) {
                    ImU32 GRID_COLOR = IM_COL32(200, 200, 200, 40);
                    float GRID_SZ = 64.0f;
                    ImVec2 win_pos = ImGui::GetCursorScreenPos();
                    ImVec2 canvas_sz = ImGui::GetWindowSize();
                    for (float x = fmodf(scrolling.x, GRID_SZ); x < canvas_sz.x; x += GRID_SZ)
                        drawList->AddLine(ImVec2(x, 0.0f) + win_pos, ImVec2(x, canvas_sz.y) + win_pos, GRID_COLOR);
                    for (float y = fmodf(scrolling.y, GRID_SZ); y < canvas_sz.y; y += GRID_SZ)
                        drawList->AddLine(ImVec2(0.0f, y) + win_pos, ImVec2(canvas_sz.x, y) + win_pos, GRID_COLOR);
                }

                drawList->ChannelsSplit(2);
                drawList->ChannelsSetCurrent(0);

                const ImVec2 offset = ImGui::GetCursorScreenPos() + scrolling;
                for(auto& gate : gates) {
                    gate->draw(drawList, offset);
                }

                drawList->ChannelsMerge();

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
