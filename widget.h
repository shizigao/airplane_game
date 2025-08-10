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
#include "enemyplanepool.h"
#include "enemybulletpool.h"
#include "random"
#include "QProgressBar"
#include "QLineEdit"
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
    //加载暂停界面
    void load_pause();
    //加载结束界面
    void load_end();
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

    //转到界面函数
    void turn_to_menu();
    void turn_to_level1();

    //键盘输入函数
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    //英雄机的移动函数
    void heroplane1_move();
    void heroplane2_move();

    //碰撞检测
    void collision_detection();//总碰撞检测函数
    void collision_detection_herobullet_with_enemyplane();
    void collision_detection_enemybullet_with_heroplane();
    void collision_detection_heroplane_with_enemyplane();

    //暂停游戏
    void game_pause();

    //游戏结束
    void game_end();
    void delete_level();

    //存储分数
    void save_score();
    //读取本地最高分
    int load_score();



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

    //关卡UI
    //血量进度条
    QProgressBar* heroplane1_health_bar = nullptr, *heroplane2_health_bar = nullptr;
    //血量值文本框
    QLineEdit *heroplane1_health_text = nullptr, *heroplane2_health_text = nullptr;




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
    EnemyPlanePool* enemyplane_pool = nullptr;
    //敌机子弹的对象池
    EnemyBulletPool* enemybullet_pool = nullptr;

    //暂停界面元素
    QGraphicsPixmapItem* pause_picture = nullptr;
    QGraphicsRectItem* pause_background = nullptr;

    //结束游戏界面元素
    QGraphicsPixmapItem* end_picture = nullptr;

    //游戏状态
    int status = 2;//0表示游戏结束 1表示游戏暂停 2表示游戏正常运行

    //分数
    int score = 0;

    //游戏中的分数板
    QLineEdit* score_text = nullptr;
    //显示游戏最高分的分数板
    QLineEdit* high_score_text = nullptr;

    //经验条
    QProgressBar* heroplane1_experience_bar = nullptr, *heroplane2_experience_bar = nullptr;



private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
