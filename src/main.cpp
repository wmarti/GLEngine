// These pragmas disable documentation warnings
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop

#include "gl_engine.h"

int main(int argc, char* argv[]) {
    GLEngine engine;
    engine.init();
    engine.run();
    engine.cleanup();
    return 0;
}