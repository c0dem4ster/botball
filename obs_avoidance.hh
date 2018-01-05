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

#ifndef OBS_AVOIDANCE_HH
#define OBS_AVOIDANCE_HH

#include <math.h>
#include <QGraphicsItem>
#include "soccerfield.hh"
#include "robot.hh"

//waypoint distance
#define waypoint_distance 100

//number of obstacles
#define obstacle_quantity 5

//minimum distance between robots
#define minimum_distance 500

//soccer field area
#define field_height 6000
#define field_width 9000

class SoccerField;
class Robot;

class ObstacleAvoidance : public QGraphicsItem
{
public:
  ObstacleAvoidance(SoccerField *soccerField);
  // calculate waypoints
  void calculateTrajectory(QPointF start, QPointF end, Robot *obs[obstacle_quantity]);

  enum { Type = UserType + 1 };
  int type() const override { return Type; }
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
  // distance between robot's position and given point
  float getDistance(QPointF pt0, QPointF pt1);
  // repulsion force from obstacle with index cobs
  QPointF calculateRepulsion(int cobs);
  // array of obstacles
  Robot **obstacles;
  // our final position
  QPointF finalPosition;
  // current position
  QPointF currentPosition;
  // generated waypoints of our trajectory
  QPointF waypoints[10000];
  // number of waypoints
  int waypointQuantity;
  SoccerField *graph;
};

#endif // OBS_AVOIDANCE_HH
