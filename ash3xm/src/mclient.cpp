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


#include "mclient.h"
#include "response.h"
#define I_NORMAL 0
#define I_MSG 1
#define I_MSG2 2
#define I_MSG3 3
#define I_ERROR 4



mclient::mclient(QWidget* parent, Qt::WFlags fl)
: QWidget( parent, fl ), Ui::Form()
{
	setupUi(this);
	dparent=parent;
	createTrayIcon();
	setIcon(I_NORMAL);
        trayIcon->show();

	/* Cargando valores por defecto */
	textURL->setText(settings.value("url").toString());
	textUser->setText(settings.value("user").toString());
	textPass->setText(settings.value("password").toString());
	intervalo->setValue(settings.value("intervalo").toInt());
	if (intervalo->value()==0) {
		intervalo->setValue(60);
	}
	intervalo->setSuffix( " seg" );
	calendar_id->addItems(settings.value("calendarios").toStringList ());
	calendar_id-> setCurrentIndex ( settings.value("calendar_id").toInt());
	


	/* Creamos clientes XML-RPC */
	client = new xmlrpc::Client(this);
	connect( client, SIGNAL(done( int, xmlrpc::Variant )),
             this, SLOT(processReturnValue( int, xmlrpc::Variant )) );
    	connect( client, SIGNAL(failed( int, int, QString )),
             this, SLOT(processFault( int, int, QString )) );

	/* Creamos clientes XML-RPC para el emial checker*/
	client_mail = new xmlrpc::Client(this);
	connect( client_mail, SIGNAL(done( int, xmlrpc::Variant )),
             this, SLOT(processSummary( int, xmlrpc::Variant )) );
    	connect( client_mail, SIGNAL(failed( int, int, QString )),
             this, SLOT(processFault( int, int, QString )) );

	if ((textUser->text().length()==0)&&(textPass->text().length()==0)) 
		show();
	else
		aGo();

}

mclient::~mclient()
{
}

/*$SPECIALIZATION$*/

void mclient::createTrayIcon()
 {

     minimizeAction = new QAction(tr("Mi&nimizar"), this);
     connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

     
     restoreAction = new QAction(tr("&Restaurar"), this);
     connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormalC()));

     quitAction = new QAction(tr("&Cerrar"), this);
     connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

     /*connect(quitAction, SIGNAL(triggered()), qApp, SLOT(PtestAction()));

     connect(quitAction, SIGNAL(triggered()), qApp, SLOT(PtestAction()));
*/

     trayIconMenu = new QMenu(this);
     
     trayIconMenu->addAction(minimizeAction);
     trayIconMenu->addAction(restoreAction);
     trayIconMenu->addSeparator();
     trayIconMenu->addAction(quitAction);

     trayIcon = new QSystemTrayIcon(this);

     trayIcon->setContextMenu(trayIconMenu);
     
 }

 void mclient::createIconGroupBox()
 {
     
	return ;
     
 }

 void mclient::setIcon(int index)
 {
     
    
     switch (index) {
	case I_NORMAL:
			icon=QIcon(":/images/bad.png");
			dtooltip=QString("Sin avisos");
       			break;
	case I_MSG:
			icon=QIcon(":/images/trash.png");
			dtooltip=QString("Avisos pendientes");
       			break;
	default:
			icon=QIcon(":/images/bad.png");
			dtooltip=QString("Todo normal");
			break;
     }

     trayIcon->setIcon(icon);
     setWindowIcon(icon);
     trayIcon->setToolTip(dtooltip);

 }

void mclient::PtestAction() {
	return ;

}

void mclient::aGo() {
	
	settings.setValue("url", textURL->text());
	settings.setValue("user", textUser->text());
	settings.setValue("password", textPass->text());
        settings.setValue("calendar_id", calendar_id->currentIndex());
	QStringList calendarios;
	for ( int it =0;it<calendar_id->count();it++)
        	calendarios<<calendar_id->itemText(it);
     	
	settings.setValue("calendarios", calendarios);
	settings.setValue("intervalo", intervalo->value());

	hide();

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(checkUpdates()));
        timer->start(intervalo->value()*1000);
        checkUpdates();
}


void mclient::aTestParams() {
	
        QUrl url(textURL->text());

        textSystem->setText( "Conectando" );
        client->setHost( url.host(), url.port(),url.path() );
        client->setUser( textUser->text(),textPass->text());
    
	int x = textURL->text().toInt();
        int y = textURL->text().toInt();

        requestIdSum = client->request("calendar.listCalendars",true,4);
        
}

void mclient::processReturnValue( int requestId, xmlrpc::Variant value )
{
     value.pprint();
     if (requestId==requestIdSum) {

     	QStringList respo=value.toStringList();
	calendar_id->clear();
	for ( QStringList::Iterator it =respo.begin(); it != respo.end(); ++it ) {
        	calendar_id->insertItem(-1,QString(*it));
     	}
	
     	textSystem->setText( value.toString() );

     } else if (requestId==idAlarm) {
        
	QListIterator<QVariant> it( value.toList() );
            while( it.hasNext() ) {
		QMapIterator<QString,QVariant> rit(it.next().toMap());
		t_alarm *t=new(t_alarm);
		t->id=0;
		t->checked=0;	
                while( rit.hasNext() ) {
                	rit.next();
                	QString val = rit.value().toString();
			
			if (rit.key()=="start") {
				t->start=new QDateTime();
				t->start->setTime_t (rit.value().toInt());
			}
			if (rit.key()=="title") {
				t->title=new QString(rit.value().toString());
			}
			if (rit.key()=="user") {
				t->user=new QString(rit.value().toString());
			}
			if (rit.key()=="text") {
				t->text=new QString(rit.value().toString());
			}
			if (rit.key()=="id") {
				t->id=new QString(rit.value().toString());
			}
            	}
		if (t->id!=0)
			if (t->id->length()>=0)
				if (!Alarmas.contains(*t->id))
					Alarmas.insert(*t->id,*t);
            }
     }
    
     
     QMapIterator<QString,t_alarm> i(Alarmas);
     while (i.hasNext()) {
  	   i.next();
     	   
     }
		
     noticeAlarms();
    

    
}

void mclient::processFault( int requestId, int errorCode, QString errorString )
{
    trayIcon->setIcon(QIcon(":/images/heart.png"));
    trayIcon->setToolTip(QString("Error")+QString(errorString));
    textSystem->setText(errorString);
    

}

void mclient::checkUpdates() {

 
 QUrl url(textURL->text());
 
 //timer->start(intervalo->value()*1000);

 client->setHost( url.host(), url.port(),url.path() );
 client->setUser( textUser->text(),textPass->text());

 QDateTime time=QDateTime::currentDateTime ();

 idAlarm = client->request("calendar.listAlarms",time.toTime_t (),textUser->text());

 client_mail->setHost( url.host(), url.port(),url.path() );
 client_mail->setUser( textUser->text(),textPass->text());
 client_mail->request("mail.summary");

}

void mclient::showNormalC() {

	timer->stop();
	showNormal();
}

void mclient::noticeAlarms() {

	
	int status=0;
 	
	QMapIterator<QString,t_alarm> i(Alarmas);
     	while (i.hasNext()) {
		t_alarm ci=i.next().value();
     	   	if (ci.checked>0)
			continue;
		else {
			QWidget *k=new QWidget();
			CMsgBox *MB=new CMsgBox();
			MB->cID->setText(*ci.id);
			QString dMessage;
			dMessage.append(*ci.title);
			dMessage.append("\n");
			dMessage.append(*ci.text);
			MB->CMessageText->setText(dMessage);
			MB->show();
			connect(MB, SIGNAL(updateAlerts(QLabel *, QCheckBox *)), this, SLOT(updateAlarms(QLabel *,QCheckBox *)));
			//QSound::play("sounds/1.wav");
			setIcon(I_MSG);
			status++;
		}
     	}
	if (status==0)
		setIcon(I_NORMAL);

}

void mclient::updateAlarms(QLabel *id, QCheckBox *est) {
	
	QMutableMapIterator <QString,t_alarm> i(Alarmas);
	
	while (i.hasNext()) {
		t_alarm ci=i.next().value();
		if (ci.id==id->text()) 
			if (est->isChecked())  {
				i.value().checked++;
				
			}
	}
 	
	return;
}


void mclient::setDuser(QString duser) {
	this->duser=duser;
        textUser->setText(duser);
}
void mclient::setDUrl(QString durl) {
	this->durl=durl;
        textURL->setText(durl);
}

void mclient::processSummary(int requestId, xmlrpc::Variant value) {

	QString messages;
	QString unseen;
	QString newmsg;

	static int onchange=0;
        
	value.pprint();
	QListIterator<QVariant> it( value.toList() );
        while( it.hasNext() ) {
		QMapIterator<QString,QVariant> rit(it.next().toMap());
		
                while( rit.hasNext() ) {
 
                	rit.next();
			
                	QString val = rit.value().toString();
			
			if (rit.key()=="messages") {
				messages=rit.value().toString();
			}
			if (rit.key()=="unseen") {
				unseen=rit.value().toString();
			}
			if (rit.key()=="newmsg") {
				newmsg=rit.value().toString();;
			}
     		}
	}	
    
     
     qCritical()<<"messages:"<<messages<<" unseen:"<<unseen<<" newmsg:"<<newmsg;
     if (unseen.toInt()>0) {

	trayIcon->setIcon(QIcon(":/images/mail.png"));
        trayIcon->setToolTip(QString(unseen)+" mensaje(s) sin leer");
                

	if (onchange==0) {
		adjustSize ();
		QSound::play("sounds/1.wav");
		onchange=1;
 	
		trayIcon->showMessage(QString("Atención"),QString(unseen)+" mensaje(s) sin leer",
			      QSystemTrayIcon::
			      MessageIcon(QSystemTrayIcon::Information),
			      0);
	}
	


       


     } else if (onchange==1) {

 	onchange=0;

     }

}