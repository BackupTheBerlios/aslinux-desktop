/***************************************************************************
                          dcopdemoiface.h  -  description
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

#ifndef DCOPDEMOIFACE_H
#define DCOPDEMOIFACE_H

#include <dcopobject.h>

/**
  *@author Augusto Beiro
  */

class DCOPDemoIface : virtual public DCOPObject  {
  K_DCOP
  k_dcop:

  virtual void setLabel(const QString &str)=0;
  virtual void setSay(const QString &str)=0;
  virtual void setShot(const QString &str)=0;
  virtual void setTitle(const QString &str)=0;
  virtual void setProgreso(int p)=0;
  virtual void setProgresoP(unsigned  long p)=0;
  virtual int getFile(const QString &src,const QString &dst)=0;
 
  virtual int getStatus()=0;
  virtual int errStatus()=0;

  virtual int getWinId()=0;

  virtual void shoshow()=0;


};


#endif
