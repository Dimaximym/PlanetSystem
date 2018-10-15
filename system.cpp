#include "system.h"

System::System(QObject *parent) : QObject(parent) {
    scene = new QGraphicsScene;
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()),
            this, SLOT(slotTimerActivated()));

    system.push_back(Planet(0, 0, 2000, 20, 0));
    scene->addItem(system.back().planet);

    system.push_back(Planet(-100, 0, 10, 10));
    scene->addItem(system.back().planet);




    system.push_back(Planet(-150, 0, 15, 10));
    scene->addItem(system.back().planet);

    system.push_back(Planet(-200, 0, 100, 10));
    scene->addItem(system.back().planet);

    system.push_back(Planet(-230, 0, 5, 2));
    scene->addItem(system.back().planet);

    timer->start(1);
}

void System::slotTimerActivated() {
    for (int i = 0; i < system.size(); ++i) {
        QGraphicsEllipseItem *p0 = system[i].planet;

//        auto collisionList = scene->collidingItems(p0);
//        bool collision = !collisionList.isEmpty();
//        bool find = false;
//        if (collision) {
//            for (int k = 0; k <= system.size(); ++k) {
//                if (system[k].planet == collisionList.front() &&
//                    system[k].mass < system[i].mass &&
//                    i != k) {
//                    scene->removeItem(system[k].planet);
//                    system.erase(system.begin() + k);
//                    find = true;
//                    break;
//                }
//            }
//            if (!find) {
//                scene->removeItem(p0);
//                system.erase(system.begin() + i);
//                continue;
//            }
//        }
        for (int j = 0; j < system.size(); ++j) {
            if (j == i) continue;
            QGraphicsEllipseItem *p = system[j].planet;
            double d = sqrt((p0->x() - p->x()) * (p0->x() - p->x()) +
                           (p0->y() - p->y()) * (p0->y() - p->y()));
            if (d > 3) {
                system[i].vx += 0.0007 * system[j].mass / d / d
                        * (p->x() - p0->x()) / d;
                system[i].vy += 0.0007 * system[j].mass / d / d
                        * (p->y() - p0->y()) / d;
            }
        }
        p0->setPos(p0->x() + system[i].vx, p0->y() + system[i].vy);

//        qDebug() << "x = " << p0->x() << " y = " <<  p0->y();
    }
}
