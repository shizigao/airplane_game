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

    load_heroplane();
    load_sound();
    load_levels();
    //load_object_pool();
    load_timer();
    load_startgame();
    load_menu();

    load_pause();
}

void Widget::load_timer()
{
    game_timer = new QTimer(this);
    game_timer->start(GAME_PERIOD);
    heroplane1_weapon1_timer = new QTimer(this);
    heroplane1_weapon2_timer = new QTimer(this);
    heroplane1_weapon3_timer = new QTimer(this);
    heroplane2_weapon1_timer = new QTimer(this);
    heroplane2_weapon2_timer = new QTimer(this);
    heroplane2_weapon3_timer = new QTimer(this);
}

void Widget::load_sound()
{
    backgroundMusic = new QMediaPlayer(this);

    // 设置音乐文件路径（支持本地文件和网络地址）
    backgroundMusic->setMedia(QUrl("qrc:/bg.wav"));

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
        HeroBullet* herobullet = new HeroBullet(0, 0, QPixmap(HEROBULLET_PICTURE1));
        herobullet->status = 1;
        herobullet_pool.append(herobullet);
        herobullet_queue.append(herobullet);
        herobullet->setVisible(false);
        level_scene.addItem(herobullet);
    }
    //创建10颗敌方子弹
    for (int i = 0; i < 10; i++){
        EnemyBullet* enemybullet = new EnemyBullet(0, 0, QPixmap(ENEMYBULLET_PICTURE1));
        enemybullet->status = 1;
        enemybullet_pool.append(enemybullet);
        enemybullet_queue.append(enemybullet);
        enemybullet->setVisible(false);
        level_scene.addItem(enemybullet);
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
    player1_healthBar = new QProgressBar();
    player1_healthBar->setFixedSize(60, 200);
    player1_healthBar->move(VIEW_WIDTH - 40, VIEW_HEIGHT - 200);
    player1_healthBar->setValue(100);
    player1_healthBar->setTextVisible(false);//生命值比率不可见，用生命值属性替代
    player1_healthBar->setStyleSheet("QProgressBar::chunk {"
                                     "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
                                     "                               stop:0 #92FF77, "
                                     "                               stop:1 #FF2626);"
                                     "}");
    player1_healthBar->setOrientation(Qt::Vertical);//设置生命条垂直
    player1_healthBar->setVisible(false);
    level_scene.addWidget(player1_healthBar);

    player1_healthValue = new QLineEdit();
    player1_healthValue->setText("233");
    player1_healthValue->setReadOnly(true);
    player1_healthValue->move(VIEW_WIDTH - 40, VIEW_HEIGHT - 125);
    player1_healthValue->setStyleSheet(R"(
                                       QLineEdit:read-only {
                                           font-family: "Arial Black";  /* 字体家族 */
                                           font-size: 20px;            /* 字体大小 */
                                       font-weight: bold;
                                           background-color: transparent;
                                           border: none;  /* 可选：去掉边框 */
                                           color: #FF0B0B;   /* 文字颜色 */
                                       }
                                   )");
    player1_healthValue->setVisible(false);
    level_scene.addWidget(player1_healthValue);



    //加载武器背景
    player1_weapon1_background = new QGraphicsPixmapItem();
    player1_weapon1_background->setPixmap(QPixmap(WEAPON_BACKGROUND));
    player1_weapon1_background->setScale(0.12);
    player1_weapon1_background->setPos(VIEW_WIDTH - 100, VIEW_HEIGHT - 200);
    player1_weapon1_background->setVisible(false);
    level_scene.addItem(player1_weapon1_background);

    player1_weapon2_background = new QGraphicsPixmapItem();
    player1_weapon2_background->setPixmap(QPixmap(WEAPON_BACKGROUND));
    player1_weapon2_background->setScale(0.12);
    player1_weapon2_background->setPos(VIEW_WIDTH - 100, VIEW_HEIGHT - 140);
    player1_weapon2_background->setVisible(false);
    level_scene.addItem(player1_weapon2_background);

    player1_weapon3_background = new QGraphicsPixmapItem();
    player1_weapon3_background->setPixmap(QPixmap(WEAPON_BACKGROUND));
    player1_weapon3_background->setScale(0.12);
    player1_weapon3_background->setPos(VIEW_WIDTH - 100, VIEW_HEIGHT - 80);
    player1_weapon3_background->setVisible(false);
    level_scene.addItem(player1_weapon3_background);

    player1_weapon4_background = new QGraphicsPixmapItem();
    player1_weapon4_background->setPixmap(QPixmap(WEAPON_BACKGROUND));
    player1_weapon4_background->setScale(0.12);
    player1_weapon4_background->setPos(VIEW_WIDTH - 160, VIEW_HEIGHT - 80);
    player1_weapon4_background->setVisible(false);
    level_scene.addItem(player1_weapon4_background);



    //加载得分
    score = new QLineEdit();
    score->setText("得分：114514");
    score->setReadOnly(true);
    score->move(VIEW_WIDTH - 160, 0);
    score->setVisible(false);
    level_scene.addWidget(score);
    score->setStyleSheet(R"(
                                 QLineEdit:read-only {
                                     font-family: "Arial Black";  /* 字体家族 */
                                     font-size: 18px;            /* 字体大小 */
                                 font-weight: bold;
                                     background-color: transparent;
                                     border: none;  /* 可选：去掉边框 */
                                     color: #FF0B0B;   /* 文字颜色 */
                                 }
                             )");

      //加载英雄机
    level_scene.addItem(heroplane1);
}
//加载英雄机资源
void Widget::load_heroplane()
{
    heroplane1 = new HeroPlane(300, 1000, QPixmap(HEROPLANE_1));
    heroplane2 = new HeroPlane(600, 1000, QPixmap(HEROPLANE_2));
}

void Widget::load_weapon1(HeroWeapon *heroweapon)
{
    heroweapon->setScale(0.4);
    heroweapon->setPos(VIEW_WIDTH - 101, VIEW_HEIGHT - 200);
    level_scene.addItem(heroweapon);
}

void Widget::load_weapon2(HeroWeapon *heroweapon)
{
    heroweapon->setScale(0.4);
    heroweapon->setPos(VIEW_WIDTH - 101, VIEW_HEIGHT - 140);
    level_scene.addItem(heroweapon);
}

void Widget::load_weapon3(HeroWeapon *heroweapon)
{
    heroweapon->setScale(0.4);
    heroweapon->setPos(VIEW_WIDTH - 101, VIEW_HEIGHT - 80);
    level_scene.addItem(heroweapon);
}

//转到菜单页面
void Widget::turn_to_menu()
{
    main_view.setScene(&main_scene2);
}

//转到第一关
void Widget::turn_to_level1()
{
    main_view.setScene(&level_scene);//将视图对准第一关场景

    //将需要的组件可视化
    level_1_background1->setVisible(true);
    level_1_background2->setVisible(true);
    player1_healthBar->setVisible(true);
    player1_healthValue->setVisible(true);
    score->setVisible(true);
    level_progressBar->setVisible(true);
    player1_weapon1_background->setVisible(true);
    player1_weapon2_background->setVisible(true);
    player1_weapon3_background->setVisible(true);
    player1_weapon4_background->setVisible(true);

    //为玩家1配置初始武器
    heroplane1->weapon1 = new HeroWeapon();
    heroplane1->weapon1->init(1);//初始化为第一种武器
    load_weapon1(heroplane1->weapon1);//加载武器图标
    //为武器1设置计时器
    heroplane1_weapon1_timer->start(heroplane1->weapon1->interval);
    connect(heroplane1_weapon1_timer, QTimer::timeout, this, [=](){
        heroplane1->weapon1->is_ready = true;
    });
    //设置计时器与第一关场景之间的信号槽
    connect(game_timer, QTimer::timeout, this, level_1_update);

}

//键盘控制英雄机移动
void Widget::heroplane_move2(HeroPlane* heroplane)
{
    int x = heroplane->pos().x();
    int y = heroplane->pos().y();
    int delta_x = 0, delta_y = 0;
    int step = 0;
    for (int keyCode : keylist){
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
    if (step == 1){
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
void Widget::heroplane_move1()
{
    double x = heroplane1->pos().x();
    double y = heroplane1->pos().y();
    QPoint point = QCursor::pos();
    QPoint local_point = mapFromGlobal(point);
    int px = local_point.x(), py = local_point.y();
    int rect_x = heroplane1->rect.width() / 2, rect_y = heroplane1->rect.height() / 2;//飞机在x轴和y轴上的移动比率（模拟按直线接近鼠标位置）
    int cx = x + rect_x, cy = y + rect_y;//飞机中心坐标
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

void Widget::level_1_update()
{
   
    //场景移动    
    level_1_background1->setY(level_1_background1->y() + 1);
    if (level_1_background1->y() >= 1229){
        level_1_background1->setY(0);
    }
    level_1_background2->setY(level_1_background2->y() + 1);
    if (level_1_background2->y() >= 0){
        level_1_background2->setY(-1229);
    }
    
    //第一种敌机每2秒随机在屏幕上方生成
    static int count = 0;//单位:ms
    count += GAME_PERIOD;
    if (count == 2000){
        int x = rand()%668, y = -100;
        EnemyPlane* new_enemyplane = get_enemyplane(x, y, 1);
        count = 0;
    }
    
    
    
    //英雄机位置更新
    if (move_mode == 1){
        heroplane_move1();
    }
    else{
        heroplane_move2(heroplane1);
    }

    //游戏通用更新函数
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
    case Qt::Key_W:
    case Qt::Key_D:
    case Qt::Key_A:
    case Qt::Key_S:
        if (move_mode == 1)return;
        keylist.append(event->key());
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
    case Qt::Key_W:
    case Qt::Key_D:
    case Qt::Key_A:
    case Qt::Key_S:
        if (move_mode == 1)return;
        keylist.removeOne(event->key());
        break;
    }


}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton && keylist.empty()){
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
}

void Widget::enemyplane_shoot(EnemyPlane *enemyplane)
{
    EnemyBullet* new_enemybullet;
    double x = enemyplane->pos().x() + enemyplane->pixmap().width() / 2;
    double y = enemyplane->pos().y() + enemyplane->pixmap().height();
    new_enemybullet = get_enemybullet(x, y, enemyplane->weapon->weapon_kind);
    new_enemybullet->set_value(enemyplane->weapon);
}

void Widget::collision_detection()
{
    collision_detection_herobullet_with_enemyplane();
    collision_detection_enemybullet_with_heroplane();
    collision_detection_heroplane_with_enemyplane();
}

void Widget::collision_detection_herobullet_with_enemyplane()
{

}

void Widget::collision_detection_enemybullet_with_heroplane()
{

}

void Widget::collision_detection_heroplane_with_enemyplane()
{

}

//游戏更新函数
void Widget::game_update()
{
    //三个对象池中的对象的移动和检测

    //敌机池
    for (EnemyPlane* enemyplane : enemyplane_pool){
        if (enemyplane->status == 2){//status为2则移动
            enemyplane->move();
            enemyplane->is_live();//判断敌机是否还存活
        }
        else if (enemyplane->status == 0){//status为0则加入队列中
            enemyplane_queue.append(enemyplane);
            enemyplane->status = 1;
            enemyplane->weapon_timer->stop();//停止计时器
        }
    }

    //敌机子弹池
    for (EnemyBullet* enemybullet : enemybullet_pool){
        if (enemybullet->status == 2){
            enemybullet->move();
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
            herobullet->move();
            herobullet->is_live();
        }
        else if (herobullet->status == 0){
            herobullet_queue.append(herobullet);
            herobullet->status = 1;
        }
    }

    //持续开火检测
    if (heroplane1->weapon1 != nullptr && heroplane1_weapon1_continuous_firing){//要先判断对应武器是否已获得（已初始化）
        heroplane1_shoot_1();
    }
    if (heroplane1->weapon2 != nullptr && heroplane1_weapon2_continuous_firing){
        heroplane1_shoot_2();
    }
    if (heroplane1->weapon3 != nullptr && heroplane1_weapon3_continuous_firing){
        heroplane1_shoot_3();
    }
}



