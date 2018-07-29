
#include "color.h"

using namespace std;

bool color_enabled(bool toggle, bool enable) {
    static bool enable_coloration = false;
    if (toggle) {
        enable_coloration = enable;
    }
    return enable_coloration;
}

void set_color(int code) {
    if (color_enabled(false, false)) {
#if defined(_WIN32)
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, static_cast<WORD>(code));
#else
        cout << ANSI_COLOR_STRINGS[code];
#endif
    }
}

void reset_color() {
    if (color_enabled(false, false)) {
#if defined(_WIN32)
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, static_cast<WORD>(WHITE_CODE));
#else
        cout << ANSI_COLOR_STRINGS[RESET_CODE];
#endif
    }
}
