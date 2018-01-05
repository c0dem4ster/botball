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

#include "soccerfield.hh"

SoccerField::SoccerField(QWidget *parent)
  : QGraphicsView(parent), timerId(0)
{
  QGraphicsScene *scene = new QGraphicsScene(this);
  scene->setItemIndexMethod(QGraphicsScene::NoIndex);
  scene->setSceneRect(-4500, -3000, 9000, 6000);
  setScene(scene);
  setCacheMode(CacheBackground);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  scale(qreal(0.2), qreal(0.2));

  ouRoboTeam = new RoboTeam(this, scene);
  //otheRoboTeam = new RoboTeam(this, scene);

  timerId = startTimer(1000 / 100);
}

void SoccerField::timerEvent(QTimerEvent *event)
{
  double initialTime = clock();
  ouRoboTeam->update();
  std::cout << "update time: " << (clock()-initialTime)*1000/CLOCKS_PER_SEC << " ms" << std::endl;
  Q_UNUSED(event);
}

#ifndef QT_NO_WHEELEVENT
void SoccerField::wheelEvent(QWheelEvent *event)
{
  scaleView(pow(2, event->delta() / 240.0));
}
#endif

void SoccerField::drawBackground(QPainter *painter, const QRectF &rect)
{
  QRectF sceneRect = this->sceneRect();
  QPointF center = sceneRect.center();
  painter->setPen(QPen(Qt::white, 40, Qt::SolidLine, Qt::FlatCap));
  int lineWidth = painter->pen().width();

  // shadow
  painter->fillRect(rect.intersected(QRectF(sceneRect.right(), sceneRect.top() + 50, 50, sceneRect.height())), Qt::darkGray);
  painter->fillRect(rect.intersected(QRectF(sceneRect.left() + 50, sceneRect.bottom(), sceneRect.width(), 50)), Qt::darkGray);

  // background
  painter->fillRect(rect.intersected(sceneRect), Qt::white);
  painter->fillRect(sceneRect.marginsRemoved(QMarginsF(lineWidth, lineWidth, lineWidth, lineWidth)), QColor(0x43, 0x55, 0x1F));

  // lines
  painter->drawLine(center.x(), sceneRect.top(), center.x(), sceneRect.bottom());
  painter->drawLine(sceneRect.left(), center.y(), sceneRect.right(), center.y());
  painter->drawArc(QRectF(sceneRect.left()-1000, center.y()-1250, 2000, 2000), 0, 90*16);
  painter->drawArc(QRectF(sceneRect.left()-1000, center.y()-750, 2000, 2000), 270*16, 90*16);
  painter->drawLine(sceneRect.left()+1000, center.y()-250, sceneRect.left()+1000, center.y()+250);
  painter->drawArc(QRectF(sceneRect.right()-1000, center.y()-1250, 2000, 2000), 90*16, 90*16);
  painter->drawArc(QRectF(sceneRect.right()-1000, center.y()-750, 2000, 2000), 180*16, 90*16);
  painter->drawLine(sceneRect.right()-1000, center.y()-250, sceneRect.right()-1000, center.y()+250);
  painter->drawEllipse(center, 1000, 1000);
}

void SoccerField::scaleView(qreal scaleFactor)
{
  qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
  if (factor < 0.07 || factor > 100)
    return;

  scale(scaleFactor, scaleFactor);
}
