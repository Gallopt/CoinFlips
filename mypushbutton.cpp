#include "mypushbutton.h"
#include <QDebug>
#include <QPropertyAnimation>


//MyPushButton::MyPushButton(QWidget *parent) : QWidget(parent)
//{

//}


MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressedImgPath = pressImg;

    QPixmap pix;

    bool ret = pix.load(normalImg);
    if(!ret)
    {
        qDebug() <<" Image loading failed";
    }

    this->setFixedSize(pix.width(),pix.height());
    //set unnormal picture style
    this->setStyleSheet("QPushButton{border:0px}");

    //
    this->setIcon(pix);

    this->setIconSize(QSize(pix.width(),pix.height()));

}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressedImgPath != "")
    {
        QPixmap pix;

        bool ret = pix.load(this->pressedImgPath);
        if(!ret)
        {
            qDebug() <<" Image loading failed";
        }

        this->setFixedSize(pix.width(),pix.height());
        //set unnormal picture style
        this->setStyleSheet("QPushButton{border:0px}");

        //
        this->setIcon(pix);

        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mousePressEvent(e);

}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressedImgPath != "")
    {
        QPixmap pix;

        bool ret = pix.load(this->normalImgPath);
        if(!ret)
        {
            qDebug() <<" Image loading failed";
        }

        this->setFixedSize(pix.width(),pix.height());
        //set unnormal picture style
        this->setStyleSheet("QPushButton{border:0px}");

        //
        this->setIcon(pix);

        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    return QPushButton::mouseReleaseEvent(e);
}

void MyPushButton::zoom1()
{
    //create animation
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    //set animation duration
    animation->setDuration(200);

    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void MyPushButton::zoom2()
{
    //create animation
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    //set animation duration
    animation->setDuration(200);

    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}


