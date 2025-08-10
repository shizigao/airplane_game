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
    load_pause();
    load_end();
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

    //分数板
    high_score_text = new QLineEdit();
    high_score_text->setReadOnly(true);
    high_score_text->setFixedSize(200, 50);
    high_score_text->move(300, 50); // 调整位置
    high_score_text->setStyleSheet(R"(
        QLineEdit:read-only {
            font-family: "Arial Black";
            font-size: 18px;
            font-weight: bold;
            background-color: transparent;
            border: 2px solid #FF0B0B;
            color: #FF0B0B;
        }
    )");
    menu_scene->addWidget(high_score_text);
    high_score_text->setVisible(false); // 初始隐藏

    //信号槽
    //转到第一关
    connect(menu_one_player_level_button, QPushButton::clicked, this, [=](){
        turn_to_level1();
    });
    //显示最高分
    connect(menu_record_button, QPushButton::clicked, this, [=](){
        int highScore = load_score();
        high_score_text->setText(QString("最高分: %1").arg(highScore));
        high_score_text->setVisible(true);
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

    //血量进度条
    //英雄机1的血量条
    heroplane1_health_bar = new QProgressBar();
    heroplane1_health_bar->move(GAME_WIDTH - 40, GAME_HEIGHT - 160);
    heroplane1_health_bar->setFixedSize(40, 160);
    heroplane1_health_bar->setValue(80);
    heroplane1_health_bar->setOrientation(Qt::Vertical);//设置生命条垂直
    heroplane1_health_bar->setTextVisible(false);
    heroplane1_health_bar->setStyleSheet(R"(
                                         QProgressBar {
                                             border: 2px solid #5c5c5c;    /* 边框样式 */
                                             text-align: center;           /* 文本居中 */
                                             height: 30px;                 /* 进度条高度 */
                                             background-color: rgba(0, 0, 0, 0); /* 背景完全透明 */
                                             background-color: #f0f0f0;    /* 背景颜色 */
                                         }
                                         QProgressBar::chunk {
                                         background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                         stop:0 #ff4444,    /* 红色 */
                                         stop:0.5 #ffdd44,  /* 中间黄色过渡 */
                                         stop:1 #44dd44);   /* 绿色 */
                                             border-radius: 4px;           /* 进度块圆角 */
                                             margin: 1px;                  /* 进度块与边框间距 */
                                         }
                                     )");

    level_scene->addWidget(heroplane1_health_bar);

    //英雄机2的血量条
    heroplane2_health_bar = new QProgressBar();
    heroplane2_health_bar->move(0, GAME_HEIGHT - 160);
    heroplane2_health_bar->setFixedSize(40, 160);
    heroplane2_health_bar->setValue(80);
    heroplane2_health_bar->setOrientation(Qt::Vertical);//设置生命条垂直
    heroplane2_health_bar->setTextVisible(false);
    heroplane2_health_bar->setStyleSheet(R"(
                                         QProgressBar {
                                             border: 2px solid #5c5c5c;    /* 边框样式 */
                                             text-align: center;           /* 文本居中 */
                                             height: 30px;                 /* 进度条高度 */
                                             background-color: rgba(0, 0, 0, 0); /* 背景完全透明 */
                                             background-color: #f0f0f0;    /* 背景颜色 */
                                         }
                                         QProgressBar::chunk {
                                         background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                         stop:0 #ff4444,    /* 红色 */
                                         stop:0.5 #ffdd44,  /* 中间黄色过渡 */
                                         stop:1 #44dd44);   /* 绿色 */
                                             border-radius: 4px;           /* 进度块圆角 */
                                             margin: 1px;                  /* 进度块与边框间距 */
                                         }
                                     )");

    level_scene->addWidget(heroplane2_health_bar);

    //英雄机血量显示文本
    //英雄机1
    heroplane1_health_text = new QLineEdit();
    heroplane1_health_text->setReadOnly(true);
    heroplane1_health_text->move(GAME_WIDTH - 40, GAME_HEIGHT - 90);
    heroplane1_health_text->setText("111");
    heroplane1_health_text->setStyleSheet(R"(
                                          QLineEdit:read-only {
                                              font-family: "Arial Black";  /* 字体家族 */
                                              font-size: 20px;            /* 字体大小 */
                                          font-weight: bold;
                                              background-color: transparent;
                                              border: none;  /* 可选：去掉边框 */
                                              color: #FF0B0B;   /* 文字颜色 */
                                          }
                                      )");

    level_scene->addWidget(heroplane1_health_text);
    //英雄机2
    heroplane2_health_text = new QLineEdit();
    heroplane2_health_text->setReadOnly(true);
    heroplane2_health_text->move(0, GAME_HEIGHT - 90);
    heroplane2_health_text->setText("111");
    heroplane2_health_text->setStyleSheet(R"(
                                          QLineEdit:read-only {
                                              font-family: "Arial Black";  /* 字体家族 */
                                              font-size: 20px;            /* 字体大小 */
                                          font-weight: bold;
                                              background-color: transparent;
                                              border: none;  /* 可选：去掉边框 */
                                              color: #FF0B0B;   /* 文字颜色 */
                                          }
                                      )");

    level_scene->addWidget(heroplane2_health_text);

    //加载分数板
    score_text = new QLineEdit();
    score_text->setText("得分：0");
    score_text->setReadOnly(true);
    score_text->move(GAME_WIDTH - 160, 0);
    score_text->setStyleSheet(R"(
                                 QLineEdit:read-only {
                                     font-family: "Arial Black";  /* 字体家族 */
                                     font-size: 18px;            /* 字体大小 */
                                 font-weight: bold;
                                     background-color: transparent;
                                     border: none;  /* 可选：去掉边框 */
                                     color: #FF0B0B;   /* 文字颜色 */
                                 }
                             )");
    level_scene->addWidget(score_text);

    //加载经验条
    //英雄机1的经验条
    heroplane1_experience_bar = new QProgressBar();
    heroplane1_experience_bar->setFixedSize(40, 20);
    heroplane1_experience_bar->move(GAME_WIDTH - 40, GAME_HEIGHT - 180);
    heroplane1_experience_bar->setTextVisible(false);
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
    level_scene->addWidget(heroplane1_experience_bar);
    //英雄机2的经验条
    heroplane2_experience_bar = new QProgressBar();
    heroplane2_experience_bar->setFixedSize(40, 20);
    heroplane2_experience_bar->move(0, GAME_HEIGHT - 180);
    heroplane2_experience_bar->setTextVisible(false);
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


    level_scene->addWidget(heroplane2_experience_bar);


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
    enemybullet_pool = new EnemyBulletPool(level_scene, 10);//初始加载10个对象
}

void Widget::load_pause()
{
    pause_picture = new QGraphicsPixmapItem();
    pause_picture->setPixmap(QPixmap(PAUSE_PICTURE));
    pause_picture->setPos(GAME_WIDTH / 2 - pause_picture->pixmap().width() / 2, GAME_HEIGHT / 2 - pause_picture->pixmap().height() / 2);
    pause_picture->setZValue(91); //层级设置比pause_background要高
    pause_picture->setVisible(false);
    level_scene->addItem(pause_picture);

    pause_background = new QGraphicsRectItem();
    pause_background->setRect(0, 0, GAME_WIDTH, GAME_HEIGHT);
    pause_background->setBrush(QColor(0, 0, 0, 128)); // 黑色半透明（alpha=128，0-255）
    pause_background->setZValue(90); // 层级设为次顶层（高于游戏元素）
    pause_background->setVisible(false); // 默认隐藏
    level_scene->addItem(pause_background);
}

void Widget::load_end()
{
    end_picture = new QGraphicsPixmapItem();
    end_picture->setPixmap(QPixmap(END_PICTURE));
    end_picture->setPos(GAME_WIDTH / 2 - end_picture->pixmap().width() / 2, GAME_HEIGHT / 2 - end_picture->pixmap().height() / 2);
    end_picture->setZValue(91); //层级设置比pause_background要高
    end_picture->setVisible(false);
    level_scene->addItem(end_picture);

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
    level1_background1->moveBy(0.0, 0.5);
    level1_background2->moveBy(0.0, 0.5);
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
        //更新英雄机血量对应的UI
        heroplane1_health_bar->setValue(heroplane1->get_health_rate());
        heroplane1_health_text->setText(QString::number(heroplane1->health, 'f', 0));
        //更新英雄机经验条
        heroplane1_experience_bar->setValue(heroplane1->get_experience_rate());
        //护盾
        if (heroplane1->shield_timer->isActive()){
            heroplane1->shield->setVisible(true);
        }
        else {
            heroplane1->shield->setVisible(false);
        }
        //判断是否升级
        if (heroplane1->experience >= heroplane1->next_level_experience){
            heroplane1->upgrade(this);
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
        //更新英雄机血量对应的UI
        heroplane2_health_bar->setValue(heroplane2->get_health_rate());
        heroplane2_health_text->setText(QString::number(heroplane2->health, 'f', 0));
        //更新英雄机经验条
        heroplane2_experience_bar->setValue(heroplane2->get_experience_rate());
        //护盾
        if (heroplane2->shield_timer->isActive()){
            heroplane2->shield->setVisible(true);
        }
        else {
            heroplane2->shield->setVisible(false);
        }
        //判断是否升级
        if (heroplane2->experience >= heroplane2->next_level_experience){
            heroplane2->upgrade(this);
        }
    }

    //英雄机子弹的移动
    for (HeroBullet* herobullet : *(herobullet_pool->herobullet_pool_list)){
        if (herobullet->status == 2){//子弹处于激活态，则移动
            herobullet->move(enemyplane_pool);
        }
        else if (herobullet->status == 0){//子弹失效，则加入子弹池等待队列
            herobullet_pool->return_herobullet(herobullet);
        }
    }
    

    for (EnemyPlane* enemyplane : *(enemyplane_pool->enemyplane_pool_list)){
        if (enemyplane->status == 2){//敌机处于激活态，则移动
            //发射子弹检测
            enemyplane->weapon_shoot(enemybullet_pool, level_scene);
            //敌机移动
            enemyplane->move();
            //判断生命值是否小于0
            enemyplane->is_live();

        }
        else if (enemyplane->status == 0){

            score += enemyplane->score;

            if(heroplane1){
                heroplane1->experience += enemyplane->experience;
            }
            if(heroplane2){
                heroplane2->experience += enemyplane->experience;
            }

            enemyplane_pool->return_enemyplane(enemyplane);
        }
    }

    for (EnemyBullet* enemybullet : *(enemybullet_pool->enemybullet_pool_list)){
        if (enemybullet->status == 2){
            //子弹移动
            enemybullet->move();
        }
        else if (enemybullet->status == 0){
            enemybullet_pool->return_enemybullet(enemybullet);
        }
    }

    //碰撞检测
    collision_detection();

    //判断英雄机生命是否小于零（游戏结束判断）
    if (heroplane1 && heroplane1->health <= 0){
        status = 0;
    }
    else if (heroplane2 && heroplane2->health <= 0){
        status = 0;
    }
    if (status == 0){
        save_score();
        game_end();
    }

    //分数板更新
    score_text->setText("分数：" + QString::number(score));



}

void Widget::turn_to_menu()
{
    view->setScene(menu_scene);
}

void Widget::turn_to_level1()
{
    view->setScene(level_scene);

    //选择英雄机
    load_heroplane1(1);


    status = 2;
    pause_background->setVisible(false);\
    end_picture->setVisible(false);


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
    case Qt::Key_P:
        game_pause();
        break;
    case Qt::Key_R:
        if (status == 0){
            delete_level();
            turn_to_menu();
        }
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
    //如果超过边界则不移动
    if (x <= 0 || x >= GAME_WIDTH - heroplane1->pixmap().width() || y <= 0 || y >= GAME_HEIGHT - heroplane1->pixmap().height()){
        return;
    }
    heroplane1->setPos(x, y);
}

void Widget::heroplane2_move()
{

}

void Widget::collision_detection()
{
    collision_detection_enemybullet_with_heroplane();
    collision_detection_herobullet_with_enemyplane();
    collision_detection_heroplane_with_enemyplane();
}

void Widget::collision_detection_herobullet_with_enemyplane()
{
    //暴力枚举检测碰撞检测
    for (HeroBullet* herobullet : *(herobullet_pool->herobullet_pool_list)){
        if (herobullet->status == 2){
            for (EnemyPlane* enemyplane : *(enemyplane_pool->enemyplane_pool_list)){
                if (enemyplane->status == 2){
                    if (herobullet->collidesWithItem(enemyplane)){
                        //碰撞函数
                        enemyplane->collide_with_herobullet(herobullet);
                        herobullet->collide_with_enemyplane(enemyplane);
                    }

                }
            }
        }
    }
}

void Widget::collision_detection_enemybullet_with_heroplane()
{
    //暴力枚举检测碰撞检测
    for (EnemyBullet* enemybullet : *(enemybullet_pool->enemybullet_pool_list)){
        if (enemybullet->status == 2){
            //英雄机1
            if (heroplane1 && heroplane1->status == 2){
                if (heroplane1->collidesWithItem(enemybullet)){
                    heroplane1->collide_with_enemybullet(enemybullet);
                    enemybullet->collide_with_heroplane();
                }
            }
            //英雄机2
            if (heroplane2 && heroplane2->status == 2 && enemybullet->status == 2){
                if (heroplane2->collidesWithItem(enemybullet)){
                    heroplane2->collide_with_enemybullet(enemybullet);
                    enemybullet->collide_with_heroplane();
                }
            }
        }
    }
}

void Widget::collision_detection_heroplane_with_enemyplane()
{
    //暴力枚举检测碰撞检测
    for (EnemyPlane* enemyplane : *(enemyplane_pool->enemyplane_pool_list)){
        if (enemyplane->status == 2){
            //英雄机1
            if (heroplane1 && heroplane1->status == 2 && !heroplane1->shield_timer->isActive()){
                if (heroplane1->collidesWithItem(enemyplane)){
                    heroplane1->collide_with_enemyplane(enemyplane);
                    enemyplane->collide_with_heroplane(heroplane1);
                }
            }
            //英雄机2
            if (heroplane2 && heroplane2->status == 2 && enemyplane->status == 2 && !heroplane2->shield_timer->isActive()){
                if (heroplane2->collidesWithItem(enemyplane)){
                    heroplane2->collide_with_enemyplane(enemyplane);
                    enemyplane->collide_with_heroplane(heroplane2);
                }

            }
        }
    }
}

void Widget::game_pause()
{
    if (status == 2){//如果游戏处于运行状态
        status = 1;
        pause_background->setVisible(true);
        pause_picture->setVisible(true);
        game_timer->stop();
    }
    else if (status == 1){//如果游戏处于暂停状态
        status = 2;
        pause_background->setVisible(false);
        pause_picture->setVisible(false);
        game_timer->start();
    }
}

void Widget::game_end()
{
    //显示游戏结束的界面
    end_picture->setVisible(true);
    pause_background->setVisible(true);
    game_timer->stop();
}

void Widget::delete_level()
{
    //重置对象池中的对象
    for (EnemyPlane* enemyplane : *(enemyplane_pool->enemyplane_pool_list)){
        enemyplane->destroy();
        enemyplane_pool->return_enemyplane(enemyplane);
    }
    for (EnemyBullet* enemybullet : *(enemybullet_pool->enemybullet_pool_list)){
        enemybullet->destroy();
        enemybullet_pool->return_enemybullet(enemybullet);
    }
    for (HeroBullet* herobullet : *(herobullet_pool->herobullet_pool_list)){
        herobullet->destroy();
        herobullet_pool->return_herobullet(herobullet);
    }

    //销毁英雄机
    if (heroplane1){
        level_scene->removeItem(heroplane1);
        delete heroplane1;
    }
    if (heroplane2){
        level_scene->removeItem(heroplane2);
        delete heroplane2;
    }

    //切断game_timer与update的连接
    disconnect(game_timer, nullptr, nullptr, nullptr);

}

void Widget::save_score()
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

int Widget::load_score()
{
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
