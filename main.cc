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

#include <QApplication>
#include <QMainWindow>
#include "soccerfield.hh"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    SoccerField *field = new SoccerField;

    QMainWindow mainWindow;
    mainWindow.setCentralWidget(field);
    mainWindow.setWindowTitle("Robot Ball");
    mainWindow.setStyleSheet("background-color: #e8e8e8;");
    mainWindow.showFullScreen();

    return app.exec();
}
