/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/
#include <qmovie.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qprogressbar.h>


#include <kio/job.h>
#include <kio/jobclasses.h>
#include <kio/global.h>


void mainWin::init( )
{
    /*QMovie *anim;
    anim=new QMovie("/usr/lib/asinstaller/pics/install.gif");
    this->animation->setMovie(*anim);*/
}

void mainWin::setLey( const QString &str )
{
	this->Ley->setText(str);
}
void mainWin::setSay( const QString &str )
{
	this->say->setText(str);
}

void mainWin::setTitle( const QString &str )
{
	this->setCaption(str);
	
}

void mainWin::setShot( const QString &str )
{
    QPixmap *shot;
    shot=new QPixmap(str);
    this->shot->setPixmap(*shot);
}
void mainWin::setProgreso( int p)
{
    this->progreso->setProgress(p);
}


void mainWin::setProgresoP( int p)
{
    this->progreso2->setProgress(p);
}

void mainWin::setSpeed( unsigned long  p)
{
    QString *dnum=new QString();
    QString dnumber=dnum->setNum((float)((float)p/(float)1024));
    if (p!=0) 
    this->speedLabel->setText(QString("Velocidad de transferencia: ") + dnumber + QString(" Kb/s"));
    else
	this->speedLabel->setText("");

}
