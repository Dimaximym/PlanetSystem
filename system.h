#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include <QGraphicsScene>

#include <QTimer>
#include <QDebug>
#include "planet.h"
class System : public QObject
{
    Q_OBJECT
public:
    QGraphicsScene *scene;
    QTimer *timer;

    QVector<Planet> system;
public:
    explicit System(QObject *parent = nullptr);

signals:

public slots:
    void slotTimerActivated();
};

#endif // SYSTEM_H
