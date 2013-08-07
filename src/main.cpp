#include <QApplication>

#include <iostream>
#include <cstdlib>

#include "Editor.hpp"

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    Editor editor(std::vector<std::string>(argv, argv + argc));
    return app.exec();
}
