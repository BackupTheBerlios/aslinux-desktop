/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : mar dic  7 11:07:55 CET 2004
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

#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <klocale.h>
#include <kapp.h>

#include "mainWin.h"

#include <sys/types.h> 
#include <unistd.h> 

static const char *description =
	I18N_NOOP("Poof2");
// INSERT A DESCRIPTION FOR YOUR APPLICATION HERE
	
	
static KCmdLineOptions options[] =
{
  { 0, 0, 0 }
  // INSERT YOUR COMMANDLINE OPTIONS HERE
};

int main(int argc, char *argv[])
{

  KAboutData aboutData( "poof2", I18N_NOOP("Poof2"),
    "0.1", description, KAboutData::License_GPL,
    "(c) 2004, Augusto Beiro", 0, 0, "abeiro@activasistemas.com");
  aboutData.addAuthor("Augusto Beiro",0, "abeiro@activasistemas.com");
  KCmdLineArgs::init( argc, argv, &aboutData );
  KCmdLineArgs::addCmdLineOptions( options ); // Add our own options.

  KApplication a;

  pid_t tenedor;
 
  mainWin *poof2 = new mainWin();
  


  a.setMainWidget(poof2);
  
  int wxx=poof2->width();
  int hxx=poof2->height();

  

  QWidget* tmp = QApplication::desktop();
  poof2->setGeometry(tmp->width()/2-(wxx/2),tmp->height()/2-(hxx/2),wxx, hxx);

  //poof2->show();

 return a.exec();
 
}
