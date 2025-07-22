#ifndef CONFIG_H
#define CONFIG_H
//配置文件
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QPixmap>
#include <QRect>
#include <random>
#include <QTimer>

//游戏资源

#define WINDOW_ICON ":/picture/app.ico"
#define STARTGAME_BACKGROUND ":/picture/background1.jpg"
#define STARTGAME_BUTTON ":/picture/start_game_button.png"
#define LEVEL_1_BACKGROUND ":/picture/img_bg_level_1.jpg" //第一关的背景
#define LEVEL_2_BACKGROUND ":/picture/img_bg_level_2.jpg" //第二关的背景
#define LEVEL_3_BACKGROUND ":/picture/img_bg_level_3.jpg" //第三关的背景
#define LEVEL_4_BACKGROUND ":/picture/img_bg_level_4.jpg" //第四关的背景
#define LEVEL_5_BACKGROUND ":/picture/img_bg_level_5.jpg" //第五关的背景
#define WEAPON_BACKGROUND ":/picture/weapon_background.png" //武器背景框
#define HEROPLANE_1 ":/picture/hero.png" //英雄1的图片
#define HEROPLANE_2 ":/picture/hero2.png" //英雄2的图片
#define PAUSE_PICTURE ":/picture/pause_picture.png" //暂停界面图片
#define BACKGROUND_MUSIC "qrc:/bg.wav"  //注意QUrl格式问题，否则不能播放音乐
#define ENEMYPLANE_PICTURE1 ":/picture/img-plane_1.png" //第一种敌机的图片
#define ENEMYPLANE_PICTURE2 ":/picture/img-plane_3.png" //第二种敌机的图片
#define ENEMYPLANE_PICTURE3 ":/picture/img-plane_5.png" //第三种敌机的图片
#define HEROBULLET_PICTURE1 ":/picture/bullet_10.png" //第一种英雄机子弹的图片
#define ENEMYBULLET_PICTURE1 ":/picture/bullet_3.png" //第一种敌机子弹的图片
#define WEAPON_PICTURE1 ":/picture/weapon2.png" //第一种武器的图标

//游戏系统常数
#define VIEW_WIDTH 768 //视图宽度
#define VIEW_HEIGHT 1152 //视图高度
#define GAME_PERIOD 20 //游戏周期20ms

//游戏数值常数
//英雄机1的数值

//英雄机武器1的数值
#define HEROWEAPON1_DAMAGE 20 //由于有升级系统，故数值直接在weapon上改变，根据weapon的数值决定创建的子弹的数值
#define HEROWEAPON1_INTERVAL 200
#define HEROWEAPON1_SPEED 30

//敌机1的数值

//敌机1武器的数值
#define ENEMYWEAPON1_DAMAGE 10
#define ENEMYWEAPON1_INTERVAL 2000
#define ENEMYWEAPON1_SPEED 20


#endif // CONFIG_H
