#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow gameMenu;

    gameMenu.show();

    return app.exec();
}
