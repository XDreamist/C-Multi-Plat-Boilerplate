#include <iostream>

#ifdef QT_PRESENT
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#elif IMGUI_PRESENT
#include "imguirunner.h"
#endif

int main(int argc, char* argv[])
{
#ifdef QT_PRESENT
    QApplication app(argc, argv);

    // Create the main window
    QWidget window;
    window.setWindowTitle("Enhanced Qt Window");
    window.resize(400, 300);

    // Create a vertical layout
    QVBoxLayout *layout = new QVBoxLayout;

    // Add a label to the layout
    QLabel *title = new QLabel("Welcome to the Enhanced Window!");
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    // Add a button to the layout
    QPushButton *button = new QPushButton("Click Me");
    button->setStyleSheet("border-radius: 10px; border: 1px solid #151515; background-color: #151515; padding: 2px 0");
    layout->addWidget(button);

    // Set the layout to the window
    window.setLayout(layout);

    // Show the window
    window.show();

    return app.exec();
#elif IMGUI_PRESENT
    ImGuiRunner* imRunner = new ImGuiRunner;
    return imRunner->run();
#endif
}
