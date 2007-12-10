/***************************************************************************
                          dcoper.h  -  description
                             -------------------
    begin                : mar dic 7 2004
    copyright            : (C) 2004 by Augusto Beiro
    email                : abeiro@activasistemas.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef DCOPER_H
#define DCOPER_H

#include <qwidget.h>
#include "dcopdemoiface.h"
#include "mainWin.h"

#include <kio/job.h>
#include <kio/jobclasses.h>
#include <kio/global.h>


/**
  *@author Augusto Beiro
  */

class dcoper : public QWidget, virtual public DCOPDemoIface { 
   Q_OBJECT

public: 
  mainWin *padre;
  bool downloadFinished;
  int status;
  int errstatus;

  KIO::FileCopyJob *job;
     
  dcoper(QWidget *parent=0, const char *name=0);
	~dcoper();
public slots:
    void setSay( const QString &str );
    void setShot( const QString &str );
    void setLabel( const QString &str );
    void setTitle( const QString &str );
    void setProgreso(int p);
    void setProgresoP(unsigned  long p);

    int getStatus();
    int errStatus();
    int getFile(const QString &src, const QString &dst);

    void resetProgresoPInternal(KIO::Job *job);
    void setProgresoPInternal(KIO::Job *job, unsigned  long p);
    void slotSpeed(KIO::Job *job, unsigned  long p);
	
    int getWinId();

    void shoshow();
};

#endif
