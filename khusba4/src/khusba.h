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
#ifndef KHUSBA_H
#define KHUSBA_H

#include <QObject>
#include <QtDBus/QtDBus>
#include <QtNetwork/QtNetwork>

/**
	@author Augusto Beiro <abeiro@activasistemas.com>
*/
class khusba : public QObject
{
Q_OBJECT
public:
    khusba(QObject *parent = 0);

    ~khusba();
private slots:
     void messageSlot(const QString &text);
     void recMoreInfo(const QDBusMessage &rep);
     void recError(const QDBusError &err,const QDBusMessage &rep);
     void requestMoreInfoSlot(uint uid,const QString &text);

};

#endif
