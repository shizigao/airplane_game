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
#include <cmath>

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
#define HEROPLANE_1_PICTURE ":/picture/hero.png" //英雄1的图片
#define HEROPLANE_2_PICTURE ":/picture/hero2.png" //英雄2的图片
#define PAUSE_PICTURE ":/picture/pause_picture.png" //暂停界面图片
#define END_BACKGROUND ":/picture/endbackground.png" //结束界面的图片
#define BACKGROUND_MUSIC "qrc:/bg.wav"  //注意QUrl格式问题，否则不能播放音乐
#define BULLET_SOUND "qrc:/bullet_sound.wav" //子弹音效
#define ENEMYPLANE_PICTURE1 ":/picture/img-plane_1.png" //第一种敌机的图片
#define ENEMYPLANE_PICTURE2 ":/picture/img-plane_3.png" //第二种敌机的图片
#define ENEMYPLANE_PICTURE3 ":/picture/img-plane_5.png" //第三种敌机的图片
#define ENEMYPLANE_PICTURE4 ":/picture/enemyplane1.png" //第四种敌机的图片
#define BOSS_PICTURE1 ":/picture/img-boss_1.png" //第一个Boss的图片
#define BOSS_PICTURE2 ":/picture/img-boss_2.png" //第二个Boss的图片
#define ENEMYBULLET_PICTURE1 ":/picture/bullet_1.png" //第一种敌机子弹的图片
#define ENEMYBULLET_PICTURE2 ":/picture/bullet_3.png" //第二种敌机子弹的图片
#define ENEMYBULLET_PICTURE3 ":/picture/bullet_4.png" //第三种敌机子弹的图片
#define ENEMYBULLET_PICTURE4 ":/picture/bullet_6.png" //第四种敌机子弹的图片
#define BOSS_BULLET_PICTURE1 ":/picture/bullet_7.png" //Boss子弹1的图片
#define BOSS_BULLET_PICTURE2 ":/picture/bullet_8.png" //Boss子弹2的图片
#define BOSS_BULLET_PICTURE3 ":/picture/bullet_9.png" //Boss子弹3的图片
#define HEROBULLET_PICTURE1 ":/picture/bullet_10.png" //第一种英雄机子弹的图片
#define HEROBULLET_PICTURE2 ":/picture/hero_bullet.png" //第二种英雄机子弹的图片
#define HEROBULLET_PICTURE3 ":/picture/bullet_12.png" //第三种英雄机子弹的图片
#define HEROBULLET_PICTURE4 ":/picture/bullet_14.png" //第四种英雄机子弹的图片
#define WEAPON_PICTURE1 ":/picture/weapon2.png" //第一种武器的图标
#define WEAPON_PICTURE2 ":/picture/weapon1.png" //第二种武器的图标
#define WEAPON_PICTURE3 ":/picture/weapon3.png" //第三种武器的图标
#define WEAPON_PICTURE4 ":/picture/weapon4.png" //第四种武器的图标
#define SHIELD_PICTURE ":/picture/shield.png" //护盾的图片
#define ENEMYPLANE_DESTROY_ANIMATION1 ":/picture/bomb-2.png" //敌机摧毁动画（一共四帧）
#define ENEMYPLANE_DESTROY_ANIMATION2 ":/picture/bomb-3.png" //敌机摧毁动画
#define ENEMYPLANE_DESTROY_ANIMATION3 ":/picture/bomb-4.png" //敌机摧毁动画
#define ENEMYPLANE_DESTROY_ANIMATION4 ":/picture/bomb-5.png" //敌机摧毁动画
#define UPGRADE_PICTURE ":/picture/upgrade.png" //升级图片
#define BOMB_SOUND "qrc:/bomb_sound.wav" //使用炸弹的声音
#define ENEMYPLANE_DEAD_SOUND "qrc:/bomb.wav" //敌机死亡的声音
#define BOMB_PICTURE ":/picture/bomb_picture.png" //使用炸弹的背景


//游戏系统常数
#define VIEW_WIDTH 768 //视图宽度
#define VIEW_HEIGHT 1152 //视图高度
#define GAME_PERIOD 20 //游戏周期20ms
#define INVINCIBLE_TIME 1000 //每次被击中后的无敌时间
#define UPGRADE_EXPERIENCE 1500 //英雄机升级的经验基数
#define UPGRADE_RATE 1.2 //英雄机升级的数值提升比率


//关卡进度常数
#define LEVEL_1_ENEMY_COUNT 50 //第一关需要击败的敌机数量
#define LEVEL_2_ENEMY_COUNT 60 //第二关需要击败的敌机数量
#define BOSS_WARNING_TIME 3000 //Boss出现前的警告时间(ms)

//游戏数值常数
//英雄机1的数值
#define HEROPLANE1_HEALTH 100
#define HEROPLANE1_SPEED 10
#define HEROPLANE1_DAMAGE 30 //撞击伤害
//英雄机2的数值
#define HEROPLANE2_HEALTH 180
#define HEROPLANE2_SPEED 6
#define HEROPLANE2_DAMAGE 50

//英雄机武器1的数值
#define HEROWEAPON1_DAMAGE 20 //由于有升级系统，故数值直接在weapon上改变，根据weapon的数值决定创建的子弹的数值
#define HEROWEAPON1_INTERVAL 200
#define HEROWEAPON1_SPEED 25

//英雄机武器2的数值
#define HEROWEAPON2_DAMAGE 120
#define HEROWEAPON2_INTERVAL 1000
#define HEROWEAPON2_SPEED 15

//英雄机武器3的数值
#define HEROWEAPON3_DAMAGE 40
#define HEROWEAPON3_INTERVAL 500
#define HEROWEAPON3_SPEED 40

//英雄机武器4的数值
#define HEROWEAPON4_DAMAGE 80
#define HEROWEAPON4_INTERVAL 1000
#define HEROWEAPON4_SPEED 20


//敌机1的数值
#define ENEMYPLANE1_HEALTH 60
#define ENEMYPLANE1_SPEED 2
#define ENEMYPLANE1_DAMAGE 10 //撞击伤害
#define ENEMYPLANE1_SCORE 100

// 敌机2参数
#define ENEMYPLANE2_SPEED 2.0
#define ENEMYPLANE2_HEALTH 100
#define ENEMYPLANE2_DAMAGE 12
#define ENEMYPLANE2_SCORE 150

// 敌机3参数
#define ENEMYPLANE3_SPEED 3.0
#define ENEMYPLANE3_HEALTH 140
#define ENEMYPLANE3_DAMAGE 15
#define ENEMYPLANE3_SCORE 200

// 敌机4参数
#define ENEMYPLANE4_SPEED 2.0
#define ENEMYPLANE4_HEALTH 200
#define ENEMYPLANE4_DAMAGE 40
#define ENEMYPLANE4_SCORE 300

// Boss1参数（第一关Boss）
#define BOSS1_SPEED 1.5
#define BOSS1_HEALTH 8000
#define BOSS1_DAMAGE 50
#define BOSS1_SCORE 5000

// Boss2参数（第二关Boss）
#define BOSS2_SPEED 2.0
#define BOSS2_HEALTH 16000
#define BOSS2_DAMAGE 80
#define BOSS2_SCORE 8000

// 敌机武器参数
#define ENEMYWEAPON1_DAMAGE 10
#define ENEMYWEAPON1_INTERVAL 2000
#define ENEMYWEAPON1_SPEED 6.0

#define ENEMYWEAPON2_DAMAGE 15
#define ENEMYWEAPON2_INTERVAL 3000
#define ENEMYWEAPON2_SPEED 5.0

#define ENEMYWEAPON3_DAMAGE 10
#define ENEMYWEAPON3_INTERVAL 1200
#define ENEMYWEAPON3_SPEED 7.0

#define ENEMYWEAPON4_DAMAGE 30
#define ENEMYWEAPON4_INTERVAL 4000
#define ENEMYWEAPON4_SPEED 4.0

// Boss武器参数
#define BOSSWEAPON1_DAMAGE 25
#define BOSSWEAPON1_INTERVAL 800
#define BOSSWEAPON1_SPEED 8.0

#define BOSSWEAPON2_DAMAGE 35
#define BOSSWEAPON2_INTERVAL 600
#define BOSSWEAPON2_SPEED 10.0

//道具数值常数
#define POWERUP_SPEED 3                    //道具下降速度
#define POWERUP_HEALTH_RESTORE 50          //生命恢复道具的恢复量
#define POWERUP_EXP_BONUS 500              //经验加成道具的经验值
#define POWERUP_FIREPOWER_DURATION 10000   //火力增强持续时间(ms)
#define POWERUP_SHIELD_DURATION 8000       //护盾强化持续时间(ms)
#define POWERUP_DROP_CHANCE 30             //道具掉落概率(百分比)

//道具效果类型
#define POWERUP_TYPE_FIREPOWER 1    //火力增强
#define POWERUP_TYPE_HEALTH 2       //生命恢复
#define POWERUP_TYPE_BOMB 3         //炸弹
#define POWERUP_TYPE_SHIELD 4       //护盾强化
#define POWERUP_TYPE_EXP 5          //经验加成

//Boss阶段常数
#define BOSS_PHASE_1_HEALTH_RATIO 0.8  //Boss第一阶段切换的生命值比例
#define BOSS_PHASE_2_HEALTH_RATIO 0.7  //Boss第二阶段切换的生命值比例
#define BOSS_PHASE_3_HEALTH_RATIO 0.4  //Boss第三阶段切换的生命值比例

#endif // CONFIG_H
