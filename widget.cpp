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

void Widget::load_resources()
{
    load_timer();
    load_startgame();
    load_menu();
    load_levels();
    load_heroplane();//加载英雄机
}

void Widget::load_timer()
{
    game_timer = new QTimer(this);
    game_timer->start(GAME_PERIOD);
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

    //设置信号槽
    connect(single_level, QToolButton::clicked, this, turn_to_level1);
}

void Widget::load_levels()
{
    //加载关卡背景
    level_1_background1 = new QGraphicsPixmapItem();
    level_1_background1->setPixmap(QPixmap(LEVEL_1_BACKGROUND));
    level_1_background1->setScale(1.6);
    level_1_background2 = new QGraphicsPixmapItem();
    level_1_background2->setPixmap(QPixmap(LEVEL_1_BACKGROUND));
    level_1_background2->setScale(1.6);
    level_1_background2->setPos(0, -1229);

    level_2_background1 = new QGraphicsPixmapItem();
    level_2_background1->setPixmap(QPixmap(LEVEL_2_BACKGROUND));
    level_2_background1->setScale(1.6);
    level_2_background2 = new QGraphicsPixmapItem();
    level_2_background2->setPixmap(QPixmap(LEVEL_2_BACKGROUND));
    level_2_background2->setScale(1.6);
    level_2_background2->setPos(0, -1229);

    level_3_background1 = new QGraphicsPixmapItem();
    level_3_background1->setPixmap(QPixmap(LEVEL_3_BACKGROUND));
    level_3_background1->setScale(1.6);
    level_3_background2 = new QGraphicsPixmapItem();
    level_3_background2->setPixmap(QPixmap(LEVEL_3_BACKGROUND));
    level_3_background2->setScale(1.6);
    level_3_background2->setPos(0, -1229);

    level_4_background1 = new QGraphicsPixmapItem();
    level_4_background1->setPixmap(QPixmap(LEVEL_4_BACKGROUND));
    level_4_background1->setScale(1.6);
    level_4_background2 = new QGraphicsPixmapItem();
    level_4_background2->setPixmap(QPixmap(LEVEL_4_BACKGROUND));
    level_4_background2->setScale(1.6);
    level_4_background2->setPos(0, -1229);

    level_5_background1 = new QGraphicsPixmapItem();
    level_5_background1->setPixmap(QPixmap(LEVEL_5_BACKGROUND));
    level_5_background1->setScale(1.6);
    level_5_background2 = new QGraphicsPixmapItem();
    level_5_background2->setPixmap(QPixmap(LEVEL_5_BACKGROUND));
    level_5_background2->setScale(1.6);
    level_5_background2->setPos(0, -1229);

    level_1_scene.addItem(level_1_background1);
    level_1_scene.addItem(level_1_background2);
    level_2_scene.addItem(level_2_background1);
    level_2_scene.addItem(level_2_background2);
    level_3_scene.addItem(level_3_background1);
    level_3_scene.addItem(level_3_background2);
    level_4_scene.addItem(level_4_background1);
    level_4_scene.addItem(level_4_background2);
    level_5_scene.addItem(level_5_background1);
    level_5_scene.addItem(level_5_background2);

    
    //加载ui
    //关卡进度条
    level_1_progressBar = new QProgressBar();
    level_1_progressBar->setFixedSize(200, 20);
    level_1_progressBar->setStyleSheet( "QProgressBar {"
                                        "   text-align: center;"  // 文本位置
                                        "   color: #333;"         // 文本颜色
                                        "}"
                                        "QProgressBar::chunk {"
                                        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, " //背景渐变色
                                        "                               stop:0 #92FF77, "
                                        "                               stop:1 #FF2626);"
                                        "}");

    level_2_progressBar = new QProgressBar();
    level_2_progressBar->setFixedSize(200, 20);
    level_2_progressBar->setStyleSheet( "QProgressBar {"
                                        "   text-align: center;"  // 文本位置
                                        "   color: #333;"         // 文本颜色
                                        "}"
                                        "QProgressBar::chunk {"
                                        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, " //背景渐变色
                                        "                               stop:0 #92FF77, "
                                        "                               stop:1 #FF2626);"
                                        "}");

    level_3_progressBar = new QProgressBar();
    level_3_progressBar->setFixedSize(200, 20);
    level_3_progressBar->setStyleSheet( "QProgressBar {"
                                        "   text-align: center;"  // 文本位置
                                        "   color: #333;"         // 文本颜色
                                        "}"
                                        "QProgressBar::chunk {"
                                        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, " //背景渐变色
                                        "                               stop:0 #92FF77, "
                                        "                               stop:1 #FF2626);"
                                        "}");

    level_4_progressBar = new QProgressBar();
    level_4_progressBar->setFixedSize(200, 20);
    level_4_progressBar->setStyleSheet( "QProgressBar {"
                                        "   text-align: center;"  // 文本位置
                                        "   color: #333;"         // 文本颜色
                                        "}"
                                        "QProgressBar::chunk {"
                                        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, " //背景渐变色
                                        "                               stop:0 #92FF77, "
                                        "                               stop:1 #FF2626);"
                                        "}");

    level_5_progressBar = new QProgressBar();
    level_5_progressBar->setFixedSize(200, 20);
    level_5_progressBar->setStyleSheet( "QProgressBar {"
                                        "   text-align: center;"  // 文本位置
                                        "   color: #333;"         // 文本颜色
                                        "}"
                                        "QProgressBar::chunk {"
                                        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, " //背景渐变色
                                        "                               stop:0 #92FF77, "
                                        "                               stop:1 #FF2626);"
                                        "}");
    level_1_progressBar->setValue(100);
    level_1_scene.addWidget(level_1_progressBar);
    level_2_progressBar->setValue(100);
    level_2_scene.addWidget(level_2_progressBar);
    level_3_progressBar->setValue(100);
    level_3_scene.addWidget(level_3_progressBar);
    level_4_progressBar->setValue(100);
    level_4_scene.addWidget(level_4_progressBar);
    level_5_progressBar->setValue(100);
    level_5_scene.addWidget(level_5_progressBar);

    //加载生命条
    level_1_healthBar = new QProgressBar();
    level_1_healthBar->setFixedSize(60, 200);
    level_1_healthBar->move(VIEW_WIDTH - 40, VIEW_HEIGHT - 200);
    level_1_healthBar->setValue(100);
    level_1_healthBar->setTextVisible(false);//生命值比率不可见，用生命值属性替代
    level_1_healthBar->setStyleSheet("QProgressBar::chunk {"
                                     "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                                     "                               stop:0 #92FF77, "
                                     "                               stop:1 #FF2626);"
                                     "}");
    level_1_healthBar->setOrientation(Qt::Vertical);//设置生命条垂直
    level_1_scene.addWidget(level_1_healthBar);

    level_1_healthValue = new QLineEdit();
    level_1_healthValue->setText("233");
    level_1_healthValue->setReadOnly(true);
    level_1_healthValue->move(VIEW_WIDTH - 40, VIEW_HEIGHT - 125);
    level_1_healthValue->setStyleSheet(R"(
                                       QLineEdit:read-only {
                                           font-family: "Arial Black";  /* 字体家族 */
                                           font-size: 20px;            /* 字体大小 */
                                       font-weight: bold;
                                           background-color: transparent;
                                           border: none;  /* 可选：去掉边框 */
                                           color: #FF0B0B;   /* 文字颜色 */
                                       }
                                   )");
    level_1_scene.addWidget(level_1_healthValue);

    level_2_healthBar = new QProgressBar();
    level_2_healthBar->setFixedSize(60, 200);
    level_2_healthBar->move(VIEW_WIDTH - 40, VIEW_HEIGHT - 200);
    level_2_healthBar->setValue(100);
    level_2_healthBar->setTextVisible(false);//生命值比率不可见，用生命值属性替代
    level_2_healthBar->setStyleSheet("QProgressBar::chunk {"
                                     "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                                     "                               stop:0 #92FF77, "
                                     "                               stop:1 #FF2626);"
                                     "}");
    level_2_healthBar->setOrientation(Qt::Vertical);//设置生命条垂直
    level_2_scene.addWidget(level_2_healthBar);

    level_2_healthValue = new QLineEdit();
    level_2_healthValue->setText("233");
    level_2_healthValue->setReadOnly(true);
    level_2_healthValue->move(VIEW_WIDTH - 40, VIEW_HEIGHT - 125);
    level_2_healthValue->setStyleSheet(R"(
                                       QLineEdit:read-only {
                                           font-family: "Arial Black";  /* 字体家族 */
                                           font-size: 20px;            /* 字体大小 */
                                       font-weight: bold;
                                           background-color: transparent;
                                           border: none;  /* 可选：去掉边框 */
                                           color: #FF0B0B;   /* 文字颜色 */
                                       }
                                   )");
    level_2_scene.addWidget(level_2_healthValue);

    level_3_healthBar = new QProgressBar();
    level_3_healthBar->setFixedSize(60, 200);
    level_3_healthBar->move(VIEW_WIDTH - 40, VIEW_HEIGHT - 200);
    level_3_healthBar->setValue(100);
    level_3_healthBar->setTextVisible(false);//生命值比率不可见，用生命值属性替代
    level_3_healthBar->setStyleSheet("QProgressBar::chunk {"
                                     "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                                     "                               stop:0 #92FF77, "
                                     "                               stop:1 #FF2626);"
                                     "}");
    level_3_healthBar->setOrientation(Qt::Vertical);//设置生命条垂直
    level_3_scene.addWidget(level_3_healthBar);

    level_3_healthValue = new QLineEdit();
    level_3_healthValue->setText("233");
    level_3_healthValue->setReadOnly(true);
    level_3_healthValue->move(VIEW_WIDTH - 40, VIEW_HEIGHT - 125);
    level_3_healthValue->setStyleSheet(R"(
                                       QLineEdit:read-only {
                                           font-family: "Arial Black";  /* 字体家族 */
                                           font-size: 20px;            /* 字体大小 */
                                       font-weight: bold;
                                           background-color: transparent;
                                           border: none;  /* 可选：去掉边框 */
                                           color: #FF0B0B;   /* 文字颜色 */
                                       }
                                   )");
    level_3_scene.addWidget(level_3_healthValue);

    level_4_healthBar = new QProgressBar();
    level_4_healthBar->setFixedSize(60, 200);
    level_4_healthBar->move(VIEW_WIDTH - 40, VIEW_HEIGHT - 200);
    level_4_healthBar->setValue(100);
    level_4_healthBar->setTextVisible(false);//生命值比率不可见，用生命值属性替代
    level_4_healthBar->setStyleSheet("QProgressBar::chunk {"
                                     "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                                     "                               stop:0 #92FF77, "
                                     "                               stop:1 #FF2626);"
                                     "}");
    level_4_healthBar->setOrientation(Qt::Vertical);//设置生命条垂直
    level_4_scene.addWidget(level_4_healthBar);

    level_4_healthValue = new QLineEdit();
    level_4_healthValue->setText("233");
    level_4_healthValue->setReadOnly(true);
    level_4_healthValue->move(VIEW_WIDTH - 40, VIEW_HEIGHT - 125);
    level_4_healthValue->setStyleSheet(R"(
                                       QLineEdit:read-only {
                                           font-family: "Arial Black";  /* 字体家族 */
                                           font-size: 20px;            /* 字体大小 */
                                       font-weight: bold;
                                           background-color: transparent;
                                           border: none;  /* 可选：去掉边框 */
                                           color: #FF0B0B;   /* 文字颜色 */
                                       }
                                   )");
    level_4_scene.addWidget(level_4_healthValue);

    level_5_healthBar = new QProgressBar();
    level_5_healthBar->setFixedSize(60, 200);
    level_5_healthBar->move(VIEW_WIDTH - 40, VIEW_HEIGHT - 200);
    level_5_healthBar->setValue(100);
    level_5_healthBar->setTextVisible(false);//生命值比率不可见，用生命值属性替代
    level_5_healthBar->setStyleSheet("QProgressBar::chunk {"
                                     "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                                     "                               stop:0 #92FF77, "
                                     "                               stop:1 #FF2626);"
                                     "}");
    level_5_healthBar->setOrientation(Qt::Vertical);//设置生命条垂直
    level_5_scene.addWidget(level_5_healthBar);

    level_5_healthValue = new QLineEdit();
    level_5_healthValue->setText("233");
    level_5_healthValue->setReadOnly(true);
    level_5_healthValue->move(VIEW_WIDTH - 40, VIEW_HEIGHT - 125);
    level_5_healthValue->setStyleSheet(R"(
                                       QLineEdit:read-only {
                                           font-family: "Arial Black";  /* 字体家族 */
                                           font-size: 20px;            /* 字体大小 */
                                       font-weight: bold;
                                           background-color: transparent;
                                           border: none;  /* 可选：去掉边框 */
                                           color: #FF0B0B;   /* 文字颜色 */
                                       }
                                   )");
    level_5_scene.addWidget(level_5_healthValue);

    //加载武器背景
    level_1_weapon1 = new QGraphicsPixmapItem();
    level_1_weapon1->setPixmap(QPixmap(WEAPON_BACKGROUND));
    level_1_weapon1->setScale(0.1);
    level_1_weapon1->setPos(VIEW_WIDTH - 100, VIEW_HEIGHT - 190);
    level_1_scene.addItem(level_1_weapon1);

    level_1_weapon2 = new QGraphicsPixmapItem();
    level_1_weapon2->setPixmap(QPixmap(WEAPON_BACKGROUND));
    level_1_weapon2->setScale(0.1);
    level_1_weapon2->setPos(VIEW_WIDTH - 100, VIEW_HEIGHT - 120);
    level_1_scene.addItem(level_1_weapon2);

    level_1_weapon3 = new QGraphicsPixmapItem();
    level_1_weapon3->setPixmap(QPixmap(WEAPON_BACKGROUND));
    level_1_weapon3->setScale(0.1);
    level_1_weapon3->setPos(VIEW_WIDTH - 100, VIEW_HEIGHT - 50);
    level_1_scene.addItem(level_1_weapon3);

    level_1_weapon4 = new QGraphicsPixmapItem();
    level_1_weapon4->setPixmap(QPixmap(WEAPON_BACKGROUND));
    level_1_weapon4->setScale(0.1);
    level_1_weapon4->setPos(VIEW_WIDTH - 160, VIEW_HEIGHT - 50);
    level_1_scene.addItem(level_1_weapon4);


    //加载得分
    level_1_score = new QLineEdit();
    level_1_score->setText("得分：114514");
    level_1_score->setReadOnly(true);
    level_1_score->move(VIEW_WIDTH - 160, 0);
    level_1_scene.addWidget(level_1_score);
    level_1_score->setStyleSheet(R"(
                                 QLineEdit:read-only {
                                     font-family: "Arial Black";  /* 字体家族 */
                                     font-size: 18px;            /* 字体大小 */
                                 font-weight: bold;
                                     background-color: transparent;
                                     border: none;  /* 可选：去掉边框 */
                                     color: #FF0B0B;   /* 文字颜色 */
                                 }
                             )");




}
//加载英雄机资源
void Widget::load_heroplane()
{
    heroplane1 = new HeroPlane(300, 1000, QPixmap(HEROPLANE_1));
    heroplane2 = new HeroPlane(600, 1000, QPixmap(HEROPLANE_2));
}

//转到菜单页面
void Widget::turn_to_menu()
{
    main_view.setScene(&main_scene2);
}

//转到第一关
void Widget::turn_to_level1()
{
    main_view.setScene(&level_1_scene);//将视图对准第一关场景
    connect(game_timer, QTimer::timeout, this, level_1_update);//设置计时器与第一关场景之间的信号槽
    //将英雄机加载到第一关
    level_1_scene.addItem(heroplane1);
}

void Widget::heroplane_move2(HeroPlane* heroplane)
{
    int x = heroplane->pos().x();
    int y = heroplane->pos().y();
    for (int keyCode : keylist){
        switch(keyCode){
        case Qt::Key_W:
            y -= heroplane->speed;
            break;
        case Qt::Key_D:
            x += heroplane->speed;
            break;
        case Qt::Key_A:
            x -= heroplane->speed;
            break;
        case Qt::Key_S:
            y += heroplane->speed;
            break;
        }
    }
    heroplane->setPos(x, y);
}

//实现鼠标控制飞机移动
void Widget::heroplane_move1()
{
    int x = heroplane1->pos().x();
    int y = heroplane1->pos().y();
    QPoint point = QCursor::pos();
    QPoint local_point = mapFromGlobal(point);
    int px = local_point.x(), py = local_point.y();
    int rect_x = heroplane1->rect.width() / 2, rect_y = heroplane1->rect.height() / 2;//飞机在x轴和y轴上的移动比率（模拟按直线接近鼠标位置）
    int cx = x + rect_x, cy = y + rect_y;//飞机中心坐标
    double rate_x = abs(cx - px) / double(abs(cx - px) + abs(cy - py));
    double rate_y = abs(cy - py) / double(abs(cx - px) + abs(cy - py));

    if ( cx > px + 5 && cx >= 0){
        x -= heroplane1->speed * rate_x;
    }
    else if (cx < px - 5 && cx <= VIEW_WIDTH){
        x += heroplane1->speed * rate_x;
    }
    if (cy > py + 5 && cy >= 0){
        y -= heroplane1->speed * rate_y;
    }
    else if (cy < py - 5 && cy <= VIEW_HEIGHT){
        y += heroplane1->speed * rate_y;
    }
    heroplane1->setPos(x, y);
}

void Widget::level_1_update()
{
    //场景移动
    level_1_background1->setY(level_1_background1->y() + 2);
    if (level_1_background1->y() >= 1229){
        level_1_background1->setY(0);
    }
    level_1_background2->setY(level_1_background2->y() + 2);
    if (level_1_background2->y() >= 0){
        level_1_background2->setY(-1229);
    }
    //英雄机位置更新
    if (move_mode == 1){
        heroplane_move1();
    }
    else{
        heroplane_move2(heroplane1);
    }
    game_update();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (move_mode == 1)return;
    switch (event->key()) {
    case Qt::Key_W:
    case Qt::Key_D:
    case Qt::Key_A:
    case Qt::Key_S:
        keylist.append(event->key());
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    if (move_mode == 1)return;
    keylist.removeOne(event->key());
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton && keylist.empty()){
        move_mode += 1;
        move_mode %= 2;
    }
}

//游戏更新函数
void Widget::game_update()
{

}



