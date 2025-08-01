#ifndef CONFIG_H
#define CONFIG_H

//通用头文件
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>

//配置文件

//游戏框宽度和高度
#define GAME_WIDTH 768
#define GAME_HEIGHT 1152

//图片、音效路径
//开始游戏界面
#define STARTGAME_BACKGROUND ":/resource/startgame_background.png"  //开始游戏背景
#define STARTGAME_BUTTON ":/resource/startgame_button.png"  //开始游戏按钮图片

//主菜单界面
#define MENU_BACKGROUND ":/resource/menu_background.png" //主菜单背景
#define MENU_ONE_PLAYER_LEVEL_BUTTON_PICTURE ":/resource/one_player_level.png"
#define MENU_ONE_PLAYER_ENDLESS_BUTTON_PICTURE ":/resource/one_player_endless.png"
#define MENU_TWO_PLAYER_ENDLESS_BUTTON_PICTURE ":/resource/two_player_endless.png"
#define MENU_TWO_PLAYER_AGAINST_BUTTON_PICTURE ":/resource/two_player_against.png"
#define MENU_RECORD_BUTTON_PICTURE ":/resource/record.png"
#define MENU_INTRODUCTION_BUTTON_PICTURE ":/resource/introduction.png"
#define MENU_SETTINGS_BUTTON_PICTURE ":/resource/settings.png"

//关卡背景
#define LEVEL1_BACKGROUND ":/resource/img_bg_level_1.jpg" //第一关的背景
#define LEVEL2_BACKGROUND ":/resource/img_bg_level_2.jpg" //第二关的背景
#define LEVEL3_BACKGROUND ":/resource/img_bg_level_3.jpg" //第三关的背景
#define LEVEL4_BACKGROUND ":/resource/img_bg_level_4.jpg" //第四关的背景
#define LEVEL5_BACKGROUND ":/resource/img_bg_level_5.jpg" //第五关的背景


//英雄机图片
#define HEROPLANE1_PICTURE ":/resource/hero.png" //第一种英雄机的图片
#define HEROPLANE2_PICTURE ":/resource/hero2.png" //第二种英雄机的图片

//英雄机子弹图片
#define HEROBULLET_PICTURE1 ":/resource/bullet_10.png" //第一种英雄机的子弹


//敌机的图片
#define ENEMYPLANE1_PICTURE ":/resource/img-plane_1.png" //第一种敌机的图片

//敌机子弹图片
#define ENEMYBULLET1_PICTURE ":/resource/bullet_1.png" //第一种敌机子弹的图片

//游戏周期
#define GAME_PERIOD 10 //游戏周期：10ms



//游戏常量

//英雄机的属性
//第一种英雄机
#define HEROPLANE1_SPEED 5

//第二种英雄机
#define HEROPLANE2_SPEED 3

//英雄机第一种武器的属性
#define HEROWEAPON1_INTERVAL 200 //发射间隔200ms
#define HEROWEAPON1_SPEED 20 //发射出的子弹的移动速度
#define HEROWEAPON1_DAMAGE 20 //子弹的伤害


//敌机
//第一种敌机
#define ENEMYPLANE1_SPEED 1 //移动速度
#define ENEMYPLANE1_HEALTH 100 //敌机的生命

//第一种敌机武器的属性
#define ENEMYWEAPON1_INTERVAL 2000 //发射间隔2000ms
#define ENEMYWEAPON1_SPEED 10 //发射出的子弹的移动速度

#endif // CONFIG_H
