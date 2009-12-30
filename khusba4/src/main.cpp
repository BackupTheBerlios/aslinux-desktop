/***************************************************************************
 *   Copyright (C) 2009 by Augusto Beiro   *
 *   abeiro@activasistemas.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/


#include <QtCore/QCoreApplication>
#include <QtDBus/QtDBus>
#include "khusba.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
      QCoreApplication app(argc, argv);
      qDebug("Hello from Qt 4!");
      if (!QDBusConnection::systemBus().isConnected()) {
         qWarning("Cannot connect to the D-Bus session bus.\n"
                  "Please check your system settings and try again.\n");
         return 1;
     }
     khusba *mainw=new khusba(NULL);
     return app.exec();
}

