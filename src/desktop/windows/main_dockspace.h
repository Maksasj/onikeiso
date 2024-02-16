#ifndef _MAIN_DOCKSPACE_WINDOW_H_
#define _MAIN_DOCKSPACE_WINDOW_H_

#include <functional>
#include "common_window.h"

namespace onik {
    class MainDockspaceWindow : public CommonWindow {
        private:

        public:
            MainDockspaceWindow();
            ~MainDockspaceWindow();

            void run(const std::function<void(void)>& dockSpaceBody);
    };
}

#endif