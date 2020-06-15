#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H

#include <QMainWindow>
#include <mycoin.h>
#include <QSound>


class PlayWindow : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayWindow(QWidget *parent = nullptr);
    PlayWindow(int levelNum);

    int levelIndex;

    void paintEvent(QPaintEvent *);

    int gameArray[4][4];//per level

    MyCoin * coinBtn[4][4];

    bool isWin;
    QSound * backSound;
    QSound * flipSound;
    QSound * winSound;

signals:
    void chooseBack();

};

#endif // PLAYWINDOW_H
