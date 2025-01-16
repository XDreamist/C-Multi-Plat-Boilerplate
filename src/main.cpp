#include <iostream>

#ifdef QT_PRESENT
    #include <QApplication>
    #include <QWidget>
#else
    #include "imguirunner.h"
#endif

int main(int argc, char* argv[])
{
    #ifdef QT_PRESENT
        QApplication app(argc, argv);
        
        QWidget window;
        window.setWindowTitle("Basic Qt Window");
        window.resize(400, 300);
        window.show();
        
        return app.exec();
    #else
        ImGuiRunner* imRunner = new ImGuiRunner;
        return imRunner->run();
    #endif
}