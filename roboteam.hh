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

#ifndef ROBOTEAM_HH
#define ROBOTEAM_HH

#include <iostream>
#include <QGraphicsScene>
#include "soccerfield.hh"
#include "robot.hh"
#include "obs_avoidance.hh"

class ObstacleAvoidance;
class SoccerField;
class Robot;

class RoboTeam
{
public:
  RoboTeam(SoccerField *soccerField, QGraphicsScene *scene);
  void setEnemy(RoboTeam *other);
  void update();
  Robot *members[6];
private:
  SoccerField *field;
  RoboTeam *enemy;
  ObstacleAvoidance *avoidances[6];
};

#endif // ROBOTEAM_HH
