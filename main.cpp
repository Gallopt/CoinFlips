/**
* @projectName  Qt_CoinFlips
* @brief        A Game Of CoinFlips
* @author       Gallopt
* @date         2020-05-25
*/
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
