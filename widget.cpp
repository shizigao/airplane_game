#include "widget.h"
#include "ui_widget.h"
#include <QToolButton>

//游戏主函数
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //进行初始化
    ui->setupUi(this);
    this->setWindowTitle("双人飞机大战");
    this->setWindowIcon(QIcon(WINDOW_ICON));
    main_view.setScene(&main_scene);
    main_view.setParent(this);
    main_view.centerOn(384, 576);//将视图对准
    main_view.setSceneRect(0, 0, 768, 1152);

    // 禁用水平和垂直滚动条
    main_view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    main_view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    //加载资源
    load_resources();





}

Widget::~Widget()
{
    delete ui;
}

//加载资源的总函数
void Widget::load_resources()
{

    load_sound();
    //load_object_pool();
    load_timer();
    load_startgame();
    load_menu();
    load_level_resources();
    load_pause();
    load_end();
}

void Widget::load_timer()
{
    game_timer = new QTimer();
    game_timer->start(GAME_PERIOD);
    heroplane1_weapon1_timer = new QTimer();
    heroplane1_weapon2_timer = new QTimer();
    heroplane1_weapon3_timer = new QTimer();
    heroplane2_weapon1_timer = new QTimer();
    heroplane2_weapon2_timer = new QTimer();
    heroplane2_weapon3_timer = new QTimer();
    heroplane1_invincible_timer = new QTimer();
    heroplane1_invincible_timer->setSingleShot(true);//无敌状态计时器只计时一次
    heroplane2_invincible_timer = new QTimer();
    heroplane2_invincible_timer->setSingleShot(true);//无敌状态计时器只计时一次

}

void Widget::load_sound()
{
    backgroundMusic = new QMediaPlayer(this);

    // 设置音乐文件路径（支持本地文件和网络地址）
    backgroundMusic->setMedia(QUrl(BACKGROUND_MUSIC));

    // 设置音量（0-100）
    backgroundMusic->setVolume(10);
    // 设置循环播放
    connect(backgroundMusic, &QMediaPlayer::stateChanged, [=](QMediaPlayer::State state) {
            if (state == QMediaPlayer::StoppedState) {
                backgroundMusic->play(); // 播放结束后重新开始
            }
        });
    // 开始播放
    backgroundMusic->play();

    //加载子弹音效
    bullet_sound = new QSoundEffect(this);
    bullet_sound->setSource(QUrl(BULLET_SOUND));
    bullet_sound->setVolume(0.2);
    if (bullet_sound->status() == QSoundEffect::Error){
        qDebug() << "加载失败";
    }

    //加载炸弹音效
    bomb_sound = new QSoundEffect(this);
    bomb_sound->setSource(QUrl(BOMB_SOUND));
    bomb_sound->setVolume(0.2);
    if (bomb_sound->status() == QSoundEffect::Error){
        qDebug() << "加载失败";
    }

    //加载敌机死亡音效
    enemyplane_dead_sound = new QSoundEffect(this);
    enemyplane_dead_sound->setSource(QUrl(ENEMYPLANE_DEAD_SOUND));
    enemyplane_dead_sound->setVolume(0.2);
    if (enemyplane_dead_sound->status() == QSoundEffect::Error){
        qDebug() << "加载失败";
    }

}

//加载对象池
void Widget::load_object_pool()
{
    //预先创建一定数量的对象
    //创建10个敌机和对应计时器
    for (int i = 0; i < 10; i++){
        QTimer* timer = new QTimer();
        EnemyPlane* enemyplane = new EnemyPlane(timer);
        //连接信号槽（控制敌机自动开火）
        connect(timer, QTimer::timeout, this, [=](){
            enemyplane_shoot(enemyplane);
        });
        enemyplane->status = 1;
        enemyplane_pool.append(enemyplane);
        enemyplane_queue.append(enemyplane);
        enemyplane->setVisible(false);
        level_scene.addItem(enemyplane);
    }
    //创建10颗我方子弹
    for (int i = 0; i < 10; i++){
        HeroBullet* herobullet = new HeroBullet();
        herobullet->status = 1;
        herobullet_pool.append(herobullet);
        herobullet_queue.append(herobullet);
        herobullet->setVisible(false);
        level_scene.addItem(herobullet);
    }
    //创建10颗敌方子弹
    for (int i = 0; i < 10; i++){
        EnemyBullet* enemybullet = new EnemyBullet();
        enemybullet->status = 1;
        enemybullet_pool.append(enemybullet);
        enemybullet_queue.append(enemybullet);
        enemybullet->setVisible(false);
        level_scene.addItem(enemybullet);
    }
    //创建10个道具
        for (int i = 0; i < 10; i++){
            PowerUp* powerup = new PowerUp();
            powerup->status = 1;
            powerup_pool.append(powerup);
            powerup_queue.append(powerup);
            powerup->setVisible(false);
            level_scene.addItem(powerup);
        }
}

void Widget::load_pause()
{
    pause_background = new QGraphicsRectItem();
    pause_background->setRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT);
    pause_background->setBrush(QColor(0, 0, 0, 128)); // 黑色半透明（alpha=128，0-255）
    pause_background->setZValue(90); // 层级设为次顶层（高于游戏元素）
    pause_background->setVisible(false); // 默认隐藏
    level_scene.addItem(pause_background);
    pause_picture = new QGraphicsPixmapItem();
    pause_picture->setPixmap(QPixmap(PAUSE_PICTURE));
    pause_picture->setScale(1);
    pause_picture->setPos(VIEW_WIDTH / 2 - pause_picture->pixmap().width() / 2, VIEW_HEIGHT / 2 - pause_picture->pixmap().height() / 2);
    pause_picture->setZValue(91); //层级设置比pause_background要高
    pause_picture->setVisible(false);
    level_scene.addItem(pause_picture);
}

void Widget::load_end()
{
    end_picture = new QGraphicsPixmapItem();
    end_picture->setPixmap(QPixmap(END_BACKGROUND));
    end_picture->setScale(1);
    end_picture->setPos(VIEW_WIDTH / 2 - end_picture->pixmap().width() / 2, VIEW_HEIGHT / 2 - end_picture->pixmap().height() / 2);
    end_picture->setZValue(91); //层级设置比pause_background要高
    end_picture->setVisible(false);
    level_scene.addItem(end_picture);
}

//加载开始界面
void Widget::load_startgame()
{
    //加载开始界面资源
    main_scene.setParent(this);
    startgame_background1 = new QGraphicsPixmapItem();
    startgame_background1->setPixmap(QPixmap(STARTGAME_BACKGROUND));
    startgame_background1->setScale(1.5);//放大背景图片，使之契合视图大小
    main_scene.addItem(startgame_background1);
    //加载“开始游戏”按钮
    startgame_button = new QToolButton();
    startgame_button->setIcon(QPixmap(STARTGAME_BUTTON));
    startgame_button->move(240, 560);
    startgame_button->setFixedSize(270, 89);
    startgame_button->setIconSize(QSize(270, 89));
    startgame_button->setAutoRaise(true);
    main_scene.addWidget(startgame_button);
    //为按钮设置信号槽
    connect(startgame_button, QToolButton::clicked, this, turn_to_menu);
}

//加载主菜单
void Widget::load_menu()
{
    //加载主菜单资源

    main_scene2.setParent(this);
    startgame_background2 = new QGraphicsPixmapItem();
    startgame_background2->setPixmap(QPixmap(STARTGAME_BACKGROUND));
    startgame_background2->setScale(1.5);//放大背景图片，使之契合视图大小
    main_scene2.addItem(startgame_background2);

    single_level = new QToolButton();
    single_level->setText("单人闯关");
    single_infinite = new QToolButton();
    single_infinite->setText("单人无尽");
    double_infinite = new QToolButton();
    double_infinite->setText("双人无尽");
    double_against = new QToolButton();
    double_against->setText("双人对抗");
    record = new QToolButton();
    record->setText("游戏记录");
    help = new QToolButton();
    help->setText("操作说明");
    settings = new QToolButton();
    settings->setText("游戏设置");

    single_level->setFixedSize(180, 90);
    single_infinite->setFixedSize(180, 90);
    double_infinite->setFixedSize(180, 90);
    double_against->setFixedSize(180, 90);
    record->setFixedSize(180, 90);
    help->setFixedSize(180, 90);
    settings->setFixedSize(180, 90);

    single_level->move(150, 300);
    single_infinite->move(450, 300);
    double_infinite->move(150, 500);
    double_against->move(450, 500);
    record->move(150, 700);
    help->move(450, 700);
    settings->move(300, 900);

    main_scene2.addWidget(single_level);
    main_scene2.addWidget(single_infinite);
    main_scene2.addWidget(double_infinite);
    main_scene2.addWidget(double_against);
    main_scene2.addWidget(record);
    main_scene2.addWidget(help);
    main_scene2.addWidget(settings);

    // 初始化最高分显示控件（可以在菜单中或专门的记录界面）
        highScoreDisplay = new QLineEdit();
        highScoreDisplay->setReadOnly(true);
        highScoreDisplay->setFixedSize(200, 50);
        highScoreDisplay->move(300, 400); // 调整位置
        highScoreDisplay->setStyleSheet(R"(
            QLineEdit:read-only {
                font-family: "Arial Black";
                font-size: 18px;
                font-weight: bold;
                background-color: transparent;
                border: 2px solid #FF0B0B;
                color: #FF0B0B;
            }
        )");
        main_scene2.addWidget(highScoreDisplay);
        highScoreDisplay->setVisible(false); // 初始隐藏

        // 记录按钮点击事件：显示最高分
        connect(record, &QToolButton::clicked, this, [=]() {
            int highScore = loadHighScore();
            highScoreDisplay->setText(QString("最高分: %1").arg(highScore));
            highScoreDisplay->setVisible(true);
            // 可以隐藏其他菜单按钮，只显示最高分和返回按钮
        });

    //设置信号槽
    connect(single_level, QToolButton::clicked, this, turn_to_level1);
    connect(double_infinite, QToolButton::clicked, this, turn_to_cooperation);
}

void Widget::load_level_resources()
{
    //加载关卡背景
    level_1_background1 = new QGraphicsPixmapItem();
    level_1_background1->setPixmap(QPixmap(LEVEL_1_BACKGROUND));
    level_1_background1->setScale(1.6);
    level_1_background1->setZValue(-10);
    level_1_background2 = new QGraphicsPixmapItem();
    level_1_background2->setPixmap(QPixmap(LEVEL_1_BACKGROUND));
    level_1_background2->setScale(1.6);
    level_1_background2->setPos(0, -1229);
    level_1_background2->setZValue(-10);

    level_2_background1 = new QGraphicsPixmapItem();
    level_2_background1->setPixmap(QPixmap(LEVEL_2_BACKGROUND));
    level_2_background1->setScale(1.6);
    level_2_background1->setZValue(-10);
    level_2_background2 = new QGraphicsPixmapItem();
    level_2_background2->setPixmap(QPixmap(LEVEL_2_BACKGROUND));
    level_2_background2->setScale(1.6);
    level_2_background2->setPos(0, -1229);
    level_2_background2->setZValue(-10);

    level_3_background1 = new QGraphicsPixmapItem();
    level_3_background1->setPixmap(QPixmap(LEVEL_3_BACKGROUND));
    level_3_background1->setScale(1.6);
    level_3_background1->setZValue(-10);
    level_3_background2 = new QGraphicsPixmapItem();
    level_3_background2->setPixmap(QPixmap(LEVEL_3_BACKGROUND));
    level_3_background2->setScale(1.6);
    level_3_background2->setPos(0, -1229);
    level_3_background2->setZValue(-10);

    level_4_background1 = new QGraphicsPixmapItem();
    level_4_background1->setPixmap(QPixmap(LEVEL_4_BACKGROUND));
    level_4_background1->setScale(1.6);
    level_4_background1->setZValue(-10);
    level_4_background2 = new QGraphicsPixmapItem();
    level_4_background2->setPixmap(QPixmap(LEVEL_4_BACKGROUND));
    level_4_background2->setScale(1.6);
    level_4_background2->setPos(0, -1229);
    level_4_background2->setZValue(-10);

    level_5_background1 = new QGraphicsPixmapItem();
    level_5_background1->setPixmap(QPixmap(LEVEL_5_BACKGROUND));
    level_5_background1->setScale(1.6);
    level_5_background1->setZValue(-10);
    level_5_background2 = new QGraphicsPixmapItem();
    level_5_background2->setPixmap(QPixmap(LEVEL_5_BACKGROUND));
    level_5_background2->setScale(1.6);
    level_5_background2->setPos(0, -1229);
    level_5_background2->setZValue(-10);

    level_scene.addItem(level_1_background1);
    level_scene.addItem(level_1_background2);
    level_1_background1->setVisible(false);//先设置不可见，等对应关卡再设置可见
    level_scene.addItem(level_2_background1);
    level_scene.addItem(level_2_background2);
    level_2_background1->setVisible(false);
    level_scene.addItem(level_3_background1);
    level_scene.addItem(level_3_background2);
    level_3_background1->setVisible(false);
    level_scene.addItem(level_4_background1);
    level_scene.addItem(level_4_background2);
    level_4_background1->setVisible(false);
    level_scene.addItem(level_5_background1);
    level_scene.addItem(level_5_background2);
    level_5_background1->setVisible(false);


    //加载ui
    //关卡进度条
    level_progressBar = new QProgressBar();
    level_progressBar->setFixedSize(200, 20);
    level_progressBar->setStyleSheet( "QProgressBar {"
                                        "   text-align: center;"  // 文本位置
                                        "   color: #333;"         // 文本颜色
                                        "}"
                                        "QProgressBar::chunk {"
                                        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, " //背景渐变色
                                        "                               stop:0 #92FF77, "
                                        "                               stop:1 #FF2626);"
                                        "}");


    level_progressBar->setValue(100);
    level_progressBar->setVisible(false);
    level_scene.addWidget(level_progressBar);


    //加载生命条
    //玩家1的生命条
    heroplane1_healthBar = new QProgressBar();
    heroplane1_healthBar->setFixedSize(60, 200);
    heroplane1_healthBar->move(VIEW_WIDTH - 40, VIEW_HEIGHT - 200);
    heroplane1_healthBar->setValue(100);
    heroplane1_healthBar->setTextVisible(false);//生命值比率不可见，用生命值属性替代
    heroplane1_healthBar->setStyleSheet("QProgressBar::chunk {"
                                     "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                                     "                               stop:0 #92FF77, "
                                     "                               stop:1 #FF2626);"
                                     "}");
    heroplane1_healthBar->setOrientation(Qt::Vertical);//设置生命条垂直
    heroplane1_healthBar->setVisible(false);

    level_scene.addWidget(heroplane1_healthBar);

    heroplane1_health_value = new QLineEdit();
    heroplane1_health_value->setText("233");
    heroplane1_health_value->setReadOnly(true);
    heroplane1_health_value->move(VIEW_WIDTH - 40, VIEW_HEIGHT - 125);
    heroplane1_health_value->setStyleSheet(R"(
                                       QLineEdit:read-only {
                                           font-family: "Arial Black";  /* 字体家族 */
                                           font-size: 20px;            /* 字体大小 */
                                       font-weight: bold;
                                           background-color: transparent;
                                           border: none;  /* 可选：去掉边框 */
                                           color: #FF0B0B;   /* 文字颜色 */
                                       }
                                   )");
    heroplane1_health_value->setVisible(false);
    level_scene.addWidget(heroplane1_health_value);

    //玩家2的生命条

    heroplane2_healthBar = new QProgressBar();
    heroplane2_healthBar->setFixedSize(40, 200);
    heroplane2_healthBar->move(0, VIEW_HEIGHT - 200);
    heroplane2_healthBar->setValue(100);
    heroplane2_healthBar->setTextVisible(false);//生命值比率不可见，用生命值属性替代
    heroplane2_healthBar->setStyleSheet("QProgressBar::chunk {"
                                     "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                                     "                               stop:0 #92FF77, "
                                     "                               stop:1 #FF2626);"
                                     "}");
    heroplane2_healthBar->setOrientation(Qt::Vertical);//设置生命条垂直
    heroplane2_healthBar->setVisible(false);

    level_scene.addWidget(heroplane2_healthBar);

    heroplane2_health_value = new QLineEdit();
    heroplane2_health_value->setText("233");
    heroplane2_health_value->setReadOnly(true);
    heroplane2_health_value->move(0, VIEW_HEIGHT - 125);
    heroplane2_health_value->setStyleSheet(R"(
                                       QLineEdit:read-only {
                                           font-family: "Arial Black";  /* 字体家族 */
                                           font-size: 20px;            /* 字体大小 */
                                       font-weight: bold;
                                           background-color: transparent;
                                           border: none;  /* 可选：去掉边框 */
                                           color: #FF0B0B;   /* 文字颜色 */
                                       }
                                   )");
    heroplane2_health_value->setVisible(false);
    level_scene.addWidget(heroplane2_health_value);

    //加载经验条
    //英雄机1的经验条
    heroplane1_experience_bar = new QProgressBar();
    heroplane1_experience_bar->setFixedSize(40, 20);
    heroplane1_experience_bar->move(VIEW_WIDTH - 40, VIEW_HEIGHT - 220);
    heroplane1_experience_bar->setValue(100);
    heroplane1_experience_bar->setTextVisible(false);
    heroplane1_experience_bar->setVisible(false);
    heroplane1_experience_bar->setStyleSheet(R"(
                                             QProgressBar {
                                                 border: 3px solid #333;          /* 深色边框 */
                                                 border-radius: 4px;              /* 轻微圆角 */
                                                 background-color: #1a1a1a;       /* 深色背景 */
                                                 text-align: center;              /* 进度文字居中 */
                                                 color: #ffffff;                  /* 文字颜色为白色 */
                                                 height: 30px;                    /* 进度条高度 */
                                             }
                                             QProgressBar::chunk {
                                                 background-color: #4CAF50;       /* 绿色进度块 */
                                                 border-radius: 2px;              /* 进度块轻微圆角 */
                                                 margin: 1px;                     /* 进度块与边框的间距 */
                                             }
                                         )");
    level_scene.addWidget(heroplane1_experience_bar);
    //英雄机2的经验条
    heroplane2_experience_bar = new QProgressBar();
    heroplane2_experience_bar->setFixedSize(40, 20);
    heroplane2_experience_bar->move(0, VIEW_HEIGHT - 220);
    heroplane2_experience_bar->setValue(100);
    heroplane2_experience_bar->setTextVisible(false);
    heroplane2_experience_bar->setVisible(false);
    heroplane2_experience_bar->setStyleSheet(R"(
                                             QProgressBar {
                                                 border: 3px solid #333;          /* 深色边框 */
                                                 border-radius: 4px;              /* 轻微圆角 */
                                                 background-color: #1a1a1a;       /* 深色背景 */
                                                 text-align: center;              /* 进度文字居中 */
                                                 color: #ffffff;                  /* 文字颜色为白色 */
                                                 height: 30px;                    /* 进度条高度 */
                                             }
                                             QProgressBar::chunk {
                                                 background-color: #4CAF50;       /* 绿色进度块 */
                                                 border-radius: 2px;              /* 进度块轻微圆角 */
                                                 margin: 1px;                     /* 进度块与边框的间距 */
                                             }
                                         )");


    level_scene.addWidget(heroplane2_experience_bar);

    //加载武器背景
    //英雄机1的武器背景
    heroplane1_weapon1_background = new QGraphicsPixmapItem();
    heroplane1_weapon1_background->setPixmap(QPixmap(WEAPON_BACKGROUND));
    heroplane1_weapon1_background->setScale(0.12);
    heroplane1_weapon1_background->setPos(VIEW_WIDTH - 100, VIEW_HEIGHT - 200);
    heroplane1_weapon1_background->setVisible(false);
    level_scene.addItem(heroplane1_weapon1_background);

    heroplane1_weapon2_background = new QGraphicsPixmapItem();
    heroplane1_weapon2_background->setPixmap(QPixmap(WEAPON_BACKGROUND));
    heroplane1_weapon2_background->setScale(0.12);
    heroplane1_weapon2_background->setPos(VIEW_WIDTH - 100, VIEW_HEIGHT - 140);
    heroplane1_weapon2_background->setVisible(false);
    level_scene.addItem(heroplane1_weapon2_background);

    heroplane1_weapon3_background = new QGraphicsPixmapItem();
    heroplane1_weapon3_background->setPixmap(QPixmap(WEAPON_BACKGROUND));
    heroplane1_weapon3_background->setScale(0.12);
    heroplane1_weapon3_background->setPos(VIEW_WIDTH - 100, VIEW_HEIGHT - 80);
    heroplane1_weapon3_background->setVisible(false);
    level_scene.addItem(heroplane1_weapon3_background);

    heroplane1_weapon4_background = new QGraphicsPixmapItem();
    heroplane1_weapon4_background->setPixmap(QPixmap(WEAPON_BACKGROUND));
    heroplane1_weapon4_background->setScale(0.12);
    heroplane1_weapon4_background->setPos(VIEW_WIDTH - 160, VIEW_HEIGHT - 80);
    heroplane1_weapon4_background->setVisible(false);
    level_scene.addItem(heroplane1_weapon4_background);

    //英雄机2的武器背景
    heroplane2_weapon1_background = new QGraphicsPixmapItem();
    heroplane2_weapon1_background->setPixmap(QPixmap(WEAPON_BACKGROUND));
    heroplane2_weapon1_background->setScale(0.12);
    heroplane2_weapon1_background->setPos(40, VIEW_HEIGHT - 200);
    heroplane2_weapon1_background->setVisible(false);
    level_scene.addItem(heroplane2_weapon1_background);

    heroplane2_weapon2_background = new QGraphicsPixmapItem();
    heroplane2_weapon2_background->setPixmap(QPixmap(WEAPON_BACKGROUND));
    heroplane2_weapon2_background->setScale(0.12);
    heroplane2_weapon2_background->setPos(40, VIEW_HEIGHT - 140);
    heroplane2_weapon2_background->setVisible(false);
    level_scene.addItem(heroplane2_weapon2_background);

    heroplane2_weapon3_background = new QGraphicsPixmapItem();
    heroplane2_weapon3_background->setPixmap(QPixmap(WEAPON_BACKGROUND));
    heroplane2_weapon3_background->setScale(0.12);
    heroplane2_weapon3_background->setPos(40, VIEW_HEIGHT - 80);
    heroplane2_weapon3_background->setVisible(false);
    level_scene.addItem(heroplane2_weapon3_background);

    heroplane2_weapon4_background = new QGraphicsPixmapItem();
    heroplane2_weapon4_background->setPixmap(QPixmap(WEAPON_BACKGROUND));
    heroplane2_weapon4_background->setScale(0.12);
    heroplane2_weapon4_background->setPos(100, VIEW_HEIGHT - 80);
    heroplane2_weapon4_background->setVisible(false);
    level_scene.addItem(heroplane2_weapon4_background);

    //英雄机的武器等级显示文字
    heroplane1_weapon1_level_text = new QLineEdit();
    heroplane1_weapon1_level_text->setReadOnly(true);
    heroplane1_weapon1_level_text->move(VIEW_WIDTH - 100, VIEW_HEIGHT - 170);
    heroplane1_weapon1_level_text->setText("lv ");
    heroplane1_weapon1_level_text->setVisible(false);
    heroplane1_weapon1_level_text->setStyleSheet(R"(
                                                 QLineEdit:read-only {
                                                     font-family: "Arial Black";  /* 字体家族 */
                                                     font-size: 15px;            /* 字体大小 */
                                                     background-color: transparent;
                                                     border: none;  /* 可选：去掉边框 */
                                                     color: #FFFFFF;   /* 文字颜色 */
                                                 }
                                             )");
    level_scene.addWidget(heroplane1_weapon1_level_text);

    heroplane1_weapon2_level_text = new QLineEdit();
    heroplane1_weapon2_level_text->setReadOnly(true);
    heroplane1_weapon2_level_text->move(VIEW_WIDTH - 100, VIEW_HEIGHT - 110);
    heroplane1_weapon2_level_text->setText("lv ");
    heroplane1_weapon2_level_text->setVisible(false);
    heroplane1_weapon2_level_text->setStyleSheet(R"(
                                                 QLineEdit:read-only {
                                                     font-family: "Arial Black";  /* 字体家族 */
                                                     font-size: 15px;            /* 字体大小 */
                                                     background-color: transparent;
                                                     border: none;  /* 可选：去掉边框 */
                                                     color: #FFFFFF;   /* 文字颜色 */
                                                 }
                                             )");
    level_scene.addWidget(heroplane1_weapon2_level_text);

    heroplane1_weapon3_level_text = new QLineEdit();
    heroplane1_weapon3_level_text->setReadOnly(true);
    heroplane1_weapon3_level_text->move(VIEW_WIDTH - 100, VIEW_HEIGHT - 50);
    heroplane1_weapon3_level_text->setText("lv ");
    heroplane1_weapon3_level_text->setVisible(false);
    heroplane1_weapon3_level_text->setStyleSheet(R"(
                                                 QLineEdit:read-only {
                                                     font-family: "Arial Black";  /* 字体家族 */
                                                     font-size: 15px;            /* 字体大小 */
                                                     background-color: transparent;
                                                     border: none;  /* 可选：去掉边框 */
                                                     color: #FFFFFF;   /* 文字颜色 */
                                                 }
                                             )");
    level_scene.addWidget(heroplane1_weapon3_level_text);

    heroplane2_weapon1_level_text = new QLineEdit();
    heroplane2_weapon1_level_text->setReadOnly(true);
    heroplane2_weapon1_level_text->move(40, VIEW_HEIGHT - 170);
    heroplane2_weapon1_level_text->setText("lv ");
    heroplane2_weapon1_level_text->setVisible(false);
    heroplane2_weapon1_level_text->setStyleSheet(R"(
                                                 QLineEdit:read-only {
                                                     font-family: "Arial Black";  /* 字体家族 */
                                                     font-size: 15px;            /* 字体大小 */
                                                     background-color: transparent;
                                                     border: none;  /* 可选：去掉边框 */
                                                     color: #FFFFFF;   /* 文字颜色 */
                                                 }
                                             )");
    level_scene.addWidget(heroplane2_weapon1_level_text);

    heroplane2_weapon2_level_text = new QLineEdit();
    heroplane2_weapon2_level_text->setReadOnly(true);
    heroplane2_weapon2_level_text->move(40, VIEW_HEIGHT - 110);
    heroplane2_weapon2_level_text->setText("lv ");
    heroplane2_weapon2_level_text->setVisible(false);
    heroplane2_weapon2_level_text->setStyleSheet(R"(
                                                 QLineEdit:read-only {
                                                     font-family: "Arial Black";  /* 字体家族 */
                                                     font-size: 15px;            /* 字体大小 */
                                                     background-color: transparent;
                                                     border: none;  /* 可选：去掉边框 */
                                                     color: #FFFFFF;   /* 文字颜色 */
                                                 }
                                             )");
    level_scene.addWidget(heroplane2_weapon2_level_text);

    heroplane2_weapon3_level_text = new QLineEdit();
    heroplane2_weapon3_level_text->setReadOnly(true);
    heroplane2_weapon3_level_text->move(40, VIEW_HEIGHT - 50);
    heroplane2_weapon3_level_text->setText("lv ");
    heroplane2_weapon3_level_text->setVisible(false);
    heroplane2_weapon3_level_text->setStyleSheet(R"(
                                                 QLineEdit:read-only {
                                                     font-family: "Arial Black";  /* 字体家族 */
                                                     font-size: 15px;            /* 字体大小 */
                                                     background-color: transparent;
                                                     border: none;  /* 可选：去掉边框 */
                                                     color: #FFFFFF;   /* 文字颜色 */
                                                 }
                                             )");
    level_scene.addWidget(heroplane2_weapon3_level_text);


    //加载得分
    score_board = new QLineEdit();
    score_board->setText("得分：0");
    score_board->setReadOnly(true);
    score_board->move(VIEW_WIDTH - 160, 0);
    score_board->setVisible(false);
    level_scene.addWidget(score_board);
    score_board->setStyleSheet(R"(
                                 QLineEdit:read-only {
                                     font-family: "Arial Black";  /* 字体家族 */
                                     font-size: 18px;            /* 字体大小 */
                                 font-weight: bold;
                                     background-color: transparent;
                                     border: none;  /* 可选：去掉边框 */
                                     color: #FF0B0B;   /* 文字颜色 */
                                 }
                             )");


    // 英雄机1的炸弹数量
    heroplane1_bomb_count = new QLineEdit();
    heroplane1_bomb_count->setText("炸弹: 3");
    heroplane1_bomb_count->setReadOnly(true);
    heroplane1_bomb_count->move(VIEW_WIDTH - 120, VIEW_HEIGHT - 40);
    heroplane1_bomb_count->setFixedSize(100, 30);
    heroplane1_bomb_count->setStyleSheet(R"(
                                         QLineEdit:read-only {
                                         font-family: "Arial Black";
                                         font-size: 16px;
                                         font-weight: bold;
                                         background-color: transparent;
                                         border: none;
                                         color: #FFD700;   /* 金色 */
                                         }
                                         )");
    heroplane1_bomb_count->setVisible(false);
    level_scene.addWidget(heroplane1_bomb_count);

    // 英雄机2的炸弹数量
    heroplane2_bomb_count = new QLineEdit();
    heroplane2_bomb_count->setText("炸弹: 3");
    heroplane2_bomb_count->setReadOnly(true);
    heroplane2_bomb_count->move(0, VIEW_HEIGHT - 40);
    heroplane2_bomb_count->setFixedSize(100, 30);
    heroplane2_bomb_count->setStyleSheet(R"(
                                         QLineEdit:read-only {
                                         font-family: "Arial Black";
                                         font-size: 16px;
                                         font-weight: bold;
                                         background-color: transparent;
                                         border: none;
                                         color: #FFD700;   /* 金色 */
                                         }
                                         )");
    heroplane2_bomb_count->setVisible(false);
    level_scene.addWidget(heroplane2_bomb_count);

    //炸弹图片
    bomb_picture = new QGraphicsPixmapItem();
    bomb_picture->setPixmap(QPixmap(BOMB_PICTURE));
    bomb_picture->setVisible(false);
    bomb_picture->setPos(100, 250);
    level_scene.addItem(bomb_picture);

        // 添加Boss血条
            boss_healthBar = new QProgressBar();
            boss_healthBar->setFixedSize(400, 30);
            boss_healthBar->move(VIEW_WIDTH/2 - 200, 50);
            boss_healthBar->setValue(100);
            boss_healthBar->setStyleSheet(R"(
                QProgressBar {
                    border: 3px solid #FF0000;
                    border-radius: 8px;
                    background-color: #1a1a1a;
                    text-align: center;
                    color: #FFFFFF;
                    font-family: "Arial Black";
                    font-size: 16px;
                    font-weight: bold;
                }
                QProgressBar::chunk {
                    background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                                               stop:0 #FF0000,
                                               stop:0.5 #FF6600,
                                               stop:1 #FFAA00);
                    border-radius: 5px;
                }
            )");
            boss_healthBar->setVisible(false);
            level_scene.addWidget(boss_healthBar);

            // Boss名称显示
            boss_name_display = new QLineEdit();
            boss_name_display->setReadOnly(true);
            boss_name_display->move(VIEW_WIDTH/2 - 100, 20);
            boss_name_display->setFixedSize(200, 30);
            boss_name_display->setStyleSheet(R"(
                QLineEdit:read-only {
                    font-family: "Arial Black";
                    font-size: 18px;
                    font-weight: bold;
                    background-color: transparent;
                    border: none;
                    color: #FF0000;
                    text-align: center;
                }
            )");
            boss_name_display->setVisible(false);
            level_scene.addWidget(boss_name_display);

            // 关卡进度文字显示
            level_progress_text = new QLineEdit();
            level_progress_text->setReadOnly(true);
            level_progress_text->move(10, 10);
            level_progress_text->setFixedSize(200, 30);
            level_progress_text->setStyleSheet(R"(
                QLineEdit:read-only {
                    font-family: "Arial Black";
                    font-size: 16px;
                    font-weight: bold;
                    background-color: transparent;
                    border: 2px solid #00FF00;
                    color: #00FF00;
                    padding: 5px;
                }
            )");
            level_progress_text->setVisible(false);
            level_scene.addWidget(level_progress_text);

            // Boss警告计时器
            boss_warning_timer = new QTimer();
            boss_warning_timer->setSingleShot(true);



}

void Widget::load_heroplane1_weapon1_background(HeroWeapon *heroweapon)
{
    heroweapon->setScale(0.4);
    heroweapon->setPos(VIEW_WIDTH - 101, VIEW_HEIGHT - 200);
    level_scene.addItem(heroweapon);
}

void Widget::load_heroplane1_weapon2_background(HeroWeapon *heroweapon)
{
    heroweapon->setScale(0.4);
    heroweapon->setPos(VIEW_WIDTH - 101, VIEW_HEIGHT - 140);
    level_scene.addItem(heroweapon);
}

void Widget::load_heroplane1_weapon3_background(HeroWeapon *heroweapon)
{
    heroweapon->setScale(0.4);
    heroweapon->setPos(VIEW_WIDTH - 101, VIEW_HEIGHT - 80);
    level_scene.addItem(heroweapon);
}

void Widget::load_heroplane2_weapon1_background(HeroWeapon *heroweapon)
{
    heroweapon->setScale(0.4);
    heroweapon->setPos(40, VIEW_HEIGHT - 200);
    level_scene.addItem(heroweapon);
}

void Widget::load_heroplane2_weapon2_background(HeroWeapon *heroweapon)
{
    heroweapon->setScale(0.4);
    heroweapon->setPos(40, VIEW_HEIGHT - 140);
    level_scene.addItem(heroweapon);
}

void Widget::load_heroplane2_weapon3_background(HeroWeapon *heroweapon)
{
    heroweapon->setScale(0.4);
    heroweapon->setPos(40, VIEW_HEIGHT - 80);
    level_scene.addItem(heroweapon);
}

void Widget::refresh_timer()
{
    game_timer->start(GAME_PERIOD);
}

//转到菜单页面
void Widget::turn_to_menu()
{
    game_level = 0;
    main_view.setScene(&main_scene2);
}
void Widget::turn_to_level1()
{
    game_level = 1;
    main_view.setScene(&level_scene);
    refresh_timer();
    // 重置保存状态（开始新游戏时）
    saved_heroplane1_state.reset();
    use_saved_state = false;

    // 初始化关卡进度
    enemies_killed_in_level = 0;
    required_enemies_for_level = LEVEL_1_ENEMY_COUNT;
    boss_spawned = false;
    boss_warning_shown = false;
    current_boss = nullptr;

    // 显示UI元素
    level_1_background1->setVisible(true);
    level_1_background2->setVisible(true);
    heroplane1_healthBar->setVisible(true);
    heroplane1_health_value->setVisible(true);
    heroplane1_experience_bar->setVisible(true);
    score_board->setVisible(true);
    level_progressBar->setVisible(true);
    level_progress_text->setVisible(true);
    heroplane1_weapon1_background->setVisible(true);
    heroplane1_weapon2_background->setVisible(true);
    heroplane1_weapon3_background->setVisible(true);
    heroplane1_weapon4_background->setVisible(true);
    heroplane1_weapon1_level_text->setVisible(true);
    heroplane1_weapon2_level_text->setVisible(true);
    heroplane1_weapon3_level_text->setVisible(true);
    heroplane1_bomb_count->setVisible(true);

    load_level_heroplane1(1);
    connect(game_timer, QTimer::timeout, this, level_1_update);
}
//转到第二关
void Widget::turn_to_level2()
{
    game_level = 2;
    main_view.setScene(&level_scene);
    refresh_timer();

    // 初始化关卡进度
    enemies_killed_in_level = 0;
    required_enemies_for_level = LEVEL_2_ENEMY_COUNT;
    boss_spawned = false;
    boss_warning_shown = false;
    current_boss = nullptr;

    // 显示UI元素
    level_2_background1->setVisible(true);
    level_2_background2->setVisible(true);
    heroplane1_healthBar->setVisible(true);
    heroplane1_health_value->setVisible(true);
    heroplane1_experience_bar->setVisible(true);
    score_board->setVisible(true);
    level_progressBar->setVisible(true);
    level_progress_text->setVisible(true);
    heroplane1_weapon1_background->setVisible(true);
    heroplane1_weapon2_background->setVisible(true);
    heroplane1_weapon3_background->setVisible(true);
    heroplane1_weapon4_background->setVisible(true);
    heroplane1_weapon1_level_text->setVisible(true);
    heroplane1_weapon2_level_text->setVisible(true);
    heroplane1_weapon3_level_text->setVisible(true);
    heroplane1_bomb_count->setVisible(true);

    load_level_heroplane1(1);
    connect(game_timer, QTimer::timeout, this, level_2_update);
}


void Widget::turn_to_cooperation()
{
    game_level = 7;
    //将视图对准关卡场景
    main_view.setScene(&level_scene);
    //刷新计时器
    refresh_timer();
    //将需要的组件可视化
    level_5_background1->setVisible(true);//用第5关的场景
    level_5_background2->setVisible(true);
    heroplane1_healthBar->setVisible(true);
    heroplane1_health_value->setVisible(true);
    heroplane1_experience_bar->setVisible(true);
    heroplane2_healthBar->setVisible(true);
    heroplane2_health_value->setVisible(true);
    heroplane2_experience_bar->setVisible(true);
    score_board->setVisible(true);
    level_progressBar->setVisible(true);
    heroplane1_weapon1_background->setVisible(true);
    heroplane1_weapon2_background->setVisible(true);
    heroplane1_weapon3_background->setVisible(true);
    heroplane1_weapon4_background->setVisible(true);
    heroplane2_weapon1_background->setVisible(true);
    heroplane2_weapon2_background->setVisible(true);
    heroplane2_weapon3_background->setVisible(true);
    heroplane2_weapon4_background->setVisible(true);
    heroplane1_weapon1_level_text->setVisible(true);
    heroplane1_weapon2_level_text->setVisible(true);
    heroplane1_weapon3_level_text->setVisible(true);
    heroplane2_weapon1_level_text->setVisible(true);
    heroplane2_weapon2_level_text->setVisible(true);
    heroplane2_weapon3_level_text->setVisible(true);
    heroplane1_bomb_count->setVisible(true);
    heroplane2_bomb_count->setVisible(true);


    //加载英雄机
    load_level_heroplane1(1);
    load_level_heroplane2(2);

    //设置计时器与第一关场景之间的信号槽
    connect(game_timer, QTimer::timeout, this, cooperation_update);
}

void Widget::load_level_heroplane1(int kind)
{
    //英雄机初始化
    heroplane1 = new HeroPlane(heroplane1_invincible_timer);
    heroplane1->init(400.0, 1000.0, kind);
    level_scene.addItem(heroplane1);

    // 如果有保存的状态，则恢复状态
    if (use_saved_state) {
        restore_heroplane_state();
    } else {
        // 正常初始化武器1
        init_heroplane1_weapon1();
    }

    //为英雄机1的护盾图片设置计时器
    connect(heroplane1_invincible_timer, QTimer::timeout, this, [=](){
        heroplane1->shield->setVisible(false);
    });
}

void Widget::load_level_heroplane2(int kind)
{
    //英雄机初始化
    heroplane2 = new HeroPlane(heroplane2_invincible_timer);//一定要记得new
    heroplane2->init(200.0, 1000.0, kind);//初始化英雄机
    level_scene.addItem(heroplane2);//在场景中加载英雄机

    //为英雄机2配置初始武器
    heroplane2->weapon1 = new HeroWeapon();
    heroplane2->weapon1->init(kind);//初始化武器
    heroplane2->weapon1->setZValue(-1);
    load_heroplane2_weapon1_background(heroplane2->weapon1);//加载武器图标
    //为武器1设置计时器
    heroplane2_weapon1_timer->start(heroplane2->weapon1->interval);
    connect(heroplane2_weapon1_timer, QTimer::timeout, this, [=](){
        heroplane2->weapon1->is_ready = true;
    });
    //为英雄机2的护盾设置计时器
    connect(heroplane2_invincible_timer, QTimer::timeout, this, [=](){
        heroplane2->shield->setVisible(false);
    });
}
void Widget::restore_heroplane_state()
{
    if (!heroplane1) return;

    // 恢复基础属性
    heroplane1->level = saved_heroplane1_state.level;
    heroplane1->experience = saved_heroplane1_state.experience;
    heroplane1->next_level_experience = saved_heroplane1_state.next_level_experience;
    heroplane1->rate_sum = saved_heroplane1_state.rate_sum;
    heroplane1->max_health = saved_heroplane1_state.max_health;
    heroplane1->health = saved_heroplane1_state.health;
    heroplane1->damage = saved_heroplane1_state.damage;
    heroplane1->bomb_count = saved_heroplane1_state.bomb_count;
    // 恢复分数
    score = saved_heroplane1_state.score;
    score_board->setText("得分：" + QString::number(score));

    // 恢复武器1
    if (saved_heroplane1_state.weapon1_state.exists) {
        heroplane1->weapon1 = new HeroWeapon();
        restore_weapon(heroplane1->weapon1, saved_heroplane1_state.weapon1_state);
        load_heroplane1_weapon1_background(heroplane1->weapon1);
        setup_weapon1_timer();
    }

    // 恢复武器2
    if (saved_heroplane1_state.weapon2_state.exists) {
        heroplane1->weapon2 = new HeroWeapon();
        restore_weapon(heroplane1->weapon2, saved_heroplane1_state.weapon2_state);
        load_heroplane1_weapon2_background(heroplane1->weapon2);
        setup_weapon2_timer();
    }

    // 恢复武器3
    if (saved_heroplane1_state.weapon3_state.exists) {
        heroplane1->weapon3 = new HeroWeapon();
        restore_weapon(heroplane1->weapon3, saved_heroplane1_state.weapon3_state);
        load_heroplane1_weapon3_background(heroplane1->weapon3);
        setup_weapon3_timer();
    }
}
// 添加初始化武器1的辅助函数
void Widget::init_heroplane1_weapon1()
{
    heroplane1->weapon1 = new HeroWeapon();
    heroplane1->weapon1->init(1); // 默认武器1
    load_heroplane1_weapon1_background(heroplane1->weapon1);
    heroplane1->weapon1->setZValue(-1);
    setup_weapon1_timer();
}

// 添加设置武器计时器的辅助函数
void Widget::setup_weapon1_timer()
{
    heroplane1_weapon1_timer->start(heroplane1->weapon1->interval);
    connect(heroplane1_weapon1_timer, QTimer::timeout, this, [=](){
        heroplane1->weapon1->is_ready = true;
    });
}

void Widget::setup_weapon2_timer()
{
    heroplane1_weapon2_timer->start(heroplane1->weapon2->interval);
    connect(heroplane1_weapon2_timer, QTimer::timeout, this, [=](){
        heroplane1->weapon2->is_ready = true;
    });
}

void Widget::setup_weapon3_timer()
{
    heroplane1_weapon3_timer->start(heroplane1->weapon3->interval);
    connect(heroplane1_weapon3_timer, QTimer::timeout, this, [=](){
        heroplane1->weapon3->is_ready = true;
    });
}
void Widget::restore_weapon(HeroWeapon* weapon, const HeroPlaneState::WeaponState& weapon_state)
{
    weapon->weapon_kind = weapon_state.weapon_kind;
    weapon->weapon_level = weapon_state.weapon_level;
    weapon->damage = weapon_state.damage;
    weapon->interval = weapon_state.interval;
    weapon->speed = weapon_state.speed;
    weapon->is_ready = true;
    weapon->setZValue(-1);

    // 根据武器种类设置图片
    switch(weapon_state.weapon_kind) {
        case 1:
            weapon->setPixmap(QPixmap(WEAPON_PICTURE1));
            break;
        case 2:
            weapon->setPixmap(QPixmap(WEAPON_PICTURE2));
            break;
        case 3:
            weapon->setPixmap(QPixmap(WEAPON_PICTURE3));
            break;
        case 4:
            weapon->setPixmap(QPixmap(WEAPON_PICTURE4));
            break;
    }
}

void Widget::delete_level()
{
    delete_level_heroplane1();
    delete_level_heroplane2();
    delete_level_pools();
    delete_level_timers();

    //难度系数重置
    EnemyPlane::difficulty_degree = 1;

    // 清理Boss相关UI和状态
    boss_healthBar->setVisible(false);
    boss_name_display->setVisible(false);
    level_progress_text->setVisible(false);

    // 重置Boss相关状态变量
    boss_spawned = false;
    boss_warning_shown = false;
    current_boss = nullptr;
    enemies_killed_in_level = 0;
    required_enemies_for_level = 0;

    // 清理可能存在的Boss警告图片
    if (boss_warning_image) {
        level_scene.removeItem(boss_warning_image);
        delete boss_warning_image;
        boss_warning_image = nullptr;
    }

    //将结束界面去掉
    end_picture->setVisible(false);
    pause_background->setVisible(false);
    game_status = 0;//改变游戏状态
    score = 0;//分数清零
    score_board->setText("得分: 0");
    level_progressBar->setVisible(false); // 修改这里，应该是setVisible而不是setValue
    EnemyPlane::difficulty_degree = 1.0;//重置难度系数

    // 隐藏通用UI元素
    heroplane1_healthBar->setVisible(false);
    heroplane1_health_value->setVisible(false);
    heroplane1_experience_bar->setVisible(false);
    score_board->setVisible(false);
    heroplane1_weapon1_background->setVisible(false);
    heroplane1_weapon2_background->setVisible(false);
    heroplane1_weapon3_background->setVisible(false);
    heroplane1_weapon4_background->setVisible(false);
    heroplane1_weapon1_level_text->setVisible(false);
    heroplane1_weapon2_level_text->setVisible(false);
    heroplane1_weapon3_level_text->setVisible(false);
    heroplane1_bomb_count->setVisible(false);

    // 隐藏关卡背景
    level_1_background1->setVisible(false);
    level_1_background2->setVisible(false);
    level_2_background1->setVisible(false);
    level_2_background2->setVisible(false);

    //根据不同关卡额外析构一些地图元素
    if (game_level == 7){//双人无尽模式的额外析构
        heroplane2_healthBar->setVisible(false);
        heroplane2_health_value->setVisible(false);
        heroplane2_experience_bar->setVisible(false);
        heroplane2_weapon1_background->setVisible(false);
        heroplane2_weapon2_background->setVisible(false);
        heroplane2_weapon3_background->setVisible(false);
        heroplane2_weapon4_background->setVisible(false);
        level_5_background1->setVisible(false);
        level_5_background2->setVisible(false);
        heroplane2_weapon1_level_text->setVisible(false);
        heroplane2_weapon2_level_text->setVisible(false);
        heroplane2_weapon3_level_text->setVisible(false);
        heroplane2_bomb_count->setVisible(false);
    }
}

void Widget::delete_level_heroplane1()
{
    //析构英雄机1
    if (heroplane1){
        level_scene.removeItem(heroplane1);
        if(heroplane1->weapon1){
            level_scene.removeItem(heroplane1->weapon1);
        }
        if(heroplane1->weapon2){
            level_scene.removeItem(heroplane1->weapon2);
        }
        if(heroplane1->weapon3){
            level_scene.removeItem(heroplane1->weapon3);
        }

        delete heroplane1;
    }
}

void Widget::delete_level_heroplane2()
{
    //析构英雄机2
    if (heroplane2){
        level_scene.removeItem(heroplane2);
        if (heroplane2->weapon1){
            level_scene.removeItem(heroplane2->weapon1);
        }
        if (heroplane2->weapon2){
            level_scene.removeItem(heroplane2->weapon2);
        }
        if (heroplane2->weapon3){
            level_scene.removeItem(heroplane2->weapon3);
        }

        delete heroplane2;
    }
}

void Widget::delete_level_pools()
{
    for (EnemyBullet* enemybullet : enemybullet_pool){
        enemybullet->destroy();
    }
    enemybullet_queue.clear();
    for (EnemyPlane* enemyplane : enemyplane_pool){
        enemyplane->destroy();
    }
    herobullet_queue.clear();
    for (HeroBullet* herobullet : herobullet_pool){
        herobullet->destroy();
    }
    enemybullet_queue.clear();
}

void Widget::delete_level_timers()
{
    if (game_timer){
        game_timer->disconnect();
        game_timer->stop();
    }
    if (heroplane1_weapon1_timer){
        heroplane1_weapon1_timer->disconnect();
        heroplane1_weapon1_timer->stop();
    }
    if (heroplane1_weapon2_timer){
        heroplane1_weapon2_timer->disconnect();
        heroplane1_weapon2_timer->stop();
    }
    if (heroplane1_weapon3_timer){
        heroplane1_weapon3_timer->disconnect();
        heroplane1_weapon3_timer->stop();
    }
    if (heroplane2_weapon1_timer){
        heroplane2_weapon1_timer->disconnect();
        heroplane2_weapon2_timer->stop();
    }
    if (heroplane2_weapon2_timer){
        heroplane2_weapon2_timer->disconnect();
        heroplane2_weapon2_timer->stop();
    }
    if (heroplane2_weapon3_timer){
        heroplane2_weapon3_timer->disconnect();
        heroplane2_weapon3_timer->stop();
    }
    if (heroplane1_invincible_timer){
        heroplane1_invincible_timer->disconnect();
        heroplane1_invincible_timer->stop();
    }
    if (heroplane2_invincible_timer){
        heroplane2_invincible_timer->disconnect();
        heroplane2_invincible_timer->stop();
    }
    // 添加Boss警告计时器的处理
    if (boss_warning_timer){
        boss_warning_timer->disconnect();
        boss_warning_timer->stop();
    }
}

//键盘控制英雄机移动
void Widget::heroplane1_move1(HeroPlane* heroplane)
{
    int x = heroplane->pos().x();
    int y = heroplane->pos().y();
    int delta_x = 0, delta_y = 0;
    int step = 0;
    for (int keyCode : keylist1){
        switch(keyCode){
        case Qt::Key_W:
            delta_y -= heroplane->speed;
            step++;
            break;
        case Qt::Key_D:
            delta_x += heroplane->speed;
            step++;
            break;
        case Qt::Key_A:
            delta_x -= heroplane->speed;
            step++;
            break;
        case Qt::Key_S:
            delta_y += heroplane->speed;
            step++;
            break;
        }
    }
    if (step == 1 || step == 3){
        x += delta_x;
        y += delta_y;
    }
    else if (step == 2){
        x += delta_x * 0.707;//乘以根号二分之一，保证斜向移动时速度和垂直移动时一致
        y += delta_y * 0.707;
    }
    heroplane->move_to(x, y);
}

void Widget::heroplane2_move1(HeroPlane *heroplane)
{
    int x = heroplane->pos().x();
    int y = heroplane->pos().y();
    int delta_x = 0, delta_y = 0;
    int step = 0;
    for (int keyCode : keylist2){
        switch(keyCode){
        case Qt::Key_Up:
            delta_y -= heroplane->speed;
            step++;
            qDebug() << "up";
            break;
        case Qt::Key_Right:
            delta_x += heroplane->speed;
            step++;
            break;
        case Qt::Key_Left:
            delta_x -= heroplane->speed;
            step++;
            break;
        case Qt::Key_Down:
            delta_y += heroplane->speed;
            step++;
            break;
        }
    }
    if (step == 1 || step == 3){
        x += delta_x;
        y += delta_y;
    }
    else if (step == 2){
        x += delta_x * 0.707;//乘以根号二分之一，保证斜向移动时速度和垂直移动时一致
        y += delta_y * 0.707;
    }
    heroplane->move_to(x, y);
}

//实现鼠标控制飞机移动
void Widget::heroplane_move0(HeroPlane* heroplane1)
{
    double x = heroplane1->pos().x();
    double y = heroplane1->pos().y();
    QPoint point = QCursor::pos();
    QPoint local_point = mapFromGlobal(point);
    double px = local_point.x(), py = local_point.y();
    double rect_x = heroplane1->pixmap().width() / 2, rect_y = heroplane1->pixmap().height() / 2;//飞机在x轴和y轴上的移动比率（模拟按直线接近鼠标位置）
    double cx = x + rect_x, cy = y + rect_y;//飞机中心坐标
    double rate_x = abs(cx - px) / double(abs(cx - px) + abs(cy - py));
    double rate_y = abs(cy - py) / double(abs(cx - px) + abs(cy - py));

    if ( cx > px + 5 && cx >= 0){
        x -= heroplane1->speed * rate_x * 1.2;//不知道为什么鼠标控制移动会比较慢，加个1.2系数修正一下
    }
    else if (cx < px - 5 && cx <= VIEW_WIDTH){
        x += heroplane1->speed * rate_x * 1.2;
    }
    if (cy > py + 5 && cy >= 0){
        y -= heroplane1->speed * rate_y * 1.2;
    }
    else if (cy < py - 5 && cy <= VIEW_HEIGHT){
        y += heroplane1->speed * rate_y * 1.2;
    }
    heroplane1->move_to(x, y);
}

//第一关更新函数
void Widget::level_1_update()
{
    // 场景移动
    level_1_background1->setY(level_1_background1->y() + 1);
    if (level_1_background1->y() >= 1229){
        level_1_background1->setY(0);
    }
    level_1_background2->setY(level_1_background2->y() + 1);
    if (level_1_background2->y() >= 0){
        level_1_background2->setY(-1229);
    }

    // 检查是否应该生成Boss
    check_boss_spawn();

    // 如果Boss还没有生成，继续生成普通敌机
    if (!boss_spawned) {
        static int count = 0;
        static int period = 2000;//生成敌机的间隔
        count += GAME_PERIOD;
        if (count >= period){
            int kind = (rand() % 4) + 1;
            int x = rand()%668, y = -100;
            get_enemyplane(x, y, kind);
            count = 0;
            if (period >= 500)period *= 0.95;//生成敌机越来越快
            EnemyPlane::difficulty_degree *= 1.02;//难度系数提升
        }
    }

    // 英雄机位置更新
    if (move_mode == 1){
        heroplane1_move1(heroplane1);
    }
    else{
        heroplane_move0(heroplane1);
    }

    // 更新关卡进度
    update_level_progress();

    // 检查关卡是否完成
    check_level_complete();

    // 游戏通用更新函数
    game_update();
}
//第二关更新函数
void Widget::level_2_update()
{
    // 场景移动
    level_2_background1->setY(level_2_background1->y() + 1);
    if (level_2_background1->y() >= 1229){
        level_2_background1->setY(0);
    }
    level_2_background2->setY(level_2_background2->y() + 1);
    if (level_2_background2->y() >= 0){
        level_2_background2->setY(-1229);
    }

    // 检查是否应该生成Boss
    check_boss_spawn();

    // 如果Boss还没有生成，继续生成普通敌机
    if (!boss_spawned) {
        static int count = 0;
        count += GAME_PERIOD;
        if (count == 1500){ // 第二关敌机生成更频繁
            int kind = (rand() % 4) + 1;
            int x = rand()%668, y = -100;
            get_enemyplane(x, y, kind);
            count = 0;
        }
    }

    // 英雄机位置更新
    if (move_mode == 1){
        heroplane1_move1(heroplane1);
    }
    else{
        heroplane_move0(heroplane1);
    }

    // 更新关卡进度
    update_level_progress();

    // 检查关卡是否完成
    check_level_complete();

    // 游戏通用更新函数
    game_update();
}
void Widget::update_level_progress()
{
    // 更新进度条
    int progress = (enemies_killed_in_level * 100) / required_enemies_for_level;
    if (progress > 100) progress = 100;
    level_progressBar->setValue(progress);

    // 更新进度文字
    if (boss_spawned && current_boss) {
        level_progress_text->setText("Boss战斗中！");
    } else {
        level_progress_text->setText(QString("第%1关 - 进度: %2/%3")
                                   .arg(game_level)
                                   .arg(enemies_killed_in_level)
                                   .arg(required_enemies_for_level));
    }
}

//检查是否应该生成Boss
void Widget::check_boss_spawn()
{
    if (boss_spawned) return; // Boss已经生成

    if (enemies_killed_in_level >= required_enemies_for_level) {
        // 清除剩余的普通敌机
        for (EnemyPlane* enemyplane : enemyplane_pool) {
            if (enemyplane->status == 2 && !enemyplane->is_boss()) {
                enemyplane->destroy();
            }
        }

        if (!boss_warning_shown) {
            show_boss_warning();
        }
    }
}

//显示Boss警告
void Widget::show_boss_warning()
{
    boss_warning_shown = true;

    // 创建Boss警告文字提示，而不是使用暂停图片
    QGraphicsTextItem* warning_text = new QGraphicsTextItem("BOSS WARNING!");
    warning_text->setFont(QFont("Arial Black", 36, QFont::Bold));
    warning_text->setDefaultTextColor(Qt::red);

    // 获取文本的边界框来正确居中
    QRectF textRect = warning_text->boundingRect();
    double centerX = VIEW_WIDTH / 2 - textRect.width() / 2;
    double centerY = VIEW_HEIGHT / 2 - textRect.height() / 2;
    warning_text->setPos(centerX, centerY);

    warning_text->setZValue(95);
    level_scene.addItem(warning_text);

    // 添加闪烁效果
    QTimer* blink_timer = new QTimer();
    bool visible = true;
    connect(blink_timer, &QTimer::timeout, [=]() mutable {
        warning_text->setVisible(visible);
        visible = !visible;
    });
    blink_timer->start(200); // 每200ms闪烁一次

    // 3秒后隐藏警告并生成Boss
    connect(boss_warning_timer, &QTimer::timeout, this, [=]() {
        blink_timer->stop();
        delete blink_timer;
        level_scene.removeItem(warning_text);
        delete warning_text;

        // 生成对应关卡的Boss
        if (game_level == 1) {
            spawn_boss(5); // Boss1
        } else if (game_level == 2) {
            spawn_boss(6); // Boss2
        }
    });

    boss_warning_timer->start(BOSS_WARNING_TIME);
}
//生成Boss
void Widget::spawn_boss(int boss_kind)
{
    boss_spawned = true;

    // 从屏幕上方生成Boss
    current_boss = get_enemyplane(VIEW_WIDTH / 2 - 50, -200, boss_kind);

    // 显示Boss血条和名称
    boss_healthBar->setVisible(true);
    boss_name_display->setVisible(true);

    if (boss_kind == 5) {
        boss_name_display->setText("终极守护者");
    } else if (boss_kind == 6) {
        boss_name_display->setText("毁灭战舰");
    }

    // 更新Boss血条
    update_boss_health_bar();
}

//更新Boss血条
void Widget::update_boss_health_bar()
{
    if (current_boss && current_boss->status == 2) {
        int health_percentage = (current_boss->health * 100) / current_boss->max_health;
        if (health_percentage < 0) health_percentage = 0;
        boss_healthBar->setValue(health_percentage);

        // 显示Boss阶段信息
        QString phase_text = QString("阶段 %1").arg(current_boss->boss_phase);
        boss_healthBar->setFormat(QString("%1 - %2%").arg(phase_text).arg(health_percentage));
    }
}

//检查关卡是否完成
void Widget::check_level_complete()
{
    if (boss_spawned && current_boss && current_boss->status == 0) {
        // Boss被击败，关卡完成
        boss_healthBar->setVisible(false);
        boss_name_display->setVisible(false);

        // 可以在这里添加关卡完成的特效和奖励
        score += 10000; // 关卡完成奖励
        score_board->setText("得分：" + QString::number(score));

        // 如果是第一关，保存英雄机状态并进入第二关
        if (game_level == 1) {
            // 保存英雄机1的状态
            save_heroplane_state();

            // 延迟3秒后进入第二关
            QTimer::singleShot(3000, this, [=]() {
                delete_level();
                turn_to_level2();
            });
        } else if (game_level == 2) {
            // 游戏胜利
            game_status = 2;
            saveScore();
        }
    }
}
void Widget::save_heroplane_state()
{
    if (!heroplane1) return;

    // 保存基础属性
    saved_heroplane1_state.level = heroplane1->level;
    saved_heroplane1_state.experience = heroplane1->experience;
    saved_heroplane1_state.next_level_experience = heroplane1->next_level_experience;
    saved_heroplane1_state.rate_sum = heroplane1->rate_sum;
    saved_heroplane1_state.max_health = heroplane1->max_health;
    saved_heroplane1_state.health = heroplane1->max_health; // 关卡间回满血
    saved_heroplane1_state.damage = heroplane1->damage;
    saved_heroplane1_state.bomb_count = heroplane1->bomb_count + 1; // 过关奖励一个炸弹
    saved_heroplane1_state.score = score;

    // 保存武器1状态
    if (heroplane1->weapon1) {
        saved_heroplane1_state.weapon1_state.exists = true;
        saved_heroplane1_state.weapon1_state.weapon_kind = heroplane1->weapon1->weapon_kind;
        saved_heroplane1_state.weapon1_state.weapon_level = heroplane1->weapon1->weapon_level;
        saved_heroplane1_state.weapon1_state.damage = heroplane1->weapon1->damage;
        saved_heroplane1_state.weapon1_state.interval = heroplane1->weapon1->interval;
        saved_heroplane1_state.weapon1_state.speed = heroplane1->weapon1->speed;
    }

    // 保存武器2状态
    if (heroplane1->weapon2) {
        saved_heroplane1_state.weapon2_state.exists = true;
        saved_heroplane1_state.weapon2_state.weapon_kind = heroplane1->weapon2->weapon_kind;
        saved_heroplane1_state.weapon2_state.weapon_level = heroplane1->weapon2->weapon_level;
        saved_heroplane1_state.weapon2_state.damage = heroplane1->weapon2->damage;
        saved_heroplane1_state.weapon2_state.interval = heroplane1->weapon2->interval;
        saved_heroplane1_state.weapon2_state.speed = heroplane1->weapon2->speed;
    }

    // 保存武器3状态
    if (heroplane1->weapon3) {
        saved_heroplane1_state.weapon3_state.exists = true;
        saved_heroplane1_state.weapon3_state.weapon_kind = heroplane1->weapon3->weapon_kind;
        saved_heroplane1_state.weapon3_state.weapon_level = heroplane1->weapon3->weapon_level;
        saved_heroplane1_state.weapon3_state.damage = heroplane1->weapon3->damage;
        saved_heroplane1_state.weapon3_state.interval = heroplane1->weapon3->interval;
        saved_heroplane1_state.weapon3_state.speed = heroplane1->weapon3->speed;
    }

    use_saved_state = true; // 标记下次加载时使用保存的状态
}


void Widget::cooperation_update()
{
    //场景移动
    level_5_background1->setY(level_5_background1->y() + 1);
    if (level_5_background1->y() >= 1229){
        level_5_background1->setY(0);
    }
    level_5_background2->setY(level_5_background2->y() + 1);
    if (level_5_background2->y() >= 0){
        level_5_background2->setY(-1229);
    }

    //第一种敌机每2秒随机在屏幕上方生成
    static int count = 0;//单位:ms
    count += GAME_PERIOD;
    if (count == 2000){
        int kind = (rand() % 4) + 1;
        int x = rand()%668, y = -100;
        get_enemyplane(x, y, kind);
        count = 0;
    }
    //英雄机位置更新
    move_mode = 1;
    heroplane1_move1(heroplane1);
    heroplane_move0(heroplane2);


    //常规更新
    game_update();

}

EnemyPlane *Widget::get_enemyplane(int x, int y, int kind)
{
    EnemyPlane* enemyplane;
    if (enemyplane_queue.empty()){
        QTimer *timer = new QTimer();//新建一个计时器
        enemyplane = new EnemyPlane(timer);
        //连接信号槽（控制敌机自动开火）
        connect(timer, QTimer::timeout, this, [=](){
            enemyplane_shoot(enemyplane);
        });
        enemyplane_pool.append(enemyplane);
        level_scene.addItem(enemyplane);//加入背景
    }
    else{
        enemyplane = enemyplane_queue.dequeue();
    }
    enemyplane->status = 2;
    enemyplane->init(x, y, kind);
    return enemyplane;
}

EnemyBullet *Widget::get_enemybullet(int x, int y, int kind)
{
    EnemyBullet* enemybullet;
    if (enemybullet_queue.empty()){
        enemybullet = new EnemyBullet();
        enemybullet_pool.append(enemybullet);
        level_scene.addItem(enemybullet);//加入背景
    }
    else {
        enemybullet = enemybullet_queue.dequeue();
    }
    enemybullet->status = 2;
    enemybullet->init(x, y, kind);
    return enemybullet;
}

HeroBullet *Widget::get_herobullet(int x, int y, int kind)
{
    HeroBullet* herobullet;
    if (herobullet_queue.empty()){
        herobullet = new HeroBullet();
        herobullet_pool.append(herobullet);
        level_scene.addItem(herobullet);//加入背景
    }
    else{
        herobullet = herobullet_queue.dequeue();
    }
    herobullet->status = 2;
    herobullet->init(x, y, kind);
    return herobullet;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space: // 空格键 - 英雄机1释放炸弹
        if (heroplane1 && heroplane1->status == 2) {
            heroplane1_release_bomb();
        }
        break;
    case Qt::Key_Return: // 回车键 - 英雄机2释放炸弹
    case Qt::Key_Enter:
        if (heroplane2 && heroplane2->status == 2) {
            heroplane2_release_bomb();
        }
        break;

    case Qt::Key_W:
    case Qt::Key_D:
    case Qt::Key_A:
    case Qt::Key_S:
        if (move_mode == 0)return;
        keylist1.append(event->key());
        break;
    case Qt::Key_P: //按下P键暂停
        game_pause();
        break;
    case Qt::Key_J://按下J键英雄机1武器1连续发射
        heroplane1_weapon1_continuous_firing = true;
        break;
    case Qt::Key_K://按下J键英雄机1武器2连续发射
        heroplane1_weapon2_continuous_firing = true;
        break;
    case Qt::Key_L://按下J键英雄机1武器3连续发射
        heroplane1_weapon3_continuous_firing = true;
        break;
    case Qt::Key_1://按下1键英雄机2武器1连续发射
        heroplane2_weapon1_continuous_firing = true;
        break;
    case Qt::Key_2://按下2键英雄机2武器2连续发射
        heroplane2_weapon2_continuous_firing = true;
        break;
    case Qt::Key_3://按下3键英雄机2武器3连续发射
        heroplane2_weapon3_continuous_firing = true;
        break;
    case Qt::Key_R://在游戏结束时按下R键退回主菜单
        if (game_status == 2){
            delete_level();//析构关卡
            turn_to_menu();
            break;
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        if (move_mode == 0)return;
        keylist2.append(event->key());
        break;
        }

    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_J://松开J键英雄机1武器1取消发射
        heroplane1_weapon1_continuous_firing = false;
        break;
    case Qt::Key_K://松开K键英雄机1武器2取消发射
        heroplane1_weapon2_continuous_firing = false;
        break;
    case Qt::Key_L://松开L键英雄机1武器3取消发射
        heroplane1_weapon3_continuous_firing = false;
        break;
    case Qt::Key_1://松开1键英雄机2武器1取消发射
        heroplane2_weapon1_continuous_firing = false;
        break;
    case Qt::Key_2://松开2键英雄机2武器2取消发射
        heroplane2_weapon2_continuous_firing = false;
        break;
    case Qt::Key_3://松开3键英雄机2武器3取消发射
        heroplane2_weapon3_continuous_firing = false;
        break;
    case Qt::Key_W:
    case Qt::Key_D:
    case Qt::Key_A:
    case Qt::Key_S:
        if (move_mode == 0)return;
        keylist1.removeOne(event->key());
        break;
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        if (move_mode == 0)return;
        keylist2.removeOne(event->key());
        break;
    }


}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton && keylist1.empty()){
        move_mode += 1;
        move_mode %= 2;
    }
}

//实现游戏暂停
void Widget::game_pause()
{
    if (game_status == 0){
        pause_background->setVisible(true);
        pause_picture->setVisible(true);
        game_timer->stop();
        game_status = 1;
    }
    else if (game_status == 1){
        pause_background->setVisible(false);
        pause_picture->setVisible(false);
        game_timer->start(GAME_PERIOD);
        game_status = 0;
    }
}

void Widget::heroplane1_shoot_1()
{
    //先判断武器是否可发射
    if (!heroplane1->weapon1->is_ready)return;
    //可发射就发射一颗子弹
    HeroBullet* new_herobullet;
    double x = heroplane1->x() + 42, y = heroplane1->y() - 30;
    new_herobullet = get_herobullet(x, y , heroplane1->weapon1->weapon_kind);
    new_herobullet->set_value(heroplane1->weapon1);
    heroplane1->weapon1->is_ready = false;//发射后要重置武器冷却
    heroplane1_weapon1_timer->start(heroplane1->weapon1->interval);//重新计时，顺便刷新计时间隔
    //播放子弹音效
    if (!bullet_sound->isPlaying())
        bullet_sound->play();
}

void Widget::heroplane1_shoot_2()
{
    //先判断武器是否可发射
    if (!heroplane1->weapon2->is_ready)return;
    //可发射就发射一颗子弹
    HeroBullet* new_herobullet;
    double x = heroplane1->x() + 42, y = heroplane1->y() - 30;
    new_herobullet = get_herobullet(x, y , heroplane1->weapon2->weapon_kind);
    new_herobullet->set_value(heroplane1->weapon2);
    heroplane1->weapon2->is_ready = false;//发射后要重置
    heroplane1_weapon2_timer->start(heroplane1->weapon2->interval);//重新计时，顺便刷新计时间隔
    //播放子弹音效
    if (!bullet_sound->isPlaying())
        bullet_sound->play();
}

void Widget::heroplane1_shoot_3()
{
    //先判断武器是否可发射
    if (!heroplane1->weapon3->is_ready)return;
    //可发射就发射一颗子弹
    HeroBullet* new_herobullet;
    double x = heroplane1->x() + 42, y = heroplane1->y() - 30;
    new_herobullet = get_herobullet(x, y , heroplane1->weapon3->weapon_kind);
    new_herobullet->set_value(heroplane1->weapon3);
    heroplane1->weapon3->is_ready = false;//发射后要重置
    heroplane1_weapon3_timer->start(heroplane1->weapon3->interval);//重新计时，顺便刷新计时间隔
    //播放子弹音效
    if (!bullet_sound->isPlaying())
        bullet_sound->play();
}

void Widget::heroplane2_shoot_1()
{
    //先判断武器是否可发射
    if (!heroplane2->weapon1->is_ready)return;
    //可发射就发射一颗子弹
    HeroBullet* new_herobullet;
    double x = heroplane2->x() + 42, y = heroplane2->y() - 30;
    new_herobullet = get_herobullet(x, y , heroplane2->weapon1->weapon_kind);
    new_herobullet->set_value(heroplane2->weapon1);
    heroplane2->weapon1->is_ready = false;//发射后要重置武器冷却
    heroplane2_weapon1_timer->start(heroplane2->weapon1->interval);//重新计时，顺便刷新计时间隔
    //播放子弹音效
    if (!bullet_sound->isPlaying())
        bullet_sound->play();
}

void Widget::heroplane2_shoot_2()
{
    //先判断武器是否可发射
    if (!heroplane2->weapon2->is_ready)return;
    //可发射就发射一颗子弹
    HeroBullet* new_herobullet;
    double x = heroplane2->x() + 42, y = heroplane2->y() - 30;
    new_herobullet = get_herobullet(x, y , heroplane2->weapon2->weapon_kind);
    new_herobullet->set_value(heroplane2->weapon2);
    heroplane2->weapon2->is_ready = false;//发射后要重置武器冷却
    heroplane2_weapon2_timer->start(heroplane2->weapon2->interval);//重新计时，顺便刷新计时间隔
    //播放子弹音效
    if (!bullet_sound->isPlaying())
        bullet_sound->play();
}

void Widget::heroplane2_shoot_3()
{
    //先判断武器是否可发射
    if (!heroplane2->weapon3->is_ready)return;
    //可发射就发射一颗子弹
    HeroBullet* new_herobullet;
    double x = heroplane2->x() + 42, y = heroplane2->y() - 30;
    new_herobullet = get_herobullet(x, y , heroplane2->weapon3->weapon_kind);
    new_herobullet->set_value(heroplane2->weapon3);
    heroplane2->weapon3->is_ready = false;//发射后要重置武器冷却
    heroplane2_weapon3_timer->start(heroplane2->weapon3->interval);//重新计时，顺便刷新计时间隔
    //播放子弹音效
    if (!bullet_sound->isPlaying())
        bullet_sound->play();
}

void Widget::enemyplane_shoot(EnemyPlane *enemyplane)
{
    if (!enemyplane || enemyplane->status != 2 || !enemyplane->weapon)
        return;

    // Boss特殊攻击模式
    if (enemyplane->is_boss()) {
        switch(enemyplane->boss_phase) {
        case 1:
            boss_shoot_pattern_1(enemyplane);
            break;
        case 2:
            boss_shoot_pattern_2(enemyplane);
            break;
        case 3:
            boss_shoot_pattern_3(enemyplane);
            break;
        }
        return;
    }

    // 普通敌机攻击模式（保持原有逻辑）
    switch(enemyplane->plane_kind) {
    case 1: {
        EnemyBullet* bullet = get_enemybullet(
            enemyplane->pos().x() + enemyplane->pixmap().width()/2 - 5,
            enemyplane->pos().y() + enemyplane->pixmap().height(),
            1
        );
        bullet->set_value(enemyplane->weapon);
        break;
    }
    case 2: {
        EnemyBullet* bullet1 = get_enemybullet(
            enemyplane->pos().x() + enemyplane->pixmap().width()/3,
            enemyplane->pos().y() + enemyplane->pixmap().height(),
            2
        );
        bullet1->set_value(enemyplane->weapon);

        EnemyBullet* bullet2 = get_enemybullet(
            enemyplane->pos().x() + enemyplane->pixmap().width()*2/3,
            enemyplane->pos().y() + enemyplane->pixmap().height(),
            3
        );
        bullet2->set_value(enemyplane->weapon);
        break;
    }
    case 3: {
        for (int i = -1; i <= 1; i++) {
            EnemyBullet* bullet = get_enemybullet(
                enemyplane->pos().x() + enemyplane->pixmap().width()/2 + i*10,
                enemyplane->pos().y() + enemyplane->pixmap().height(),
                3
            );
            bullet->set_value(enemyplane->weapon);
        }
        break;
    }
    case 4: {
        EnemyBullet* bullet = get_enemybullet(
            enemyplane->pos().x() + enemyplane->pixmap().width()/2 - 5,
            enemyplane->pos().y() + enemyplane->pixmap().height()/2,
            4
        );
        bullet->set_value(enemyplane->weapon);
        break;
    }
    }
}

//Boss攻击模式1：散弹攻击
void Widget::boss_shoot_pattern_1(EnemyPlane* boss)
{
    double centerX = boss->pos().x() + boss->pixmap().width() / 2;
    double centerY = boss->pos().y() + boss->pixmap().height();

    // 发射5发散弹
    for (int i = -2; i <= 2; i++) {
        EnemyBullet* bullet = get_enemybullet(
            centerX + i * 15,
            centerY,
            5 // Boss子弹类型1
        );
        bullet->set_value(boss->weapon);
    }
}

//Boss攻击模式2：环形弹幕
void Widget::boss_shoot_pattern_2(EnemyPlane* boss)
{
    double centerX = boss->pos().x() + boss->pixmap().width() / 2;
    double centerY = boss->pos().y() + boss->pixmap().height() / 2;

    // 发射8方向的环形弹幕
    for (int i = 0; i < 8; i++) {
        double angle = i * M_PI / 4; // 45度间隔
        double bulletX = centerX + 30 * cos(angle);
        double bulletY = centerY + 30 * sin(angle);

        EnemyBullet* bullet = get_enemybullet(bulletX, bulletY, 6); // Boss子弹类型2
        bullet->set_value(boss->weapon);
    }
}

//Boss攻击模式3：激光攻击
void Widget::boss_shoot_pattern_3(EnemyPlane* boss)
{
    double centerX = boss->pos().x() + boss->pixmap().width() / 2;
    double centerY = boss->pos().y() + boss->pixmap().height();

    // 发射密集的激光子弹
    for (int i = -3; i <= 3; i++) {
        for (int j = 0; j < 3; j++) {
            EnemyBullet* bullet = get_enemybullet(
                centerX + i * 10,
                centerY + j * 20,
                7 // Boss子弹类型3（激光）
            );
            bullet->set_value(boss->weapon);
        }
    }
}

PowerUp *Widget::get_powerup(int x, int y, int type)
{
    PowerUp* powerup;
    if (powerup_queue.empty()){
        powerup = new PowerUp();
        powerup_pool.append(powerup);
        level_scene.addItem(powerup);//加入场景
    }
    else{
        powerup = powerup_queue.dequeue();
    }
    powerup->status = 2;
    powerup->init(x, y, type);
    return powerup;
}

void Widget::drop_random_powerup(double x, double y)
{
    // 随机选择道具类型（1-5）
    int powerup_type = (rand() % 5) + 1;
    get_powerup(x, y, powerup_type);
}

void Widget::clear_all_enemies_and_bullets()
{
    //清除所有敌机
    for (EnemyPlane* enemyplane : enemyplane_pool){
        if (enemyplane->status == 2){
            enemyplane->destroy();
            // 清除敌机时也加分
            score += enemyplane->score / 2; // 炸弹清除的敌机只给一半分数
        }
    }

    //清除所有敌机子弹
    for (EnemyBullet* enemybullet : enemybullet_pool){
        if (enemybullet->status == 2){
            enemybullet->destroy();
        }
    }

    //更新分数显示
    score_board->setText("得分：" + QString::number(score));

}

void Widget::collision_detection_powerup_with_heroplane()
{
    //道具与英雄机的碰撞检测
    for (PowerUp* powerup : powerup_pool){
        if (powerup->status != 2) continue;

        //与英雄机1碰撞
        if (heroplane1 && powerup->collidesWithItem(heroplane1)){
            // 特殊处理炸弹效果
            if (powerup->powerup_type == POWERUP_TYPE_BOMB){
                // 炸弹效果已在apply_effect中处理
            }
            // 特殊处理火力增强效果的定时器
            else if (powerup->powerup_type == POWERUP_TYPE_FIREPOWER){
                // 连接效果结束信号
                connect(powerup->effect_timer, QTimer::timeout, this, [=](){
                    // 恢复原来的武器伤害
                    if (heroplane1->weapon1) {
                        heroplane1->weapon1->damage /= 1.5;
                    }
                    if (heroplane1->weapon2) {
                        heroplane1->weapon2->damage /= 1.5;
                    }
                    if (heroplane1->weapon3) {
                        heroplane1->weapon3->damage /= 1.5;
                    }
                });
            }
            // 特殊处理经验道具 - 同时增加分数
            if (powerup->powerup_type == POWERUP_TYPE_EXP){
                score += powerup->exp_bonus; // 经验道具也增加分数
                score_board->setText("得分：" + QString::number(score));
            }

            powerup->apply_effect(heroplane1);
            continue; // 道具已被拾取，跳过后续检测
        }

        //与英雄机2碰撞
        if (heroplane2 && powerup->collidesWithItem(heroplane2)){
            // 特殊处理炸弹效果
            if (powerup->powerup_type == POWERUP_TYPE_BOMB){
                // 炸弹效果已在apply_effect中处理
            }
            // 特殊处理火力增强效果的定时器
            else if (powerup->powerup_type == POWERUP_TYPE_FIREPOWER){
                // 连接效果结束信号
                connect(powerup->effect_timer, QTimer::timeout, this, [=](){
                    // 恢复原来的武器伤害
                    if (heroplane2->weapon1) {
                        heroplane2->weapon1->damage /= 1.5;
                    }
                    if (heroplane2->weapon2) {
                        heroplane2->weapon2->damage /= 1.5;
                    }
                    if (heroplane2->weapon3) {
                        heroplane2->weapon3->damage /= 1.5;
                    }
                });
            }
            // 特殊处理经验道具 - 同时增加分数
            if (powerup->powerup_type == POWERUP_TYPE_EXP){
                score += powerup->exp_bonus; // 经验道具也增加分数
                score_board->setText("得分：" + QString::number(score));
            }

            powerup->apply_effect(heroplane2);
        }
    }
}

void Widget::heroplane1_release_bomb()
{
    // 检查是否有炸弹
    if (heroplane1->bomb_count <= 0) {
        return;
    }

    // 消耗一个炸弹
    heroplane1->bomb_count--;

    // 执行炸弹效果
    clear_all_enemies_and_bullets();

    // 更新炸弹数量显示
    heroplane1_bomb_count->setText("炸弹: " + QString::number(heroplane1->bomb_count));

    // 可以添加炸弹爆炸音效
    if (bomb_sound) bomb_sound->play();

    //播放炸弹动画
    QTimer* timer = new QTimer();
    bomb_picture->setVisible(true);
    connect(timer, QTimer::timeout, this, [=](){
        bomb_picture->setVisible(false);
        timer->stop();
        delete timer;
    });
    timer->start(1000);
}

void Widget::heroplane2_release_bomb()
{
    // 检查是否有炸弹
    if (heroplane2->bomb_count <= 0) {
        return;
    }

    // 消耗一个炸弹
    heroplane2->bomb_count--;

    // 执行炸弹效果
    clear_all_enemies_and_bullets();

    // 更新炸弹数量显示
    heroplane2_bomb_count->setText("炸弹: " + QString::number(heroplane2->bomb_count));

    // 可以添加炸弹爆炸音效
    if (bomb_sound) bomb_sound->play();

    //播放炸弹动画
    QTimer* timer = new QTimer();
    bomb_picture->setVisible(true);
    connect(timer, QTimer::timeout, this, [=](){
        bomb_picture->setVisible(false);
        timer->stop();
        delete timer;
    });
    timer->start(1000);
}

void Widget::collision_detection()
{
    collision_detection_herobullet_with_enemyplane();
    collision_detection_enemybullet_with_heroplane();
    collision_detection_heroplane_with_enemyplane();
    collision_detection_powerup_with_heroplane();
}

void Widget::collision_detection_herobullet_with_enemyplane()
{
    for (HeroBullet* herobullet : herobullet_pool){
        if (herobullet->status != 2) continue;
        for (EnemyPlane* enemyplane : enemyplane_pool){
            if (enemyplane->status != 2) continue;
            if (enemyplane->collidesWithItem(herobullet)){
                enemyplane->collide_with_herobullet(herobullet);
                herobullet->collide_with_enemyplane(enemyplane);

                if (enemyplane->health <= 0 ){
                    score += enemyplane->score;
                    score_board->setText("得分：" + QString::number(score));
                    if (heroplane1) heroplane1->experience += enemyplane->score;
                    if (heroplane2) heroplane2->experience += enemyplane->score;
                    enemyplane_destroy_animation(enemyplane->pos().x(), enemyplane->pos().y());

                    // 增加击败敌机计数
                    if (!enemyplane->is_boss()) {
                        enemies_killed_in_level++;
                    }

                    if (rand() % 100 < POWERUP_DROP_CHANCE) {
                        drop_random_powerup(enemyplane->pos().x(), enemyplane->pos().y());
                    }
                    enemyplane_dead_sound->play();//播放敌机死亡动画
                }
            }
        }
    }
}

void Widget::collision_detection_enemybullet_with_heroplane()
{
    //先试试暴力检测
    for (EnemyBullet* enemybullet : enemybullet_pool){
        if (enemybullet->status != 2)continue;
        if (heroplane1){//英雄机必须要存在才检测
            if (enemybullet->collidesWithItem(heroplane1) && !heroplane1_invincible_timer->isActive()){//要保证英雄机不处于无敌状态
                enemybullet->collide_with_heroplane(heroplane1);
                heroplane1->collide_with_enemybullet(enemybullet);
            }
        }
        if (enemybullet->status != 2)continue;
        if (heroplane2){//英雄机必须要存在才检测
            if (enemybullet->collidesWithItem(heroplane2) && !heroplane2_invincible_timer->isActive()){//要保证英雄机不处于无敌状态
                enemybullet->collide_with_heroplane(heroplane2);
                heroplane2->collide_with_enemybullet(enemybullet);
            }
        }

    }
}

void Widget::collision_detection_heroplane_with_enemyplane()
{
    //先试试暴力检测
    for (EnemyPlane* enemyplane : enemyplane_pool){
        if (enemyplane->status != 2)continue;
        if (heroplane1){
            if (enemyplane->collidesWithItem(heroplane1) && !heroplane1_invincible_timer->isActive()){//要保证英雄机不处于无敌状态
                enemyplane->collide_with_heroplane(heroplane1);
                heroplane1->collide_with_enemyplane(enemyplane);
            }
        }
        if(enemyplane->status != 2)continue;
        if (heroplane2){
            if (enemyplane->collidesWithItem(heroplane2) && !heroplane2_invincible_timer->isActive()){//要保证英雄机不处于无敌状态
                enemyplane->collide_with_heroplane(heroplane2);
                heroplane2->collide_with_enemyplane(enemyplane);
                //如果敌机生命值小于0，则加分
                if (enemyplane->health <= 0 ){
                    score += enemyplane->score;
                    score_board->setText("得分：" + QString::number(score));
                    if (heroplane1) heroplane1->experience += score;//用得分代替经验值
                    if (heroplane2) heroplane2->experience += score;//用得分代替经验值（共享经验值）
                    enemyplane_destroy_animation(enemyplane->pos().x(), enemyplane->pos().y());//播放敌机摧毁动画
                    if (rand() % 100 < POWERUP_DROP_CHANCE) { // 30%概率掉落道具
                                            drop_random_powerup(enemyplane->pos().x(), enemyplane->pos().y());
                                        }
                    enemyplane_dead_sound->play();//播放敌机死亡动画
                }
            }
        }
    }
}

void Widget::enemyplane_destroy_animation(double x, double y)
{
    QTimer* timer = new QTimer();
    QGraphicsPixmapItem* frame = new QGraphicsPixmapItem();
    frame->setPos(x, y);
    frame->setPixmap(QPixmap(ENEMYPLANE_DESTROY_ANIMATION1));
    level_scene.addItem(frame);
    int* count = new int(0);
    connect(timer, QTimer::timeout, this, [=]() mutable{
        *count += 1;
        switch(*count){
        case 1:
            frame->setPixmap(QPixmap(ENEMYPLANE_DESTROY_ANIMATION2));
            break;
        case 2:
            frame->setPixmap(QPixmap(ENEMYPLANE_DESTROY_ANIMATION3));
            break;
        case 3:
            frame->setPixmap(QPixmap(ENEMYPLANE_DESTROY_ANIMATION4));
            break;
        case 4:
            level_scene.removeItem(frame);
            delete frame;
            timer->disconnect();
            delete timer;
            delete count;
            break;
        }
    });
    timer->start(150);//150ms播放一帧
}

void Widget::saveScore()
{
    QFile file("game_scores.txt");
    // 尝试打开文件，以读写方式，如果不存在则创建
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream in(&file);
        int highScore = 0;
        // 读取当前最高分
        if (!in.atEnd()) {
            in >> highScore;
        }
        // 如果当前分数高于最高分，则更新
        if (score > highScore) {
            highScore = score;
            // 回到文件开头，覆盖写入新的最高分
            file.seek(0);
            QTextStream out(&file);
            out << highScore;
        }
        file.close();
    }
}

// 从本地文件读取最高分
int Widget::loadHighScore() {
    QFile file("game_scores.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        int highScore = 0;
        in >> highScore;
        file.close();
        return highScore;
    }
    // 如果文件不存在，返回0
    return 0;
}

//游戏更新函数
void Widget::game_update()
{
    // 更新Boss血条
        if (boss_spawned && current_boss) {
            update_boss_health_bar();
        }
    //四个对象池中的对象的移动和检测

    //敌机池
    for (EnemyPlane* enemyplane : enemyplane_pool){
        if (enemyplane->status == 2){//status为2则移动
            enemyplane->move(heroplane1, heroplane2);
            enemyplane->is_live();//判断敌机是否还存活
        }
        else if (enemyplane->status == 0){//status为0则加入队列中
            enemyplane_queue.append(enemyplane);
            enemyplane->status = 1;
        }
    }

    //敌机子弹池
    for (EnemyBullet* enemybullet : enemybullet_pool){
        if (enemybullet->status == 2){
            enemybullet->move(heroplane1, heroplane2);
            enemybullet->is_live();
        }
        else if (enemybullet->status == 0){
            enemybullet_queue.append(enemybullet);
            enemybullet->status = 1;
        }
    }

    //英雄机子弹池
    for (HeroBullet* herobullet : herobullet_pool){
        if (herobullet->status == 2){
            herobullet->move(enemyplane_pool);
            herobullet->is_live();
        }
        else if (herobullet->status == 0){
            herobullet_queue.append(herobullet);
            herobullet->status = 1;
        }
    }

    //道具池
        for (PowerUp* powerup : powerup_pool){
            if (powerup->status == 2){
                powerup->move();
                powerup->is_live();
            }
            else if (powerup->status == 0){
                powerup_queue.append(powerup);
                powerup->status = 1;
            }
        }


    //碰撞检测（每40ms检测一次)
    static int count = 0;
    count += GAME_PERIOD;
    if (count == 40){
        count = 0;
        collision_detection();
    }

    //检测英雄机是否死亡
    if (heroplane1){
        heroplane1->is_live();
        if (heroplane1->status == 0){
            game_status = 2;
        }
    }
    if (heroplane2){
        heroplane2->is_live();
        if (heroplane2->status == 0){
            game_status = 2;
        }
    }

    if (game_status == 2){//游戏结束
        game_timer->stop();
        pause_background->setVisible(true);
        end_picture->setVisible(true);
        // 保存当前分数
        saveScore();
    }

    //英雄机与生命条的动态绑定
    if (heroplane1) heroplane1_healthBar->setValue(heroplane1->health * 100 / heroplane1->max_health);
    if (heroplane1) heroplane1_health_value->setText(QString::number(heroplane1->health));
    if (heroplane2) heroplane2_healthBar->setValue(heroplane2->health * 100 / heroplane2->max_health);
    if (heroplane2) heroplane2_health_value->setText(QString::number(heroplane2->health));

    //将英雄机与经验条动态绑定
    if (heroplane1) heroplane1_experience_bar->setValue(heroplane1->experience * 100 / heroplane1->next_level_experience);
    if (heroplane2) heroplane2_experience_bar->setValue(heroplane2->experience * 100 / heroplane2->next_level_experience);
    //将武器等级实时显示在屏幕上
    if (heroplane1->weapon1) heroplane1_weapon1_level_text->setText("lv " + QString::number(heroplane1->weapon1->weapon_level));
    if (heroplane1->weapon2) heroplane1_weapon2_level_text->setText("lv " + QString::number(heroplane1->weapon2->weapon_level));
    if (heroplane1->weapon3) heroplane1_weapon3_level_text->setText("lv " + QString::number(heroplane1->weapon3->weapon_level));
    if (heroplane2 && heroplane2->weapon1) heroplane2_weapon1_level_text->setText("lv " + QString::number(heroplane2->weapon1->weapon_level));
    if (heroplane2 && heroplane2->weapon2) heroplane2_weapon2_level_text->setText("lv " + QString::number(heroplane2->weapon2->weapon_level));
    if (heroplane2 && heroplane2->weapon3) heroplane2_weapon3_level_text->setText("lv " + QString::number(heroplane2->weapon3->weapon_level));
    //实时判断是否升级
    if (heroplane1 && heroplane1->is_upgrade()){
        // 显示升级文字
        heroplane1->level_up_text->setVisible(true);
        // 创建临时定时器控制显示时间
        QTimer* level_up_timer = new QTimer();
        connect(level_up_timer, &QTimer::timeout, this, [=]() {
            heroplane1->level_up_text->setVisible(false);
            level_up_timer->stop();
            delete level_up_timer;
        });
        level_up_timer->start(2000); // 2秒后隐藏

        int level = heroplane1->level;
        if (level == 2){
            //为升级获得的武器添加图标并设置对应计时器
            load_heroplane1_weapon2_background(heroplane1->weapon2);//加载武器图标
            //为武器1设置计时器
            heroplane1_weapon2_timer->start(heroplane1->weapon2->interval);
            connect(heroplane1_weapon2_timer, QTimer::timeout, this, [=](){
                heroplane1->weapon2->is_ready = true;
            });
        }
        else if (level == 3){
            //为升级获得的武器添加图标并设置对应计时器
            load_heroplane1_weapon3_background(heroplane1->weapon3);//加载武器图标
            //为武器1设置计时器
            heroplane1_weapon3_timer->start(heroplane1->weapon3->interval);
            connect(heroplane1_weapon3_timer, QTimer::timeout, this, [=](){
                heroplane1->weapon3->is_ready = true;
            });
        }

    }
    if (heroplane2 && heroplane2->is_upgrade()){

        // 显示升级文字
        heroplane2->level_up_text->setVisible(true);
        // 创建临时定时器控制显示时间
        QTimer* level_up_timer = new QTimer();
        connect(level_up_timer, &QTimer::timeout, this, [=]() {
            heroplane2->level_up_text->setVisible(false);
            level_up_timer->stop();
            delete level_up_timer;
        });
        level_up_timer->start(2000); // 2秒后隐藏

        //为升级获得的武器添加图标并设置对应计时器
        int level = heroplane2->level;
        if (level == 2){
            //为升级获得的武器添加图标并设置对应计时器
            load_heroplane2_weapon2_background(heroplane2->weapon2);//加载武器图标
            //为武器1设置计时器
            heroplane2_weapon2_timer->start(heroplane2->weapon2->interval);
            connect(heroplane2_weapon2_timer, QTimer::timeout, this, [=](){
                heroplane2->weapon2->is_ready = true;
            });
        }
        else if (level == 3){
            //为升级获得的武器添加图标并设置对应计时器
            load_heroplane2_weapon3_background(heroplane2->weapon3);//加载武器图标
            //为武器1设置计时器
            heroplane2_weapon3_timer->start(heroplane2->weapon3->interval);
            connect(heroplane2_weapon3_timer, QTimer::timeout, this, [=](){
                heroplane2->weapon3->is_ready = true;
            });
        }
    }



    //持续开火检测
    if (heroplane1){
        if (heroplane1->weapon1 && heroplane1_weapon1_continuous_firing){//要先判断对应武器是否已获得（已初始化）
            heroplane1_shoot_1();
        }
        if (heroplane1->weapon2 && heroplane1_weapon2_continuous_firing){
            heroplane1_shoot_2();
        }
        if (heroplane1->weapon3 && heroplane1_weapon3_continuous_firing){
            heroplane1_shoot_3();
        }
    }
    if (heroplane2){
        if (heroplane2->weapon1 && heroplane2_weapon1_continuous_firing){//要先判断对应武器是否已获得（已初始化）
            heroplane2_shoot_1();
        }
        if (heroplane2->weapon2 && heroplane2_weapon2_continuous_firing){
            heroplane2_shoot_2();
        }
        if (heroplane2->weapon3 && heroplane2_weapon3_continuous_firing){
            heroplane2_shoot_3();
        }
    }

    // 更新炸弹数量显示
    if (heroplane1) {
        heroplane1_bomb_count->setText("炸弹: " + QString::number(heroplane1->bomb_count));
    }
    if (heroplane2) {
        heroplane2_bomb_count->setText("炸弹: " + QString::number(heroplane2->bomb_count));
    }


}



