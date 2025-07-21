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

#define VIEW_WIDTH 768 //视图宽度
#define VIEW_HEIGHT 1152 //视图高度
#define GAME_PERIOD 10 //游戏周期10ms
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
#define HEROBULLET_PICTURE1 ":/picture/bullet_10.png" //第一种英雄机子弹的图片
#define ENEMYBULLET_PICTURE1 ":/picture/bullet_3.png" //第一种敌机子弹的图片


#endif // CONFIG_H
