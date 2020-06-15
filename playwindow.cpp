#include "playwindow.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <mycoin.h>
#include <dataconfig.h>
#include <mypushbutton.h>
#include <QPropertyAnimation>


//PlayWindow::PlayWindow(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayWindow::PlayWindow(int levelNum)
{
    QString str = QString("entered %1th").arg(levelNum);
    qDebug() <<str;
    this->levelIndex = levelNum;

    //initial PlayWindow
    this->setFixedSize(380,570);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("Coin Flips~");

    //set menur
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    QMenu * startMenu = bar->addMenu("Menu");

    QAction * exitAction = startMenu->addAction("Exit");

    connect(exitAction, &QAction::triggered, [=](){
        this->close();
    });

    QSound * backSound = new QSound(":/res/BackButtonSound.wav");
    //back
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png" , ":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //clicked back
    connect(backBtn, &MyPushButton::clicked,[=](){
        qDebug() <<"clicked back button in game";
        backSound->play();
        QTimer::singleShot(130,this,[=](){
            emit this->chooseBack();
        });
    });


    //show level
    QLabel * label = new QLabel;
    label->setParent(this);

    QFont font;
    font.setFamily("楷体");
    font.setPointSize(20);
    font.setBold(true);

    label->setText(QString::number(this->levelIndex));
    QString str1 = QString("Level: %1").arg(this->levelIndex);
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(30, this->height() - 60,120,50);


    QSound * flipSound = new QSound(":/res/CoinFlipSound.wav");
    QSound * winSound = new QSound(":/res/LevelWinSound.wav");

    DataConfig config;

    for(int i = 0 ;i < 4 ; i ++)
    {
        for(int j = 0 ; j < 4 ; j++)
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
    }

    //display win~
    QLabel * winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/win.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width() - tmpPix.width()) * 0.5 , -tmpPix.height());
    //display background
    for (int i = 0 ; i < 4 ; i ++) {
        for ( int j = 0 ; j < 4 ;j ++) {
            QPixmap pix = QPixmap(":/res/BoardNode.png");
            QLabel * label = new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(88+ i * 50 , 200 + j* 50);

            QString str;
            if(this->gameArray[i][j] == 1)//display golden or silver coins
                str = ":/res/Coin0001.png";
            else
                str = ":/res/Coin0008.png";


            //set Coin
            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(90+ i * 50 , 203 + j* 50);

            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];

            coinBtn[i][j] = coin;
            //flap
            connect(coin,&MyCoin::clicked,[=](){
                flipSound->play();
                coin->changeFlag();
                this->gameArray[i][j] = !this->gameArray[i][j];

                //delay for flapping
                QTimer::singleShot(200,this,[=](){
                    //flap coins around
                    if(coin->posX + 1 <= 3) //flap right coin
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();

                        this->gameArray[coin->posX+1][coin->posY] = !this->gameArray[coin->posX+1][coin->posY];
                    }
                    if(coin->posX - 1 >= 0) //flap left coin
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();

                        this->gameArray[coin->posX-1][coin->posY] = !this->gameArray[coin->posX-1][coin->posY];
                    }
                    if(coin->posY - 1 >= 0) //flap uper coin
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();

                        this->gameArray[coin->posX][coin->posY-1] = !this->gameArray[coin->posX][coin->posY-1];
                    }
                    if(coin->posY + 1 <= 3) //flap nether coin
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();

                        this->gameArray[coin->posX][coin->posY+1] = !this->gameArray[coin->posX][coin->posY+1];
                    }

                    this->isWin = true;
                    for (int i = 0; i < 4;i++)
                    {
                        for(int j = 0; j < 4;j++)
                        {
                            if(coinBtn[i][j]->flag == false)
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }
                    if(this->isWin == true)
                    {
                        qDebug() << "You got it";
                        for (int i = 0; i < 4;i++)
                        {
                            for(int j = 0; j < 4;j++)
                                coinBtn[i][j]->isWin = true;
                        }

                        winSound->play();
                        QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");

                        animation->setDuration(1000);
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+200,winLabel->width(),winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutQuart);
                        animation->start();


                    }
                });
            });
        }

    }
}

void PlayWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;

    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    painter.drawPixmap(20,40,pix.width()*0.7,pix.height()*0.7,pix);
}
