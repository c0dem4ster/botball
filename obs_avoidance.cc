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

#include "obs_avoidance.hh"

ObstacleAvoidance::ObstacleAvoidance(SoccerField *soccerField)
  : graph(soccerField)
{
  setCacheMode(DeviceCoordinateCache);
  setZValue(-1);
}

void ObstacleAvoidance::calculateTrajectory(QPointF start, QPointF end, Robot *obs[obstacle_quantity])
{
  obstacles = obs;
  currentPosition = start;
  finalPosition = end;
  waypointQuantity = 0;
  QPointF movement;
  float distance = getDistance(currentPosition, finalPosition);
  while(distance > waypoint_distance)
  {
    distance = getDistance(currentPosition, finalPosition);
    waypoints[waypointQuantity] = currentPosition;
    movement = ((finalPosition-currentPosition)*20/distance);
    for(int i=0; i<obstacle_quantity; i++) movement += calculateRepulsion(i);
    currentPosition += movement*waypoint_distance/getDistance(QPointF(0, 0), movement);
    waypointQuantity++;
    if(waypointQuantity == 9999) distance=0;
  }
  waypoints[waypointQuantity] = currentPosition;
}

QRectF ObstacleAvoidance::boundingRect() const
{
  return QRectF(-4500, -3000, 9000, 6000);
}

void ObstacleAvoidance::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  painter->setPen(QPen(Qt::black, 10));
  for(int currentWaypoint = 0; currentWaypoint < waypointQuantity; currentWaypoint++)
    painter->drawLine(waypoints[currentWaypoint], waypoints[currentWaypoint+1]);
  Q_UNUSED(option);
  Q_UNUSED(widget);
}

float ObstacleAvoidance::getDistance(QPointF pt0, QPointF pt1)
{
  return sqrt(pow(pt0.x()-pt1.x(), 2)+pow(pt0.y()-pt1.y(), 2));
}

QPointF ObstacleAvoidance::calculateRepulsion(int cobs)
{
  float obstacleDistance = getDistance(currentPosition, obstacles[cobs]->pos());
  float finalDistance = getDistance(currentPosition, finalPosition);
  QPointF repulsion;

  if(obstacleDistance < (3*minimum_distance))
  {
    float repmodel = (obstacleDistance/minimum_distance-3)*(obstacleDistance/minimum_distance-3);
    int fac = 1;

    repulsion.setX((((currentPosition.x()-obstacles[cobs]->x())/obstacleDistance))*repmodel);
    repulsion.setY((((currentPosition.y()-obstacles[cobs]->y())/obstacleDistance))*repmodel);

    repmodel *= 2;
    if(((obstacles[cobs]->x()-currentPosition.x())*(finalPosition.y()-currentPosition.y())-(obstacles[cobs]->y()-currentPosition.y())*(finalPosition.x()-currentPosition.x()))>0)
    {
      fac = -1;
    }
    repulsion.setX(repulsion.x() + fac*((finalPosition.y()-currentPosition.y())/finalDistance)*repmodel);
    repulsion.setY(repulsion.y() - fac*((finalPosition.x()-currentPosition.x())/finalDistance)*repmodel);
  }
  else
  {
    repulsion.setX(0);
    repulsion.setY(0);
  }
  return repulsion;
}
