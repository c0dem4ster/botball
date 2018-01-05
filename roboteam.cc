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

#include "roboteam.hh"

RoboTeam::RoboTeam(SoccerField *soccerField, QGraphicsScene *scene)
{
  field = soccerField;
  for(int i=0; i<6; i++)
    {
      avoidances[i] = new ObstacleAvoidance(field);
      members[i] = new Robot(field);
      scene->addItem(avoidances[i]);
      scene->addItem(members[i]);
    }
  members[0]->setPos(-4000,  2000);
  members[1]->setPos( 1000,     0);
  members[2]->setPos( 2000, -1000);
  members[3]->setPos(-2000,  1000);
  members[4]->setPos(    0,  1000);
  members[5]->setPos(-1000,     0);
}

void RoboTeam::setEnemy(RoboTeam *other)
{
  enemy = other;
}

void RoboTeam::update()
{
  for(int i=0; i<5; i++)
    {
      members[i]->constrainArea();
      members[i]->update();
    }
  double initialTime = clock();
  avoidances[0]->calculateTrajectory(members[0]->pos(), QPointF(4000, -2000), members+1);
  std::cout << "calculation time: " << (clock()-initialTime)*1000/CLOCKS_PER_SEC << " ms" << std::endl;
  avoidances[0]->update();
}
