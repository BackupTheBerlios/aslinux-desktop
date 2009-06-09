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

#include <QtGui>


#include "mclient.h"
int main(int argc, char *argv[])
{
      
     Q_INIT_RESOURCE(systray);

     QApplication app(argc, argv);
     QApplication::setOrganizationName("Activa Sistemas");
     QApplication::setOrganizationDomain("activasistemas.com");
     QApplication::setApplicationName("Horde3 agent");
     
     QString durl;
     QString duser;

     if (argc>2){
	durl.append(app.argv()[1]);
     	duser.append(app.argv()[2]);
	}
     
     if (!QSystemTrayIcon::isSystemTrayAvailable()) {
         QMessageBox::critical(0, QObject::tr("Systray"),
                               QObject::tr("I couldn't detect any system tray "
                                           "on this system."));
         return 1;
     }
     QApplication::setQuitOnLastWindowClosed(false);

     //Window window;
     //window.show();

     mclient *test = new mclient();
     if (argc>2){
	test->setDuser(duser);
     	test->setDUrl(durl);
	}
     
     return app.exec();

}

