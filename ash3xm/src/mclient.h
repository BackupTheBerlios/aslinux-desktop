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

#ifndef MCLIENT_H
#define MCLIENT_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include "ui_mclient.h"
#include "cmsgbox.h"
#include <QtGui>
#include <QDialog>
#include "client.h"

class QAction;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QPushButton;
class QSpinBox;
class QTextEdit;

struct _alarm {
	QDateTime *start;
	QString *text;
	QString *title;
	QString *user;
	QString *id;
	int checked;
};

typedef struct _alarm t_alarm;


class mclient : public QWidget, private Ui::Form
{
  Q_OBJECT

public:
  mclient(QWidget* parent = 0, Qt::WFlags fl = 0 );
  ~mclient();
  void createTrayIcon();
  void createIconGroupBox();
  void setIcon(int index);
  void setDuser(QString duser);
  void setDUrl(QString durl);
  
  /*$PUBLIC_FUNCTIONS$*/

public slots:
  /*$PUBLIC_SLOTS$*/
  void PtestAction();
  void aGo();
  void aTestParams();
  void processReturnValue( int requestId, xmlrpc::Variant value );
  void processFault( int requestId, int errorCode, QString errorString );
  void processSummary(int requestId, xmlrpc::Variant value);
  void checkUpdates();
  void showNormalC();
  void noticeAlarms();
  void updateAlarms(QLabel *id, QCheckBox *est);
  

protected:
  /*$PROTECTED_FUNCTIONS$*/

protected slots:
  /*$PROTECTED_SLOTS$*/

private:
 QSystemTrayIcon *trayIcon;
 QMenu *trayIconMenu;
 QAction *minimizeAction;
 QAction *maximizeAction;
 QAction *restoreAction;
 QAction *quitAction;

 QAction *okAction;

 QAction *testAction;

 QGroupBox *iconGroupBox;
 QLabel *iconLabel;
 QComboBox *iconComboBox;
 QCheckBox *showIconCheckBox;

 QIcon icon;
 QString dtooltip;

 QSettings settings;

 xmlrpc::Client *client;
 xmlrpc::Client *client_mail;

 QTimer *timer;

 int requestIdSum;
 int requestIdDiff;
 int idAlarm;

 QWidget *dparent;
 
 QString durl;
 QString duser;

 QMap<QString,t_alarm> Alarmas;
 

};

#endif

