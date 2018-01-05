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

#include "robot.hh"

Robot::Robot(SoccerField *soccerField)
  : field(soccerField)
{
  setFlag(ItemIsMovable);
  setCacheMode(DeviceCoordinateCache);
}

bool Robot::constrainArea()
{
  QRectF sceneRect = scene()->sceneRect();
  newPos.setX(qMin(qMax(pos().x(), sceneRect.left() + 90), sceneRect.right() - 90));
  newPos.setY(qMin(qMax(pos().y(), sceneRect.top() + 90), sceneRect.bottom() - 90));

  if (newPos == pos())
    return false;

  setPos(newPos);
  return true;
}

QRectF Robot::boundingRect() const
{
  qreal adjust = 2;
  return QRectF( -100 - adjust, -100 - adjust, 230 + adjust, 230 + adjust);
}

QPainterPath Robot::shape() const
{
  QPainterPath path;
  path.addEllipse(-90, -90, 180, 180);
  return path;
}

void Robot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
  painter->setPen(Qt::NoPen);
  painter->setBrush(Qt::black);
  painter->drawEllipse(-70, -70, 180, 180);

  QRadialGradient gradient(-30, -30, 100);
  if (option->state & QStyle::State_Sunken)
    {
      gradient.setCenter(30, 30);
      gradient.setFocalPoint(30, 30);
      gradient.setColorAt(1, QColor(0x80, 0x80, 0x80).light(120));
      gradient.setColorAt(0, QColor(0x60, 0x60, 0x60).light(120));
    }
  else
    {
      gradient.setColorAt(0, QColor(0x80, 0x80, 0x80));
      gradient.setColorAt(1, QColor(0x60, 0x60, 0x60));
    }
  painter->setBrush(gradient);

  painter->setPen(QPen(Qt::black, 0));
  painter->drawEllipse(-90, -90, 180, 180);
}

void Robot::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  update();
  QGraphicsItem::mousePressEvent(event);
}

void Robot::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  update();
  QGraphicsItem::mouseReleaseEvent(event);
}
