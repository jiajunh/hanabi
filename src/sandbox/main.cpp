#include "Hanabi.h"
#include "Sandbox.h"
#include "pch.h"

// #include "Core/HanabiAssert.h"

int main() {
    // initiate Logger
    Hanabi::Log logger = Hanabi::Log();
    logger.Init();

    HANABI_CORE_INFO("================Start================");

    SandboxApp *app = new SandboxApp();
    app->Run();
    delete app;

    return 0;
}