#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "config.h"
#include <QEvent>
#include <QWheelEvent>
#include <QToolButton>
#include <QPixmap>
#include <QProgressBar>
#include <QPalette>
#include <QLineEdit>
#include <QKeyEvent>
#include <QMouseEvent>
#include "heroplane.h"
#include <QTimer>
#include <QList>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


    //加载资源
    void load_resources();//加载资源总函数
    void load_timer();//加载游戏计时器
    void load_startgame();//加载开始界面资源
    void load_menu();//加载主菜单资源
    void load_levels();//加载关卡资源
    void load_heroplane();//在指定场景中加载英雄机资源

    //切换页面
    void turn_to_menu();//转到主菜单
    void turn_to_level1();//转到第一关

    //实现鼠标控制飞机移动
    void heroplane_move1();
    //实现键盘控制飞机移动
    void heroplane_move2(HeroPlane* heroplane);


    //游戏周期更新函数，表示每个游戏周期所有组件的行为
    //通用更新函数，包含英雄机的移动、敌机的移动、子弹移动、飞机碰撞检测和敌机碰撞检测
    void game_update();
    //各个管钱的更新函数，需要单独实现
    void level_1_update();//第一关的更新函数
    void level_2_update();//第二关的更新函数
    void level_3_update();//第三关的更新函数
    void level_4_update();//第四关的更新函数
    void level_5_update();//第五关的更新函数

    
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    Ui::Widget *ui;
    //英雄机
    HeroPlane *heroplane1, *heroplane2;//因为有多人模式，所以设置两个英雄机
    
    //游戏周期计时器（10ms为一个周期)
    QTimer *game_timer;
    //主视图
    QGraphicsView main_view;

    //场景
    QGraphicsScene main_scene;//开始界面
    QGraphicsScene main_scene2;//主菜单
    QGraphicsScene level_1_scene;//第一关场景
    QGraphicsScene level_2_scene;//第二关场景
    QGraphicsScene level_3_scene;//第三关场景
    QGraphicsScene level_4_scene;//第四关场景
    QGraphicsScene level_5_scene;//第五关场景





    //背景图片
    QGraphicsPixmapItem* startgame_background1;
    QGraphicsPixmapItem* startgame_background2;
    QGraphicsPixmapItem* level_1_background1, *level_1_background2;
    QGraphicsPixmapItem* level_2_background1, *level_2_background2;
    QGraphicsPixmapItem* level_3_background1, *level_3_background2;
    QGraphicsPixmapItem* level_4_background1, *level_4_background2;
    QGraphicsPixmapItem* level_5_background1, *level_5_background2;

    //按钮

    //游戏主界面按钮
    QToolButton *startgame_button, *single_level, *single_infinite, *double_infinite, *double_against, *record, *help, *settings;

    //ProgressBar
    //关卡进度条
    QProgressBar *level_1_progressBar;
    QProgressBar *level_2_progressBar;
    QProgressBar *level_3_progressBar;
    QProgressBar *level_4_progressBar;
    QProgressBar *level_5_progressBar;
    //生命条
    QProgressBar *level_1_healthBar;
    QProgressBar *level_2_healthBar;
    QProgressBar *level_3_healthBar;
    QProgressBar *level_4_healthBar;
    QProgressBar *level_5_healthBar;

    QLineEdit *level_1_healthValue;
    QLineEdit *level_2_healthValue;
    QLineEdit *level_3_healthValue;
    QLineEdit *level_4_healthValue;
    QLineEdit *level_5_healthValue;
    //武器背景
    QGraphicsPixmapItem *level_1_weapon1;
    QGraphicsPixmapItem *level_1_weapon2;
    QGraphicsPixmapItem *level_1_weapon3;
    QGraphicsPixmapItem *level_1_weapon4;
    QGraphicsPixmapItem *level_2_weapon1;
    QGraphicsPixmapItem *level_2_weapon2;
    QGraphicsPixmapItem *level_2_weapon3;
    QGraphicsPixmapItem *level_2_weapon4;
    QGraphicsPixmapItem *level_3_weapon1;
    QGraphicsPixmapItem *level_3_weapon2;
    QGraphicsPixmapItem *level_3_weapon3;
    QGraphicsPixmapItem *level_3_weapon4;
    QGraphicsPixmapItem *level_4_weapon1;
    QGraphicsPixmapItem *level_4_weapon2;
    QGraphicsPixmapItem *level_4_weapon3;
    QGraphicsPixmapItem *level_4_weapon4;
    QGraphicsPixmapItem *level_5_weapon1;
    QGraphicsPixmapItem *level_5_weapon2;
    QGraphicsPixmapItem *level_5_weapon3;
    QGraphicsPixmapItem *level_5_weapon4;
    //分数板
    QLineEdit *level_1_score;
    QLineEdit *level_2_score;
    QLineEdit *level_3_score;
    QLineEdit *level_4_score;
    QLineEdit *level_5_score;



    //其他变量

    //移动模式
    int move_mode = 0;//0表示随鼠标移动,1表示随键盘移动
    //存储键盘按键的列表
    QList<int> keylist;




};

#endif // WIDGET_H
