/***************************************************************************
                          dcoper.cpp  -  description
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

#include "dcoper.h"
#include <kapp.h>
#include <dcopclient.h>
#include "mainWin.h"
#include <stdio.h>



dcoper::dcoper(QWidget *parent, const char *name ) : QWidget(parent,name), DCOPObject( "dcoper" ) {

  QCString  appIdef;
  padre=(mainWin *)parent->parent();
 if ( !kapp->dcopClient()->isRegistered() ) {
          kapp->dcopClient()->registerAs( "dcoper" );
          kapp->dcopClient()->setDefaultObject( objId() );
 }
  appIdef=kapp->dcopClient()->appId();

  downloadFinished=true;
  status=0;
  errstatus=0;
  printf("%s\n",appIdef.data());
}
dcoper::~dcoper(){
}

void dcoper::setLabel(const QString &str) {

    padre->setLey(str);
}

void dcoper::setSay(const QString &str) {

    padre->setSay(str);
}

void dcoper::setTitle(const QString &str) {

    padre->setTitle(str);
}

void dcoper::setShot(const QString &str) {

    padre->setShot(str);
}
void dcoper::setProgreso(int p) {

    padre->setProgreso(p);
}
void dcoper::setProgresoP(unsigned  long p) {
    padre->setProgresoP((int)p);
}

void dcoper::setProgresoPInternal(KIO::Job *job, unsigned  long p) {
    if (job->error())
	errstatus=job->error();
    padre->setProgresoP((int)p);
}

void dcoper::resetProgresoPInternal(KIO::Job *job) {

    
    downloadFinished=true;
    //padre->setProgresoP(0);
    status=0; 
    
}

void  dcoper::slotSpeed(KIO::Job *job, unsigned  long p) {

	
	//printf("Speed %.2f (Kb/s)\n",(float)((float)p/(float)1024));
	padre->setSpeed(p);
}

int dcoper::errStatus() {

    return errstatus;
    
}

int dcoper::getStatus() {

    
    return status;
    
}

void dcoper::shoshow() { 

	padre->show();
}

int dcoper::getFile(const QString &src, const QString &dst) {

	if (downloadFinished==true) {
		status=1;
		errstatus=0;
		downloadFinished=false;
		job = KIO::file_copy(KURL(src),KURL(dst),-1,true,false,false);
		connect(job, SIGNAL(percent (KIO::Job *,unsigned  long)),SLOT(setProgresoPInternal(KIO::Job *,unsigned  long)));
	        connect(job, SIGNAL( speed( KIO::Job *, unsigned long )), SLOT(slotSpeed(KIO::Job *, unsigned long ) ) );
		connect(job, SIGNAL(result (KIO::Job *)),SLOT(resetProgresoPInternal(KIO::Job *)));
		return 0; 
	}
	else
		return -1;
	
	

}


int dcoper::getWinId() {

    return getWinId();
}

