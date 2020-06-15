#ifndef CHOOSELEVELWINDOW_H
#define CHOOSELEVELWINDOW_H

#include <QMainWindow>
#include "playwindow.h"
#include <QSound>

class ChooseLevelWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelWindow(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);

    //
    PlayWindow * play = NULL;

    QSound * backSound;
    QSound * tapSound;

signals:
    void chooseBack();

};

#endif // CHOOSELEVELWINDOW_H
