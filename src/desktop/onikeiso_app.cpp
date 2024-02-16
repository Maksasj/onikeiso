#include "onikeiso_app.h"

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
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window->get_backend(), true);
        ImGui_ImplOpenGL3_Init("#version 330");

        mainDockspaceWindow = std::make_shared<MainDockspaceWindow>();

        gateLibraryWindow = std::make_shared<GateLibraryWindow>();
        schemePreviewWindow = std::make_shared<SchemePreviewWindow>();
        simulationInfoWindow = std::make_shared<SimulationInfoWindow>();
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

    void OnikeisoApp::run() {
        while (!window->closing()) {
            GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
            GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            mainDockspaceWindow->run([&]() {
                gateLibraryWindow->run();
                schemePreviewWindow->run(gates);
                simulationInfoWindow->run();
            });

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
