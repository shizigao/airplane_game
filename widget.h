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
#include <QMediaPlayer>
#include <QQueue>
#include <QList>
#include <QVector>
#include "enemybullet.h"
#include "enemyplane.h"
#include "herobullet.h"
#include "heroweapon.h"
#include "enemyweapon.h"
#include <algorithm>
using namespace std;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{


public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


    //加载资源
    void load_resources();//加载资源总函数
    void load_timer();//加载游戏计时器
    void load_sound();//加载音乐和音效等
    void load_object_pool();//加载对象池
    void load_pause();//加载暂停界面
    void load_startgame();//加载开始界面资源
    void load_menu();//加载主菜单资源
    void load_levels();//加载关卡资源
    void load_heroplane();//在指定场景中加载英雄机资源

    void load_weapon1(HeroWeapon* heroweapon);//加载武器1图标
    void load_weapon2(HeroWeapon* heroweapon);//加载武器2图标
    void load_weapon3(HeroWeapon* heroweapon);//加载武器3图标


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

    //各个关卡的更新函数，需要单独实现
    void level_1_update();//第一关的更新函数
    void level_2_update();//第二关的更新函数
    void level_3_update();//第三关的更新函数
    void level_4_update();//第四关的更新函数
    void level_5_update();//第五关的更新函数


    //对象池函数
    EnemyPlane* get_enemyplane(int x, int y, int kind);//从对象池中获取敌机(初始化为kind值对应的类型，已初始化）
    EnemyBullet* get_enemybullet(int x, int y, int kind);//从对象池中获取敌人子弹(初始化为kind值对应的类型，已初始化）
    HeroBullet* get_herobullet(int x, int y, int kind);//从对象池中获取英雄机的子弹(初始化为kind值对应的类型，已初始化）


    
    //操作事件
    void keyPressEvent(QKeyEvent *event);//处理键盘按下事件
    void keyReleaseEvent(QKeyEvent *event);//处理键盘松开事件
    void mousePressEvent(QMouseEvent *event);//处理鼠标点击事件
    void game_pause();//实现游戏暂停功能

    //玩家发射子弹
    void heroplane1_shoot_1();//玩家1武器1发射
    void heroplane1_shoot_2();//玩家1武器2发射
    void heroplane1_shoot_3();//玩家1武器3发射
    void heroplane2_shoot_1();//玩家2武器1发射
    void heroplane2_shoot_2();//玩家2武器2发射
    void heroplane2_shoot_3();//玩家2武器3发射
    //敌机发射子弹
    void enemyplane_shoot(EnemyPlane* enemyplane);
private:

    //基于扫掠裁剪算法的碰撞检测优化（每100ms执行一次碰撞检测）
    void collision_detection();//总碰撞检测函数
    void collision_detection_herobullet_with_enemyplane();
    void collision_detection_enemybullet_with_heroplane();
    void collision_detection_heroplane_with_enemyplane();


    Ui::Widget *ui;

    //英雄机
    HeroPlane *heroplane1, *heroplane2;//因为有多人模式，所以设置两个英雄机
    
    //计时器
    //游戏周期计时器（20ms为一个周期)
    QTimer *game_timer;
    //英雄机武器计时器
    QTimer *heroplane1_weapon1_timer, *heroplane1_weapon2_timer, *heroplane1_weapon3_timer;
    QTimer *heroplane2_weapon1_timer, *heroplane2_weapon2_timer, *heroplane2_weapon3_timer;
    //表示是否连续开火的状态
    bool heroplane1_weapon1_continuous_firing = false, heroplane1_weapon2_continuous_firing = false, heroplane1_weapon3_continuous_firing = false;
    bool heroplane2_weapon1_continuous_firing = false, heroplane2_weapon2_continuous_firing = false, heroplane2_weapon3_continuous_firing = false;


    //主视图
    QGraphicsView main_view;


    //场景（游戏中所有的场景都在这）
    QGraphicsScene main_scene;//开始界面
    QGraphicsScene main_scene2;//主菜单
    QGraphicsScene level_scene;//关卡场景

    //暂停界面
    QGraphicsRectItem *pause_background;//半透明黑色矩形框，用于模拟暂停界面
    QGraphicsPixmapItem *pause_picture;


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
    QProgressBar *level_progressBar;

    //生命条
    QProgressBar *player1_healthBar;
    QLineEdit *player1_healthValue;
    //武器背景
    QGraphicsPixmapItem *player1_weapon1_background;
    QGraphicsPixmapItem *player1_weapon2_background;
    QGraphicsPixmapItem *player1_weapon3_background;
    QGraphicsPixmapItem *player1_weapon4_background;

    //分数板
    QLineEdit *score;

    //音乐播放器
    QMediaPlayer *backgroundMusic;

    //其他变量

    //移动模式
    int move_mode = 0;//0表示随鼠标移动,1表示随键盘移动
    //存储键盘按键的列表
    QList<int> keylist;//储存移动的列表
    //游戏界面状态（有限状态机）
    int game_status = 0;//0表示正常运行，1表示游戏暂停，2表示游戏结束

    //对象池
    //敌机对象池
    QVector<EnemyPlane*> enemyplane_pool;
    QQueue<EnemyPlane*> enemyplane_queue;
    //我方子弹对象池
    QVector<HeroBullet*> herobullet_pool;
    QQueue<HeroBullet*> herobullet_queue;
    //敌方子弹对象池
    QVector<EnemyBullet*> enemybullet_pool;
    QQueue<EnemyBullet*> enemybullet_queue;
};

#endif // WIDGET_H
