#include <iostream>

#include "imguirunner.h"

int main(int argc, char* argv[])
{
    ImGuiRunner* imRunner = new ImGuiRunner;
    return imRunner->run();
}