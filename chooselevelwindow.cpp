#include "chooselevelwindow.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>

ChooseLevelWindow::ChooseLevelWindow(QWidget *parent) : QMainWindow(parent)
{
    //set window
    this->setFixedSize(380,570);

    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    this->setWindowTitle("Select A Level");

    //set menu
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    QMenu * startMenu = bar->addMenu("Menu");

    QAction * exitAction = startMenu->addAction("Exit");

    connect(exitAction, &QAction::triggered, [=](){
        this->close();
    });

    QSound * backSound = new QSound(":/res/BackButtonSound.wav");
    QSound * tapSound = new QSound(":/res/BackButtonSound.wav");

    //back button
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png" , ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //clicked back
    connect(backBtn, &MyPushButton::clicked,[=](){
        qDebug() <<"clicked back button";
        backSound->play();
        QTimer::singleShot(130,this,[=](){
            emit this->chooseBack();
        });
    });

    for (int i = 0 ; i <20 ; i++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(58 + i%4 * 70, 130 + i/4 * 70);

        //listen per button clicked event
        connect(menuBtn, &MyPushButton::clicked,[=](){
            tapSound->play();
            QString str = QString("You chose the %1 th").arg(1+i);
            qDebug() <<str;
            this->hide();

            //enter PlayWindow
            play = new PlayWindow(i+1);
            play->setGeometry(this->geometry());
            play->show();
            //set window position


            connect(play, &PlayWindow::chooseBack,[=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play = nullptr;
            });
        });

        QLabel * label = new  QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(1+i));
        label->move(58 + i%4 * 70, 130 + i/4 * 70);
        label->setAlignment(Qt::AlignCenter);//center
        //transparent for mouse
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    };

}

void ChooseLevelWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;

    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
//    painter.drawPixmap( (this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);
    painter.drawPixmap(20,40,pix.width()*0.7,pix.height()*0.7,pix);
}






