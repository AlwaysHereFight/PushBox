#ifndef GAMEWIDGET_H #define GAMEWIDGET_H

#include #include #include #include #include #include #include #include #include #include #include #include #include #include #include #include <qsize.h> #include

#define WALL 0; #define PEOPLE 1; #define BOX 2; #define GOAL 3; #define GROUND 4; #define Finish 5; #define PeopleAndGoal 6; class GameWidget : public QWidget { Q_OBJECT public: explicit GameWidget(QWidget *parent = 0); ~GameWidget(); void keyPressEvent(QKeyEvent *); void paintEvent(QPaintEvent *); void createMap(int level); void update(); int move(int *first, int *second ,int * now ); void startToTimer();

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

public slots: void startbtnSlot(); void returnbtnSlot(); void chooseoneslot(); void choosetwoslot(); void choosethreeslot(); void choosefourslot(); void choosefiveslot(); void timeout(); };

#endif // GAMEWIDGET_H

mainWidget.h

#ifndef MAINWIDGET_H #define MAINWIDGET_H #include "GameWidget.h" #include #include #include #include #include #include #include #include #include #include #include class mainWidget : public QWidget { Q_OBJECT

public: mainWidget(QWidget *parent = 0); //构造函数 ~mainWidget(); //void resizeEvent(QResizeEvent *); private: QPushButton *startbtn; QPushButton *exitbtn; QPushButton *bangbtn; GameWidget *g; QLabel *label; signals: public slots: void exitSlot(); void startSlot(); void bangSlot(); };

#endif // MAINWIDGET_H
