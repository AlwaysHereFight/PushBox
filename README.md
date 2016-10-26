# PushBox
a sample game of PushBox

pushbox.pro

#-------------------------------------------------
#
# Project created by QtCreator 2016-9-30T20:23:11
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PushBox
TEMPLATE = app


SOURCES += main.cpp\
        mainWidget.cpp \
    GameWidget.cpp

HEADERS  += mainWidget.h \
    GameWidget.h

RESOURCES += \
    pushboxresource.qrc \


GameWidget.h

#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPalette>
#include <QIcon>
#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QKeyEvent>
#include <QLabel>
#include <QFont>
#include <QSound>
#include <QBrush>
#include <QImage>
#include <qsize.h>
#include <QPixmap>

#define WALL 0;
#define PEOPLE 1;
#define BOX 2;
#define GOAL 3;
#define GROUND 4;
#define Finish 5;
#define PeopleAndGoal 6;
class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();
    void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);
    void createMap(int level);
    void update();
    int move(int *first, int *second ,int * now );
    void startToTimer();

private:

    QPushButton *startbtn;
    QPushButton *returnbtn;
    QPushButton *chooseone;
    QPushButton *choosetwo;
    QPushButton *choosethree;
    QPushButton *choosefour;
    QPushButton *choosefive;
    QTimer *timer;
    int score;
    int level;
    int time;
    int step;
    int fllower;
    int finished;
    int map_x,map_y;
    int now_x,now_y;
    int mapNow[18][15];

    QLabel *scorelabel;
    QLabel *levellabel;
    QLabel *timelabel;
    QLabel * steplabel;
    QLabel *scoreshow;
    QLabel *levelshow;
    QLabel *timeshow;
    QLabel * stepshow;
    QLabel *choose;
signals:

public slots:
    void startbtnSlot();
    void returnbtnSlot();
    void chooseoneslot();
    void choosetwoslot();
    void choosethreeslot();
    void choosefourslot();
    void choosefiveslot();
    void timeout();
};

#endif // GAMEWIDGET_H


mainWidget.h

#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include "GameWidget.h"
#include <QWidget>
#include <QIcon>
#include <QPalette>
#include <QBrush>
#include <QPixmap>
#include <QPushButton>
#include <QMessageBox>
#include <QLabel>
#include <QFont>
#include <QDesktopWidget>
#include <QApplication>
class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = 0);
    //构造函数
    ~mainWidget();
    //void resizeEvent(QResizeEvent *);
private:
    QPushButton *startbtn;
    QPushButton *exitbtn;
    QPushButton *bangbtn;
    GameWidget *g;
    QLabel *label;
signals:
public slots:
    void exitSlot();
    void startSlot();
    void bangSlot();
};

#endif // MAINWIDGET_H


GameWidget.cpp

#include "GameWidget.h"

GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    map_x = 40;//wigth
    map_y = 40;//high
    step = 0;
    score=0;
    level=1;
    time=0;
    createMap(level);

    this->setAutoFillBackground(true);
    this->setWindowTitle("游戏开始");
    this->setWindowIcon(QIcon(":/new/prefix1/img/1.png"));
    this->resize(parent->width() ,parent->height());
    this->setMinimumSize(parent->width() ,parent->height());
    this->setMaximumSize(parent->width() ,parent->height());
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/img/green.jpg").scaled(this->size())));
    this->setPalette(palette);

    startbtn=new QPushButton(this);
    startbtn->setIcon(QIcon(":/new/prefix1/img/start.png"));
    startbtn->setIconSize(QSize(60,60));
    startbtn->setGeometry(QRect(770,500,60,60));
    startbtn->setFlat(true);

    returnbtn=new QPushButton(this);
    returnbtn->setIcon(QIcon(":/new/prefix1/img/quit.png"));
    returnbtn->setIconSize(QSize(60,60));
    returnbtn->setGeometry(QRect(870,500,60,60));
    returnbtn->setFlat(true);

    chooseone=new QPushButton("1",this);
    chooseone->setIconSize(QSize(50,30));
    chooseone->setGeometry(QRect(760,320,50,30));

    choosetwo=new QPushButton("2",this);
    choosetwo->setIconSize(QSize(50,30));
    choosetwo->setGeometry(QRect(810,320,50,30));

    choosethree=new QPushButton("3",this);
    choosethree->setIconSize(QSize(50,30));
    choosethree->setGeometry(QRect(860,320,50,30));

    choosefour=new QPushButton("4",this);
    choosefour->setIconSize(QSize(50,30));
    choosefour->setGeometry(QRect(760,350,50,30));

    choosefive=new QPushButton("5",this);
    choosefive->setIconSize(QSize(50,30));
    choosefive->setGeometry(QRect(810,350,50,30));


    QFont font;
    font.setFamily("Consolas");
    font.setBold(true);
    font.setPixelSize(35);

    scorelabel=new QLabel("得分:",this);
    scorelabel->setFont(font);
    scorelabel->setGeometry(QRect(760,1,130,50));

    levellabel=new QLabel("关卡:",this);
    levellabel->setFont(font);
    levellabel->setGeometry(QRect(760,70,130,50));

    timelabel=new QLabel("时间:",this);
    timelabel->setFont(font);
    timelabel->setGeometry(QRect(760,139,130,50));

    QString str1,str2,str3,str4;
    str1=QString::number(score);
    str2=QString::number(level);
    str3=str3.sprintf("%03d秒",time);
    str4=QString::number(step);


    steplabel=new QLabel("步数:",this);
    steplabel->setFont(font);
    steplabel->setGeometry(QRect(760,208,130,50));

    choose=new QLabel("选关：",this);
    choose->setFont(font);
    choose->setGeometry(QRect(760,270,130,50));

    scoreshow=new QLabel(this);
    scoreshow->setFont(font);
    scoreshow->setGeometry(QRect(850,1,110,50));
    scoreshow->setText(str1);

    levelshow=new QLabel(this);
    levelshow->setFont(font);
    levelshow->setGeometry(QRect(850,70,110,50));
    levelshow->setText(str2);

    timeshow=new QLabel(this);
    timeshow->setFont(font);
    timeshow->setGeometry(QRect(850,139,110,50));
    timeshow->setText(str3);

    stepshow=new QLabel(this);
    stepshow->setFont(font);
    stepshow->setGeometry(QRect(850,208,110,50));
    stepshow->setText(str4);

    connect(startbtn,SIGNAL(clicked()),this,SLOT(startbtnSlot()));
    connect(returnbtn,SIGNAL(clicked()),this,SLOT(returnbtnSlot()));
    connect(chooseone,SIGNAL(clicked()),this,SLOT(chooseoneslot()));
    connect(choosetwo,SIGNAL(clicked()),this,SLOT(choosetwoslot()));
    connect(choosethree,SIGNAL(clicked()),this,SLOT(choosethreeslot()));
    connect(choosefour,SIGNAL(clicked()),this,SLOT(choosefourslot()));
    connect(choosefive,SIGNAL(clicked()),this,SLOT(choosefiveslot()));
}

void GameWidget::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    //背景
    QPixmap paint[7];
    paint[0].load(":/new/prefix1/img/1.png");
    paint[1].load(":/new/prefix1/img/2.png");
    paint[2].load(":/new/prefix1/img/3.png");
    paint[3].load(":/new/prefix1/img/4.png");
    paint[4].load(":/new/prefix1/img/5.png");
    paint[5].load(":/new/prefix1/img/6.png");
    paint[6].load(":/new/prefix1/img/7.png");

    for(int x = 0 ; x <18; x++){
        for(int y = 0 ; y < 15 ; y ++){
            painter.drawPixmap(x*map_x,y*map_y,map_x,map_y,paint[mapNow[x][y]]);
        }
    }

    //网格线
    for(int i=0;i<18;i++)
    {
        for(int j=0;j<16;j++)
        {
            painter.drawRect(QRect(i*map_x,j*map_y,map_x,map_y));

        }
    }
}
void GameWidget::keyPressEvent(QKeyEvent * event)
{
    int* now = &mapNow[now_x][now_y];
    int* first = NULL;
    int* second = NULL;
    switch (event->key()) {
    case Qt::Key_Left:
        first = &mapNow[now_x-1][now_y];
        second = &mapNow[now_x-2][now_y];
        if(move(first,second,now) == 1){
            now_x -=1;
        }
        break;
    case Qt::Key_Right:
        first = &mapNow[now_x+1][now_y];
        second = &mapNow[now_x+2][now_y];
        if(move(first,second,now )== 1){
            now_x +=1;
        }
        break;
    case Qt::Key_Down:
        first = &mapNow[now_x][now_y+1];
        second = &mapNow[now_x][now_y+2];
        if(move(first,second,now)==1){
            now_y +=1;
        }
        break;
    case Qt::Key_Up:
        first = &mapNow[now_x][now_y-1];
        second = &mapNow[now_x][now_y-2];
        if(move(first,second,now) == 1){
            now_y -=1;
        }
        break;

    case Qt::Key_1:
        time = 0;
        createMap(level = 1);
        score = step = 0;
        update();
        break;
    case Qt::Key_2:
        time = 0;
        createMap(level = 2);
        score = step = 0;
        update();
        break;
    case Qt::Key_3:
        time = 0;
        createMap(level = 3);
        score = step = 0;
        update();
        break;
    case Qt::Key_4:
        time = 0;
        createMap(level = 4);
        score = step = 0;
        update();
        break;
    case Qt::Key_5:
        time = 0;
        createMap(level = 5);
        score = step = 0;
        update();
        break;
    default:
        break;
    }

}

int GameWidget::move(int *first, int *second ,int * now )
{
    if(*first == 4 || *first == 3 || (*first == 2 && (*second ==3 || *second ==4)) || (*first == 5 &&(*second == 3 || *second ==4))){
        int nowValue = -1;
        if(*now == 1)
            nowValue = 4;
        else
            nowValue = 3;
        if(*first == 4 ){
            *first = 1;
            QSound::play(":/new/prefix1/img/move.wav");
        }else if(*first == 3){
            *first = 6;
            QSound::play(":/new/prefix1/img/move.wav");
        }else if(*first == 2 && *second == 3){
            QSound::play(":/new/prefix1/img/collision.wav");
            *second = 5;
            finished++;
            score++;
            *first = 1;
        }else if(*first == 5 && *second == 3){
            QSound::play(":/new/prefix1/img/collision.wav");
            step++;
            update();
            *second = 5;
            *first = 6;
        }else if(*first == 5 && *second == 4){
            QSound::play(":/new/prefix1/img/collision.wav");
            *second = 2;
            finished--;
            score--;
            *first = 6;
        }else{
            QSound::play(":/new/prefix1/img/collision.wav");
            *second = *first;
            *first = *now;
        }
        *now = nowValue;
        step++;
        if(finished==fllower){
            QSound::play(":/new/prefix1/img/victory.wav");
            QMessageBox::information(this,tr("wancheng"),tr("推便便是一款由推箱子发展而来的游戏。\n游戏玩法：\n要控制搬运工上下左右移动，来将箱子推到指定地点"),QMessageBox::Ok);
            createMap(++level);
            step=0;
            update();
            return 2;
        }
        update();
        return 1;

    }
    return 0;

}
void GameWidget::createMap(int level)
{
    for(int i=0;i<18;i++)
    {
        for(int j=0;j<15;j++)
        {
            mapNow[i][j] = GROUND;
        }
    }
    finished =0;
    step = 0;
    switch (level) {
    case 2:
        //level 1
        fllower = 4;
        now_x =6; now_y = 7;
        mapNow[5][4]=WALL;mapNow[13][5]=WALL;
        mapNow[5][4]=WALL; mapNow[6][4]=WALL;
        mapNow[7][4]=WALL; mapNow[8][4]=WALL;
        mapNow[9][4]=WALL; mapNow[10][4]=WALL;
        mapNow[5][4]=WALL; mapNow[11][4]=WALL;
        mapNow[5][5]=WALL; mapNow[11][5]=WALL;
        mapNow[12][5]=WALL; mapNow[4][6]=WALL;
        mapNow[5][6]=WALL; mapNow[5][6]=WALL;
        mapNow[6][6]=BOX;mapNow[7][6]=WALL;
        mapNow[8][6]=WALL; mapNow[9][6]=WALL;
        mapNow[13][6]=WALL;mapNow[4][7]=WALL;
        mapNow[6][7]=PEOPLE; mapNow[8][7]=BOX;
        mapNow[11][7]=BOX;mapNow[13][7]=WALL;
        mapNow[5][9]=WALL;mapNow[6][8]=GOAL;
        mapNow[7][8]=GOAL;mapNow[8][8]=WALL;
        mapNow[10][8]=BOX;mapNow[12][8]=WALL;
        mapNow[13][8]=WALL;mapNow[4][9]=WALL;
        mapNow[5][9]=WALL;mapNow[6][9]=GOAL;
        mapNow[7][9]=GOAL;mapNow[8][9]=WALL;
        mapNow[12][9]=WALL;mapNow[5][10]=WALL;
        mapNow[6][10]=WALL;mapNow[7][10]=WALL;
        mapNow[8][10]=WALL;mapNow[9][10]=WALL;
        mapNow[10][10]=WALL;mapNow[11][10]=WALL;
        mapNow[12][10]=WALL;mapNow[4][8]=WALL;
        break;
    case 1:
        //level 2
        fllower = 4;
        now_x =9; now_y = 6;
        mapNow[9][4]=WALL;mapNow[10][4]=WALL;
        mapNow[11][4]=WALL;mapNow[12][4]=WALL;
        mapNow[8][5]=WALL;mapNow[9][5]=WALL;
        mapNow[12][5]=WALL;mapNow[8][6]=WALL;
        mapNow[9][6]=PEOPLE;mapNow[10][6]=BOX;
        mapNow[12][6]=WALL;mapNow[8][7]=WALL;
        mapNow[9][7]=WALL;mapNow[10][7]=BOX;
        mapNow[8][8]=WALL;mapNow[9][8]=WALL;
        mapNow[11][8]=BOX;mapNow[13][8]=WALL;
        mapNow[8][9]=WALL;mapNow[9][9]=GOAL;
        mapNow[10][9]=BOX;mapNow[13][9]=WALL;
        mapNow[8][10]=WALL;mapNow[9][10]=GOAL;
        mapNow[10][10]=GOAL;mapNow[12][10]=GOAL;
        mapNow[13][10]=WALL;mapNow[8][11]=WALL;
        mapNow[9][11]=WALL;mapNow[10][11]=WALL;
        mapNow[11][11]=WALL;mapNow[12][11]=WALL;
        mapNow[13][11]=WALL;mapNow[13][7]=WALL;
        break;
    case 3:
        //level 3
        fllower = 6;
        now_x =10; now_y = 10;
        mapNow[7][5]=WALL;mapNow[8][5]=WALL;
        mapNow[9][5]=WALL;mapNow[10][5]=WALL;
        mapNow[11][5]=WALL;mapNow[12][5]=WALL;
        mapNow[6][6]=WALL;mapNow[7][6]=WALL;
        mapNow[12][6]=WALL;mapNow[13][6]=WALL;
        mapNow[6][7]=WALL;mapNow[8][7]=BOX;
        mapNow[10][7]=BOX;mapNow[11][7]=BOX;
        mapNow[13][7]=WALL;mapNow[6][8]=WALL;
        mapNow[7][8]=GOAL;mapNow[8][8]=GOAL;
        mapNow[9][8]=GOAL;mapNow[10][8]=GOAL;
        mapNow[11][8]=GOAL;mapNow[12][8]=GOAL;
        mapNow[13][8]=WALL;mapNow[6][9]=WALL;
        mapNow[8][9]=BOX;mapNow[9][9]=BOX;
        mapNow[11][9]=BOX;mapNow[13][9]=WALL;
        mapNow[6][10]=WALL;mapNow[7][10]=WALL;
        mapNow[8][10]=WALL;mapNow[10][10]=PEOPLE;
        mapNow[11][10]=WALL;mapNow[12][10]=WALL;
        mapNow[13][10]=WALL;mapNow[8][11]=WALL;
        mapNow[9][11]=WALL;mapNow[10][11]=WALL;
        mapNow[11][11]=WALL;
        break;
    case 4:
        //level 4
        fllower = 8;
        now_x =11; now_y = 11;
        mapNow[7][5]=WALL;mapNow[8][5]=WALL;
        mapNow[9][5]=WALL;mapNow[10][5]=WALL;
        mapNow[11][5]=WALL;mapNow[12][5]=WALL;
        mapNow[13][5]=WALL;mapNow[7][6]=WALL;
        mapNow[8][6]=GOAL;mapNow[9][6]=GOAL;
        mapNow[10][6]=BOX;mapNow[11][6]=GOAL;
        mapNow[12][6]=GOAL;mapNow[13][6]=WALL;
        mapNow[7][7]=WALL;mapNow[8][7]=GOAL;
        mapNow[9][7]=GOAL;mapNow[10][7]=WALL;
        mapNow[11][7]=GOAL;mapNow[12][7]=GOAL;
        mapNow[13][7]=WALL;mapNow[7][8]=WALL;
        mapNow[9][8]=BOX;mapNow[10][8]=BOX;
        mapNow[11][8]=BOX;mapNow[13][8]=WALL;
        mapNow[7][9]=WALL;mapNow[10][9]=BOX;
        mapNow[13][9]=WALL;mapNow[7][10]=WALL;
        mapNow[9][10]=BOX;mapNow[10][10]=BOX;
        mapNow[11][10]=BOX;mapNow[13][10]=WALL;
        mapNow[7][11]=WALL;mapNow[10][11]=WALL;
        mapNow[11][11]=PEOPLE;mapNow[13][11]=WALL;
        mapNow[7][12]=WALL;mapNow[8][12]=WALL;
        mapNow[9][12]=WALL;mapNow[10][12]=WALL;
        mapNow[11][12]=WALL;mapNow[12][12]=WALL;
        mapNow[13][12]=WALL;
        break;
    case 5:
        //第五关
        fllower = 3;
        now_x =11; now_y = 6;
        mapNow[8][5]=WALL;mapNow[9][5]=WALL;
        mapNow[10][5]=WALL;mapNow[11][5]=WALL;
        mapNow[12][5]=WALL;mapNow[6][6]=WALL;
        mapNow[7][6]=WALL;mapNow[8][6]=WALL;
        mapNow[11][6]=PEOPLE;mapNow[12][6]=WALL;
        mapNow[6][7]=WALL;mapNow[9][7]=BOX;
        mapNow[10][7]=GOAL;mapNow[12][7]=WALL;
        mapNow[13][7]=WALL;mapNow[6][8]=WALL;
        mapNow[9][8]=GOAL;mapNow[10][8]=BOX;
        mapNow[11][8]=GOAL;mapNow[13][8]=WALL;
        mapNow[6][9]=WALL;mapNow[7][9]=WALL;
        mapNow[8][9]=WALL;mapNow[10][9]=WALL;
        mapNow[11][9]=BOX;mapNow[13][9]=WALL;
        mapNow[8][10]=WALL;mapNow[12][10]=WALL;
        mapNow[13][10]=WALL;mapNow[8][11]=WALL;
        mapNow[9][11]=WALL;mapNow[10][11]=WALL;
        mapNow[11][11]=WALL;mapNow[12][11]=WALL;
        break;
    default:
        break;
    }
}

void GameWidget::update() {
    QWidget::update();
    stepshow->setText(QString::number(step));
    scoreshow->setText(QString::number(score));
    levelshow->setText(QString::number(level));
}
void GameWidget::chooseoneslot()
{
    createMap(level = 1);
    time = 0;
    GameWidget::setFocus();
    score = 0;
    update();
}
void GameWidget::choosetwoslot()
{
    createMap(level = 2);
    time = 0;
    GameWidget::setFocus();
    score = 0;
    update();
}
void GameWidget::choosethreeslot()
{
    createMap(level = 3);
    time = 0;
    GameWidget::setFocus();
    score = 0;
    update();
}
void GameWidget::choosefourslot()
{
    createMap(level = 4);
    time = 0;
    GameWidget::setFocus();
    score = 0;
    update();
}
void GameWidget::choosefiveslot()
{
    createMap(level = 5);
    time = 0;
    GameWidget::setFocus();
    score = 0;
    update();
}
void GameWidget::startbtnSlot()
{
    timer= new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->start(1000);
    GameWidget::setFocus();
    startbtn->setEnabled(false);
}
void GameWidget::timeout()
{
    time++;
    QString show ;
    show = show.sprintf("%03d秒",time);
    timeshow->setText(show);
}

void GameWidget::returnbtnSlot()
{
    delete this;
}

GameWidget::~GameWidget()
{
    delete startbtn;
    delete returnbtn;
}


main.cpp

#include "mainWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWidget w;
    w.show();
    // .exec()模式对话框
    return a.exec();
    //循环显示
}


mainWidget.cpp

#include "mainWidget.h"

mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(100,100);
    this->setMinimumSize(960,600);
    this->setMaximumSize(960,600);
   // this->setWindowIcon(QIcon(":/new/prefix1/img/icon.png"));
    this->setWindowIcon(QPixmap(":/new/prefix1/img/icon.png"));
    this->setWindowTitle("推箱子之推便便");//标题
    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/img/back.jpg").scaled(this->size())));
    this->setPalette(palette);
    //set window
    this->move((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);


    startbtn=new QPushButton(this);
    startbtn->setIcon(QIcon(":/new/prefix1/img/start.png"));
    startbtn->setIconSize(QSize(175,175));
    startbtn->setGeometry(QRect(395,180,175,175));
    startbtn->setFlat(true);


    exitbtn=new QPushButton(this);
    exitbtn->setIcon(QIcon(":/new/prefix1/img/quit.png"));
    exitbtn->setIconSize(QSize(85,85));
    exitbtn->setGeometry(QRect(850,20,85,85));
    exitbtn->setFlat(true);
    //设置说明标签
    bangbtn=new QPushButton(this);
    bangbtn->setIcon(QIcon(":/new/prefix1/img/bang.png"));
    bangbtn->setIconSize(QSize(85,85));
    bangbtn->setGeometry(QRect(25,20,85,85));
    bangbtn->setFlat(true);



    connect(exitbtn,SIGNAL(clicked()),this,SLOT(exitSlot()));
    connect(startbtn,SIGNAL(clicked()),this,SLOT(startSlot()));
    connect(bangbtn,SIGNAL(clicked()),this,SLOT(bangSlot()));

}



mainWidget::~mainWidget()
{
//    delete startbtn;
//    delete exitbtn;
//    delete bangbtn;

}

void mainWidget::exitSlot()
{
    if(QMessageBox::question(this,"退出游戏","是否退出当前游戏",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        delete this;
        exit(0);
    }
}
void mainWidget::bangSlot()
{
    QMessageBox::information(this,tr("游戏玩法"),tr("推便便是一款由推箱子发展而来的游戏。\n游戏玩法：\n要控制搬运工上下左右移动，来将箱子推到指定地点\n按“Z”撤销"),QMessageBox::Ok);

}

void mainWidget::startSlot()
{

    g=new GameWidget(this);
    g->show();
}
