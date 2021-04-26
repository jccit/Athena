#include "pch.h"

#include "BootParams.h"
#include "Engine.h"

#include <Utils/MessageBox.h>

#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#else
#include <argh.h>
#endif

Engine* engineInst;

#ifdef __EMSCRIPTEN__
void emLoop()
{
    engineInst->loop();
}
#endif

int main(int argc, char* argv[])
{
#ifndef __EMSCRIPTEN__
    argh::parser cmdl({"-w", "-h"});
    cmdl.parse(argv);

    // Check for dev mode
    if (cmdl[{ "-dev" }])
        g_devMode = true;

    if (cmdl("-w")) {
        try {
            int overrideWidth = std::stoi(cmdl("-w").str());
            g_overrideWidth = overrideWidth;
        } catch (std::invalid_argument &e) {}
    }

    if (cmdl("-h")) {
        try {
            int overrideHeight = std::stoi(cmdl("-h").str());
            g_overrideHeight = overrideHeight;
        } catch (std::invalid_argument &e) {}
    }

#else
    g_devMode = true;
#endif

    engineInst = new Engine();

    if (const int result = engineInst->init() != 0) {
        MsgBox_Error("Failed to init");
        return result;
    }

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(emLoop, 0, 1);
#else
    while (engineInst->loop()) { }
#endif

    engineInst->shutdown();

    return 0;
}