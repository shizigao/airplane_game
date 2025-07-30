#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    init_game();
    load_resources();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init_game()
{
    view = new QGraphicsView();
    view->setParent(this);
    startgame_scene = new QGraphicsScene();
    view->setScene(startgame_scene);

    // 禁用水平和垂直滚动条
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Widget::load_resources()
{
    load_timer();
    load_startgame();
    load_menu();
    load_level();
    load_pool();
}

void Widget::load_startgame()
{
    //加载背景图片
    startgame_background = new QGraphicsPixmapItem();
    startgame_background->setPixmap(QPixmap(STARTGAME_BACKGROUND));
    startgame_scene->addItem(startgame_background);

    //加载按钮
    startgame_button = new QPushButton();
    startgame_button->move(260, 600);
    startgame_button->setFixedSize(210, 90);
    startgame_button->setIcon(QIcon(STARTGAME_BUTTON));
    startgame_button->setIconSize(QSize(210, 90));
    startgame_button->setStyleSheet("QPushButton { background-color: transparent; border: none; }"
                                    "QPushButton:hover { background-color: rgba(255, 255, 255, 50); }");
    startgame_scene->addWidget(startgame_button);
    //连接信号槽
    connect(startgame_button, QPushButton::clicked, this, [=](){
        view->setScene(menu_scene);
    });
}

void Widget::load_menu()
{
    //加载主菜单背景
    menu_scene = new QGraphicsScene();
    menu_background = new QGraphicsPixmapItem();
    menu_background->setPixmap(QPixmap(MENU_BACKGROUND));
    menu_scene->addItem(menu_background);

    //加载主菜单按钮
    menu_one_player_level_button = new QPushButton();
    menu_one_player_endlessbutton = new QPushButton();
    menu_two_player_endlessbutton = new QPushButton();
    menu_two_player_against_button = new QPushButton();
    menu_record_button = new QPushButton();
    menu_settings_button = new QPushButton();
    menu_introductionbutton = new QPushButton();
    //设置按钮大小
    menu_one_player_level_button->setFixedSize(280, 120);
    menu_one_player_endlessbutton->setFixedSize(280, 120);
    menu_two_player_endlessbutton->setFixedSize(280, 120);
    menu_two_player_against_button->setFixedSize(280, 120);
    menu_record_button->setFixedSize(280, 120);
    menu_settings_button->setFixedSize(280, 120);
    menu_introductionbutton->setFixedSize(280, 120);
    //按钮图片
    menu_one_player_level_button->setIcon(QIcon(MENU_ONE_PLAYER_LEVEL_BUTTON_PICTURE));
    menu_one_player_endlessbutton->setIcon(QIcon(MENU_ONE_PLAYER_ENDLESS_BUTTON_PICTURE));
    menu_two_player_endlessbutton->setIcon(QIcon(MENU_TWO_PLAYER_ENDLESS_BUTTON_PICTURE));
    menu_two_player_against_button->setIcon(QIcon(MENU_TWO_PLAYER_AGAINST_BUTTON_PICTURE));
    menu_record_button->setIcon(QIcon(MENU_RECORD_BUTTON_PICTURE));
    menu_settings_button->setIcon(QIcon(MENU_SETTINGS_BUTTON_PICTURE));
    menu_introductionbutton->setIcon(QIcon(MENU_INTRODUCTION_BUTTON_PICTURE));
    //设置按钮图片大小
    menu_one_player_level_button->setIconSize(QSize(280, 120));
    menu_one_player_endlessbutton->setIconSize(QSize(280, 120));
    menu_two_player_endlessbutton->setIconSize(QSize(280, 120));
    menu_two_player_against_button->setIconSize(QSize(280, 120));
    menu_record_button->setIconSize(QSize(280, 120));
    menu_settings_button->setIconSize(QSize(280, 120));
    menu_introductionbutton->setIconSize(QSize(280, 120));
    //设置按钮位置
    menu_one_player_level_button->move(100, 300);
    menu_one_player_endlessbutton->move(400, 300);
    menu_two_player_endlessbutton->move(100, 500);
    menu_two_player_against_button->move(400, 500);
    menu_record_button->move(100, 700);
    menu_settings_button->move(400, 700);
    menu_introductionbutton->move(250, 900);
    //背景设置透明
    menu_one_player_level_button->setStyleSheet("QPushButton { background-color: transparent; border: none; }"
                                                "QPushButton:hover { background-color: rgba(255, 255, 255, 50); }");
    menu_one_player_endlessbutton->setStyleSheet("QPushButton { background-color: transparent; border: none; }"
                                                 "QPushButton:hover { background-color: rgba(255, 255, 255, 50); }");
    menu_two_player_endlessbutton->setStyleSheet("QPushButton { background-color: transparent; border: none; }"
                                                 "QPushButton:hover { background-color: rgba(255, 255, 255, 50); }");
    menu_two_player_against_button->setStyleSheet("QPushButton { background-color: transparent; border: none; }"
                                                  "QPushButton:hover { background-color: rgba(255, 255, 255, 50); }");
    menu_record_button->setStyleSheet("QPushButton { background-color: transparent; border: none; }"
                                      "QPushButton:hover { background-color: rgba(255, 255, 255, 50); }");
    menu_settings_button->setStyleSheet("QPushButton { background-color: transparent; border: none; }"
                                        "QPushButton:hover { background-color: rgba(255, 255, 255, 50); }");
    menu_introductionbutton->setStyleSheet("QPushButton { background-color: transparent; border: none; }"
                                           "QPushButton:hover { background-color: rgba(255, 255, 255, 50); }");

    //把按钮加入场景
    menu_scene->addWidget(menu_one_player_level_button);
    menu_scene->addWidget(menu_one_player_endlessbutton);
    menu_scene->addWidget(menu_two_player_endlessbutton);
    menu_scene->addWidget(menu_two_player_against_button);
    menu_scene->addWidget(menu_record_button);
    menu_scene->addWidget(menu_settings_button);
    menu_scene->addWidget(menu_introductionbutton);
    //信号槽
    connect(menu_one_player_level_button, QPushButton::clicked, this, [=](){
        turn_to_level1();
    });

}

void Widget::load_level()
{
    level_scene = new QGraphicsScene();
    //加载背景图片
    level1_background1 = new QGraphicsPixmapItem();
    level1_background1->setPixmap(QPixmap(LEVEL1_BACKGROUND));
    level1_background2 = new QGraphicsPixmapItem();
    level1_background2->setPixmap(QPixmap(LEVEL1_BACKGROUND));
    level1_background1->setScale(1.5);
    level1_background2->setScale(1.5);
    level1_background2->setPos(0, -1152);

    level_scene->addItem(level1_background1);
    level_scene->addItem(level1_background2);


}

void Widget::load_timer()
{
    game_timer = new QTimer(this);
    game_timer->setInterval(GAME_PERIOD);


}

void Widget::load_pool()
{
    herobullet_pool = new HeroBulletPool(level_scene, 10);//初始加载10个对象
    enemyplane_pool = new EnemyPlanePool(level_scene, 10);//初始加载10个对象

}

void Widget::load_heroplane1(int heroplane_kind)
{
    heroplane1 = new HeroPlane();
    heroplane1->init(heroplane_kind);
    heroplane1->setPos(600, 1000);
    level_scene->addItem(heroplane1);
}

void Widget::load_heroplane2(int heroplane_kind)
{
    heroplane2 = new HeroPlane();
    heroplane2->init(heroplane_kind);
    heroplane2->setPos(400, 1000);
    level_scene->addItem(heroplane2);
}


void Widget::level1_update()
{
    //场景的移动
    level1_background1->moveBy(0.0, 1.0);
    level1_background2->moveBy(0.0, 1.0);
    if (level1_background1->pos().y() >= 1152){
        level1_background1->setPos(0.0, 0.0);
    }
    if (level1_background2->pos().y() >= 0){
        level1_background2->setPos(0.0, -1152);
    }

    //生成敌人的逻辑
    static int count = 0;//计数
    if (count == 200){//200帧生成一个敌人
        EnemyPlane* enemyplane = enemyplane_pool->get_new_enemyplane();
        enemyplane->init(1);//初始化
        double rx = rand() % (GAME_WIDTH - enemyplane->pixmap().width());
        enemyplane->setPos(rx, -100);
        count = 0;
    }

    count++;

    //通用更新函数
    general_update();
}

void Widget::general_update()
{

    if (heroplane1){
        //英雄机的移动
        heroplane1_move();
        //英雄机发射子弹
        if (heroplane1->weapon1 && heroplane1->weapon1->is_continuously_shooting){
            heroplane1->weapon1_shoot(herobullet_pool, level_scene);
        }
        if (heroplane1->weapon2 && heroplane1->weapon2->is_continuously_shooting){
            heroplane1->weapon2_shoot(herobullet_pool, level_scene);
        }
        if (heroplane1->weapon3 && heroplane1->weapon3->is_continuously_shooting){
            heroplane1->weapon3_shoot(herobullet_pool, level_scene);
        }
    }
    if (heroplane2){
        //英雄机的移动
        heroplane2_move();
        //英雄机发射子弹
        if (heroplane2->weapon1 && heroplane2->weapon1->is_continuously_shooting){
            heroplane2->weapon1_shoot(herobullet_pool, level_scene);
        }
        if (heroplane2->weapon2 && heroplane2->weapon2->is_continuously_shooting){
            heroplane2->weapon2_shoot(herobullet_pool, level_scene);
        }
        if (heroplane2->weapon3 && heroplane2->weapon3->is_continuously_shooting){
            heroplane2->weapon3_shoot(herobullet_pool, level_scene);
        }
    }

    //英雄机子弹的移动
    for (HeroBullet* herobullet : *(herobullet_pool->herobullet_pool_list)){
        if (herobullet->status == 2){//子弹处于激活态，则移动
            herobullet->move();
        }
        else if (herobullet->status == 0){//子弹失效，则加入子弹池等待队列
            herobullet_pool->return_herobullet(herobullet);
        }
    }
    
    //敌机移动
    for (EnemyPlane* enemyplane : *(enemyplane_pool->enemyplane_pool_list)){
        if (enemyplane->status == 2){//敌机处于激活态，则移动
            enemyplane->move();
        }
        else if (enemyplane->status == 0){
            enemyplane_pool->return_enemyplane(enemyplane);
        }
    }
}

void Widget::turn_to_level1()
{
    view->setScene(level_scene);
    //选择英雄机
    load_heroplane1(1);

    connect(game_timer, QTimer::timeout, this, [=](){
        this->level1_update();
    });
    game_timer->start();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
        move_list.append(event->key());
        break;
    case Qt::Key_J:
        heroplane1->weapon1->is_continuously_shooting = true;
        break;
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key()){
    case Qt::Key_W:
    case Qt::Key_S:
    case Qt::Key_A:
    case Qt::Key_D:
        move_list.removeOne(event->key());
        break;
    case Qt::Key_J:
        heroplane1->weapon1->is_continuously_shooting = false;
        break;
    }
}

void Widget::heroplane1_move()
{
    if (!heroplane1)return;
    double x = heroplane1->pos().x(), y = heroplane1->pos().y();
    double speed = heroplane1->speed;
    double dx = 0, dy = 0;
    int key_count = 0;
    for (int key : move_list){
        switch (key){
        case Qt::Key_W:
            dy += -speed;
            break;
        case Qt::Key_S:
            dy += speed;
            break;
        case Qt::Key_A:
            dx += -speed;
            break;
        case Qt::Key_D:
            dx += speed;
            break;
        }
        key_count++;
    }
    if (key_count == 2){
        dx *= 0.7071;
        dy *= 0.7071;
    }
    x += dx;
    y += dy;
    heroplane1->setPos(x, y);
}

void Widget::heroplane2_move()
{

}
