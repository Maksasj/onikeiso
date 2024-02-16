#include "onikeiso_app.h"

int main() {
    onik::OnikeisoApp app;

    app.init();
    app.load();
    app.run();
    app.cleanup();
    app.terminate();

    return 0;
}