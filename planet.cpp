#include "planet.h"

Planet::Planet()// : QObject(parent)
{
    planet = new QGraphicsEllipseItem;
}

Planet::Planet(int x, int y, int _mass, int rad, double _vy)// : QObject(parent)
{
    planet = new QGraphicsEllipseItem(0,0,rad,rad);
    planet->setPos(x, y);
    mass = _mass;
    vy = _vy;
    vx = 0;
}

Planet::~Planet() {
    //???завершает процесс - программа неожиданно
    //завершилась???
    //delete planet;
}

