#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QObject>
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = nullptr);

    MyPushButton(QString normalImg, QString pressedImg = "");


    //
    QString normalImgPath;
    QString pressedImgPath;

    void zoom1();//jumped up

    void zoom2();//jumped down

    //overwite button press and release
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);


signals:

};

#endif // MYPUSHBUTTON_H
