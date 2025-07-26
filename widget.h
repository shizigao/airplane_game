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
#include <QString>
#include <QSoundEffect>
#include "powerup.h"
using namespace std;
struct HeroPlaneState {
    // 基础属性
    int level = 1;
    int experience = 0;
    int next_level_experience = UPGRADE_EXPERIENCE;
    double rate_sum = 1.0;
    int max_health = HEROPLANE1_HEALTH;
    int health = HEROPLANE1_HEALTH;
    int damage = HEROPLANE1_DAMAGE;
    int bomb_count = 1;
    int score = 0;  // 添加分数保存

    // 武器状态
    struct WeaponState {
        int weapon_kind = 0;
        int weapon_level = 1;
        int damage = 0;
        int interval = 0;
        int speed = 0;
        bool exists = false;
    };

    WeaponState weapon1_state;
    WeaponState weapon2_state;
    WeaponState weapon3_state;

    // 重置状态
    void reset() {
        score=0;
        level = 1;
        experience = 0;
        next_level_experience = UPGRADE_EXPERIENCE;
        rate_sum = 1.0;
        max_health = HEROPLANE1_HEALTH;
        health = HEROPLANE1_HEALTH;
        damage = HEROPLANE1_DAMAGE;
        bomb_count = 1;

        weapon1_state = WeaponState();
        weapon2_state = WeaponState();
        weapon3_state = WeaponState();
    }
};

namespace Ui {
class Widget;
}

class Widget : public QWidget
{


public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void save_heroplane_state();           // 保存英雄机状态
    void restore_heroplane_state();        // 恢复英雄机状态
    void restore_weapon(HeroWeapon* weapon, const HeroPlaneState::WeaponState& weapon_state); // 恢复武器状态
    void init_heroplane1_weapon1();        // 初始化武器1
    void setup_weapon1_timer();           // 设置武器1计时器
    void setup_weapon2_timer();           // 设置武器2计时器
    void setup_weapon3_timer();           // 设置武器3计时器


    //加载资源
    void load_resources();//加载资源总函数
    void load_timer();//加载游戏计时器
    void load_sound();//加载音乐和音效等
    void load_object_pool();//加载对象池（可选）
    void load_pause();//加载暂停界面
    void load_end();//加载游戏结束界面
    void load_startgame();//加载开始界面资源
    void load_menu();//加载主菜单资源
    void load_level_resources();//加载关卡资源

    void load_heroplane1_weapon1_background(HeroWeapon* heroweapon);//加载英雄机1的武器1图标，传入要设置的武器指针
    void load_heroplane1_weapon2_background(HeroWeapon* heroweapon);//加载英雄机1的武器2图标，传入要设置的武器指针
    void load_heroplane1_weapon3_background(HeroWeapon* heroweapon);//加载英雄机1的武器3图标，传入要设置的武器指针
    void load_heroplane2_weapon1_background(HeroWeapon* heroweapon);//加载英雄机1的武器1图标，传入要设置的武器指针
    void load_heroplane2_weapon2_background(HeroWeapon* heroweapon);//加载英雄机1的武器2图标，传入要设置的武器指针
    void load_heroplane2_weapon3_background(HeroWeapon* heroweapon);//加载英雄机1的武器3图标，传入要设置的武器指针
    void refresh_timer();//进入关卡后要刷新计时器


    //切换页面
    void turn_to_menu();//转到主菜单
    void turn_to_level1();//转到第一关（相当于第一关的加载函数了）
    void turn_to_level2();//转到第二关（相当于第二关的加载函数了）
    void turn_to_cooperation();//转到双人合作模式

    //关卡的加载和析构k
    //关卡加载函数
    void load_level_heroplane1(int kind);//传入要初始化飞机的种类
    void load_level_heroplane2(int kind);//传入要初始化飞机的种类
    //关卡析构函数
    void delete_level();//主析构函数
    void delete_level_heroplane1();
    void delete_level_heroplane2();
    void delete_level_pools();
    void delete_level_timers();


    //实现鼠标控制飞机移动(move_mode=0)
    void heroplane_move0(HeroPlane* heroplane);
    //实现键盘控制飞机移动(move_mode=1)
    void heroplane1_move1(HeroPlane* heroplane);
    void heroplane2_move1(HeroPlane* heroplane);


    //游戏周期更新函数，表示每个游戏周期所有组件的行为
    //通用更新函数，包含英雄机的移动、敌机的移动、子弹移动、飞机碰撞检测和敌机碰撞检测

    void game_update();

    //各个关卡的更新函数，需要单独实现
    void level_1_update();//第一关的更新函数
    void level_2_update();//第二关的更新函数
    void level_3_update();//第三关的更新函数
    void level_4_update();//第四关的更新函数
    void level_5_update();//第五关的更新函数
    void cooperation_update();//双人无尽模式的更新函数


    //对象池函数
    EnemyPlane* get_enemyplane(int x, int y, int kind);//从对象池中获取敌机(初始化为kind值对应的类型，已初始化）
    EnemyBullet* get_enemybullet(int x, int y, int kind);//从对象池中获取敌人子弹(初始化为kind值对应的类型，已初始化）
    HeroBullet* get_herobullet(int x, int y, int kind);//从对象池中获取英雄机的子弹(初始化为kind值对应的类型，已初始化）
    PowerUp *get_powerup(int x, int y, int type);//从对象池中获取道具


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
    void heroplane1_release_bomb();  // 英雄机1释放炸弹
    void heroplane2_release_bomb();  // 英雄机2释放炸弹
    //敌机发射子弹
    void enemyplane_shoot(EnemyPlane* enemyplane);
    //Boss特殊发射模式
    void boss_shoot_pattern_1(EnemyPlane* boss); // Boss散弹攻击
    void boss_shoot_pattern_2(EnemyPlane* boss); // Boss环形弹幕
    void boss_shoot_pattern_3(EnemyPlane* boss); // Boss激光攻击

    //道具对象池函数

    void drop_random_powerup(double x, double y);//在指定位置随机掉落道具
    void clear_all_enemies_and_bullets();//炸弹效果：清除所有敌机和敌机子弹




    //基于暴力枚举算法的碰撞检测优化（每40ms执行一次碰撞检测）
    void collision_detection();//总碰撞检测函数
    void collision_detection_herobullet_with_enemyplane();
    void collision_detection_enemybullet_with_heroplane();
    void collision_detection_heroplane_with_enemyplane();
    //道具碰撞检测
    void collision_detection_powerup_with_heroplane();

    //播放敌机摧毁动画
    void enemyplane_destroy_animation(double x, double y);//传入播放动画的坐标

    //关卡进度管理
    void update_level_progress();//更新关卡进度
    void check_boss_spawn();//检查是否应该生成Boss
    void spawn_boss(int boss_kind);//生成Boss
    void show_boss_warning();//显示Boss警告
    void update_boss_health_bar();//更新Boss血条

    //关卡完成检查
    void check_level_complete();//检查关卡是否完成

    //最高分存取
    void saveScore();//存储最高分
    int loadHighScore();//读取本地最高分


public:
    Ui::Widget *ui;

    //英雄机
    HeroPlane *heroplane1 = nullptr, *heroplane2 = nullptr;//因为有多人模式，所以设置两个英雄机

    //计时器
    //游戏周期计时器（20ms为一个周期)
    QTimer *game_timer = nullptr;
    //英雄机武器计时器（与武器相互连接）
    QTimer *heroplane1_weapon1_timer = nullptr, *heroplane1_weapon2_timer = nullptr, *heroplane1_weapon3_timer = nullptr;
    QTimer *heroplane2_weapon1_timer = nullptr, *heroplane2_weapon2_timer = nullptr, *heroplane2_weapon3_timer = nullptr;
    //表示是否连续开火的状态
    bool heroplane1_weapon1_continuous_firing = false, heroplane1_weapon2_continuous_firing = false, heroplane1_weapon3_continuous_firing = false;
    bool heroplane2_weapon1_continuous_firing = false, heroplane2_weapon2_continuous_firing = false, heroplane2_weapon3_continuous_firing = false;
    //英雄机无敌状态计时器（与英雄机相互连接）
    QTimer *heroplane1_invincible_timer = nullptr, *heroplane2_invincible_timer = nullptr;


    //主视图
    QGraphicsView main_view;


    //场景（游戏中所有的场景都在这）
    QGraphicsScene main_scene;//开始界面
    QGraphicsScene main_scene2;//主菜单
    QGraphicsScene level_scene;//关卡场景

    //暂停界面
    QGraphicsRectItem *pause_background = nullptr;//半透明黑色矩形框，用于模拟暂停界面
    QGraphicsPixmapItem *pause_picture = nullptr;

    //结束界面
    QGraphicsPixmapItem *end_picture = nullptr;


    //背景图片
    QGraphicsPixmapItem* startgame_background1 = nullptr;
    QGraphicsPixmapItem* startgame_background2 = nullptr;
    QGraphicsPixmapItem* level_1_background1 = nullptr, *level_1_background2 = nullptr;
    QGraphicsPixmapItem* level_2_background1 = nullptr, *level_2_background2 = nullptr;
    QGraphicsPixmapItem* level_3_background1 = nullptr, *level_3_background2 = nullptr;
    QGraphicsPixmapItem* level_4_background1 = nullptr, *level_4_background2 = nullptr;
    QGraphicsPixmapItem* level_5_background1 = nullptr, *level_5_background2 = nullptr;

    //按钮

    //游戏主界面按钮
    QToolButton *startgame_button = nullptr, *single_level = nullptr, *single_infinite = nullptr,
    *double_infinite = nullptr, *double_against = nullptr, *record = nullptr, *help = nullptr, *settings = nullptr;

    //ProgressBar
    //关卡进度条
    QProgressBar *level_progressBar = nullptr;
    //Boss血条
    QProgressBar *boss_healthBar = nullptr;
    QLineEdit *boss_name_display = nullptr;

    //生命条
    QProgressBar *heroplane1_healthBar = nullptr, *heroplane2_healthBar = nullptr;
    QLineEdit *heroplane1_health_value = nullptr, *heroplane2_health_value = nullptr;
    //经验条
    QProgressBar *heroplane1_experience_bar = nullptr, *heroplane2_experience_bar = nullptr;
    //武器背景
    QGraphicsPixmapItem *heroplane1_weapon1_background = nullptr, *heroplane2_weapon1_background = nullptr;
    QGraphicsPixmapItem *heroplane1_weapon2_background = nullptr, *heroplane2_weapon2_background = nullptr;
    QGraphicsPixmapItem *heroplane1_weapon3_background = nullptr, *heroplane2_weapon3_background = nullptr;
    QGraphicsPixmapItem *heroplane1_weapon4_background = nullptr, *heroplane2_weapon4_background = nullptr;
    //武器等级
    QLineEdit *heroplane1_weapon1_level_text = nullptr, *heroplane1_weapon2_level_text = nullptr, *heroplane1_weapon3_level_text = nullptr,
     *heroplane2_weapon1_level_text = nullptr, *heroplane2_weapon2_level_text = nullptr, *heroplane2_weapon3_level_text = nullptr;
    QLineEdit *heroplane1_bomb_count = nullptr;  // 英雄机1炸弹数量显示
    QLineEdit *heroplane2_bomb_count = nullptr;  // 英雄机2炸弹数量显示

    //分数板
    QLineEdit *score_board = nullptr;
    int score = 0;//分数

    //音乐播放器
    QMediaPlayer *backgroundMusic = nullptr;
    QSoundEffect* bullet_sound = nullptr, *bomb_sound = nullptr, *enemyplane_dead_sound = nullptr;

    //对象池
    //敌机对象池
    QList<EnemyPlane*> enemyplane_pool;
    QQueue<EnemyPlane*> enemyplane_queue;
    //我方子弹对象池
    QList<HeroBullet*> herobullet_pool;
    QQueue<HeroBullet*> herobullet_queue;
    //敌方子弹对象池
    QList<EnemyBullet*> enemybullet_pool;
    QQueue<EnemyBullet*> enemybullet_queue;
    //道具对象池
    QList<PowerUp*> powerup_pool;
    QQueue<PowerUp*> powerup_queue;


    QLineEdit *highScoreDisplay = nullptr; // 显示最高分的控件

    //关卡进度系统
    int enemies_killed_in_level = 0; //当前关卡击败的敌机数量
    int required_enemies_for_level = 0; //当前关卡需要击败的敌机数量
    bool boss_spawned = false; //Boss是否已经生成
    bool boss_warning_shown = false; //Boss警告是否已显示
    EnemyPlane* current_boss = nullptr; //当前关卡的Boss指针
    QTimer* boss_warning_timer = nullptr; //Boss警告计时器
    QGraphicsPixmapItem* boss_warning_image = nullptr; //Boss警告图片
    QLineEdit* level_progress_text = nullptr; //关卡进度文字显示


    //其他变量

    //移动模式
    int move_mode = 1;//0表示随鼠标移动,1表示随键盘移动
    //存储键盘按键的列表
    QList<int> keylist1;//储存英雄机1的移动列表
    QList<int> keylist2;//储存英雄机2的移动列表
    //游戏界面状态（有限状态机）
    int game_status = 0;//0表示正常运行，1表示游戏暂停，2表示游戏结束

    //游戏处于哪一关或哪一种模式
    int game_level = 0;//0表示菜单，1表示第一关，2表示第二关，3表示第3关，4表示第4关，5表示第5关，6表示单人无尽模式，7表示双人无尽模式
    HeroPlaneState saved_heroplane1_state;
    HeroPlaneState saved_heroplane2_state;
    bool use_saved_state = false;

    //使用炸弹时显示的图片
    QGraphicsPixmapItem* bomb_picture = nullptr;



};

#endif // WIDGET_H
