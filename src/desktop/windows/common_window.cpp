#include "common_window.h"

namespace onik {
    void CommonWindow::update_iternal_state() {
        focused = ImGui::IsWindowFocused();
    }

    bool CommonWindow::start_window() {
        if(open == false)
            return false;

        if(ImGui::Begin(title.c_str(), &open)) {
            update_iternal_state();
            return true;
        }

        ImGui::End();
        return false;
    }

    void CommonWindow::end_window() {
        ImGui::End();
    }

    CommonWindow::CommonWindow(const std::string& title, const bool& open)
            : title(title),
              focused(false),
              open(open) {

    }

    CommonWindow::~CommonWindow() {

    }

    const bool& CommonWindow::is_focused() const {
        return focused;
    }

    const bool& CommonWindow::is_open() const {
        return open;
    }

    bool& CommonWindow::ref_open_flag() {
        return open;
    }

    void CommonWindow::force_open() {
        open = true;
    }

    void CommonWindow::force_close() {
        open = false;
    }
}
