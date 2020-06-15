#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QTimer>
#include <QSound>

#include <mypushbutton.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(380,570);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("Coin FLips!");

    connect(ui->actionExit, &QAction::triggered,[=](){
        this->close();
    });

    QSound * startSound = new QSound(":/res/TapButtonSound.wav",this);



    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move( this->width() * 0.5 - startBtn->width() * 0.5 ,this->height() *0.6);

    //instantiation
    chooseWindow = new ChooseLevelWindow;

    //listen back button
    connect(chooseWindow , &ChooseLevelWindow::chooseBack,[=](){
        this->setGeometry(chooseWindow->geometry());
        chooseWindow->hide();
        this->show();
    });

    connect(startBtn, &MyPushButton::clicked, [=](){
        qDebug() << "Clicked start button";
        startSound->play();
        startBtn->zoom1();
//        startBtn->zoom2();

        //delay choosen window entry
        QTimer::singleShot(200,this,[=](){
            //set choosewindow position
            chooseWindow->setGeometry(this->geometry());

            //hide mainWindow
            this->hide();
            //show chooseWindow
            chooseWindow->show();


        });
    });
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;

    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,pix);

    pix.load(":res/Title.png");
    pix = pix.scaled(pix.width(),pix.height());
//    painter.drawPixmap(10,30,pix.width()*0.5,pix.height()*0.5,pix);
    painter.drawPixmap( (this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

