#include "mainWidget.h" #include

int main(int argc, char *argv[]) { QApplication a(argc, argv); mainWidget w; w.show(); // .exec()模式对话框 return a.exec(); //循环显示 }

mainWidget.cpp

#include "mainWidget.h"

mainWidget::mainWidget(QWidget *parent) : QWidget(parent) { this->resize(100,100); this->setMinimumSize(960,600); this->setMaximumSize(960,600); // this->setWindowIcon(QIcon(":/new/prefix1/img/icon.png")); this->setWindowIcon(QPixmap(":/new/prefix1/img/icon.png")); this->setWindowTitle("推箱子之推便便");//标题 QPalette palette; palette.setBrush(QPalette::Background,QBrush(QPixmap(":/new/prefix1/img/back.jpg").scaled(this->size()))); this->setPalette(palette); //set window this->move((QApplication::desktop()->width() - this->width())/2,(QApplication::desktop()->height() - this->height())/2);

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

mainWidget::~mainWidget() { // delete startbtn; // delete exitbtn; // delete bangbtn;

}

void mainWidget::exitSlot() { if(QMessageBox::question(this,"退出游戏","是否退出当前游戏",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes) { delete this; exit(0); } } void mainWidget::bangSlot() { QMessageBox::information(this,tr("游戏玩法"),tr("推便便是一款由推箱子发展而来的游戏。\n游戏玩法：\n要控制搬运工上下左右移动，来将箱子推到指定地点\n按“Z”撤销"),QMessageBox::Ok);

}

void mainWidget::startSlot() {

g=new GameWidget(this);
g->show();

}
