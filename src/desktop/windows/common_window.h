#ifndef COMMON_WINDOW_H
#define COMMON_WINDOW_H

#include "bebone/bebone.h"

#include <string>

namespace onik {
    class CommonWindow {
    private:
        const std::string title;
        bool focused;
        bool open;

        void update_iternal_state();

    protected:
        bool start_window();

        void end_window();

    public:
        CommonWindow(const std::string& title, const bool& open = true);

        virtual ~CommonWindow();

        const bool& is_focused() const;
        const bool& is_open() const;
        bool& ref_open_flag();

        void force_open();
        void force_close();
    };
}

#endif