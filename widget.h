#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "config.h"
#include <QPushButton>
#include <QSize>
#include <QTimer>
#include "heroplane.h"
#include <QEvent>
#include <QKeyEvent>
#include <QList>
#include "herobullet.h"
#include "enemybullet.h"
#include "enemyplane.h"
#include "herobulletpool.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //整个游戏的初始化函数
    void init_game();

    //加载函数
    //总加载函数
    void load_resources();
    //开始界面的加载函数
    void load_startgame();
    //主菜单加载函数
    void load_menu();
    //关卡的加载函数
    void load_level();
    //计时器加载函数
    void load_timer();
    //加载对象池
    void load_pool();
    //英雄机的加载函数
    void load_heroplane1(int heroplane_kind);//加载玩家1的英雄机
    void load_heroplane2(int heroplane_kind);//加载玩家2的英雄机

    //更新函数
    //不同关卡的更新函数
    void level1_update();
    void level2_update();
    void level3_update();
    void level4_update();
    void level5_update();
    //通用更新函数
    void general_update();

    //转到关卡界面函数
    void turn_to_level1();

    //键盘输入函数
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    //英雄机的移动函数
    void heroplane1_move();
    void heroplane2_move();


public:
    //视图
    QGraphicsView* view = nullptr;

    //场景
    //开始游戏场景
    QGraphicsScene* startgame_scene = nullptr;
    QGraphicsScene* menu_scene = nullptr;
    QGraphicsScene* level_scene = nullptr;

    //背景图片
    //开始游戏背景图片
    QGraphicsPixmapItem* startgame_background = nullptr;
    QGraphicsPixmapItem* menu_background = nullptr;
    //关卡的背景图片
    QGraphicsPixmapItem* level1_background1 = nullptr, *level1_background2 = nullptr;
    QGraphicsPixmapItem* level2_background1 = nullptr, *level2_background2 = nullptr;
    QGraphicsPixmapItem* level3_background1 = nullptr, *level3_background2 = nullptr;
    QGraphicsPixmapItem* level4_background1 = nullptr, *level4_background2 = nullptr;
    QGraphicsPixmapItem* level5_background1 = nullptr, *level5_background2 = nullptr;



    //按钮
    //开始界面的按钮
    QPushButton* startgame_button = nullptr;
    //主菜单的按钮
    QPushButton *menu_one_player_level_button = nullptr, *menu_one_player_endlessbutton = nullptr, *menu_two_player_endlessbutton = nullptr,
     *menu_two_player_against_button = nullptr, *menu_record_button = nullptr, *menu_introductionbutton = nullptr, *menu_settings_button = nullptr;

    //计时器
    //游戏周期计时器（帧）
    QTimer* game_timer = nullptr;


    //英雄机
    HeroPlane *heroplane1 = nullptr, *heroplane2 = nullptr;

    //处理英雄机移动的链表
    QList<int> move_list;

    //对象池
    //英雄机子弹的对象池
    HeroBulletPool* herobullet_pool = nullptr;
    //敌机的对象池
    //敌机子弹的对象池





private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
