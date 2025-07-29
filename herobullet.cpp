#include "herobullet.h"

HeroBullet::HeroBullet()
{

}

void HeroBullet::init(int bullet_kind)
{
    this->bullet_kind = bullet_kind;
    switch(bullet_kind){
    case 1:
        init1();
        break;
    case 2:
        init2();
        break;
    case 3:
        init3();
        break;
    case 4:
        init4();
        break;
    }
}

void HeroBullet::init1()
{
    setPixmap(QPixmap(HEROBULLET_PICTURE1));
}

void HeroBullet::init2()
{

}

void HeroBullet::init3()
{

}

void HeroBullet::init4()
{

}
