/*
 * Robot Ball Simulation Software corresponding to the official SSL-Rules
 *                Copyright (C) 2018  Theodor Fragner
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SOCCERFIELD_HH
#define SOCCERFIELD_HH

#include <iostream>
#include <QGraphicsView>
#include <QWheelEvent>
#include "roboteam.hh"

class RoboTeam;

class SoccerField : public QGraphicsView
{
    Q_OBJECT

public:
    SoccerField(QWidget *parent = 0);

protected:
    void timerEvent(QTimerEvent *event) override;
#ifndef QT_NO_WHEELEVENT
    void wheelEvent(QWheelEvent *event) override;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void scaleView(qreal scaleFactor);

private:
    int timerId;
    RoboTeam *ouRoboTeam;
    //RoboTeam *otheRoboTeam;
};

#endif // SOCCERFIELD_HH
