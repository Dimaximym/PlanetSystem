#ifndef PLANET_H
#define PLANET_H

#include <QGraphicsItem>

class Planet
{
public:
    QGraphicsEllipseItem *planet;
    //характеристики тела
    int mass;
    //параметры тела в данный момент
    double vx, vy;
public:
    explicit Planet();
    //x, y, mass, rad, ?vy
    Planet(int x, int y, int _mass, int rad = 10, double _vy = 0.1);
    ~Planet();
signals:

public slots:
};

#endif // PLANET_H
