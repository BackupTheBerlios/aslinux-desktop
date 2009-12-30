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
#include "khusba.h"
#include "QSyncHttp.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysctl.h>
#include <linux/sysctl.h>

struct QStringVariantArray {
    QString key;
    QVariant value;
};

Q_DECLARE_METATYPE(QStringVariantArray);
Q_DECLARE_METATYPE(QList < QStringVariantArray >);
Q_DECLARE_METATYPE(QString );
Q_DECLARE_METATYPE(QList < QString >);

struct DeviceNotificacion {
    QString VxP;
    QString Vendor;
    QString Product;
    QString Drivers;
    QString Bustype;
};

const QDebug
operator<<(QDebug debug, const QList < QStringVariantArray > &lme)
{

    foreach(QStringVariantArray me,
	    lme) debug << me.key << ":" << me.value.toString() << "\n";
    return debug;
}

const QDBusArgument &
operator>>(const QDBusArgument & argument, QStringVariantArray & me)
{

    argument.beginStructure();
    argument >> me.key >> me.value;
    argument.endStructure();
    return argument;
}

const QDBusArgument &
operator<<(QDBusArgument & argument, const QStringVariantArray & me)
{

    argument.beginStructure();
    argument << me.key << (QDBusVariant) me.value;
    argument.endStructure();
    return argument;
}

khusba::khusba(QObject * parent):QObject(parent)
{
    qDebug("Connecting signal");
    QDBusConnection::systemBus().connect("",
					 "/org/freedesktop/Hal/Manager",
					 "org.freedesktop.Hal.Manager",
					 "DeviceAdded", this,
					 SLOT(messageSlot(QString)));

    QDBusConnection::sessionBus().connect("",
					 "/VisualNotifications",
					 "org.kde.VisualNotifications",
					 "ActionInvoked", this,
					 SLOT(requestMoreInfoSlot(uint,QString)));

    qDebug("Connected");
    // messageSlot("/org/freedesktop/Hal/devices/usb_device_7ca_a815_300633400662000");
    //requestMoreInfoSlot(1,"/org/freedesktop/Hal/devices/usb_device_83a_a618_1_0");
}

void khusba::messageSlot(const QString & text)
{

    qDebug() << "Entering messageSlot:" << text;

    QDBusMessage msg =
	QDBusMessage::createMethodCall("org.freedesktop.Hal", text,
				       "org.freedesktop.Hal.Device",
				       "GetAllProperties");
    if (!QDBusConnection::systemBus().callWithCallback(msg, this,
						       SLOT(recMoreInfo
							    (const
							     QDBusMessage
							     &)),
						       SLOT(recError(const
								     QDBusError
								     &,
								     const
								     QDBusMessage
								     &)),
						       -1))
	 qDebug() << "Cound't send message to Hal:";

}

void khusba::recMoreInfo(const QDBusMessage & rep)
{

    static QList < DeviceNotificacion > DevNotList;

    qDebug() << "Entering recMoreInfo:" << " " << rep.arguments().size();
    QList < QVariant > a = rep.arguments();
    qDebug() << a[0];
    QList < QVariant > b = a[0].toList();

    QString driver;
    QString bustype;
    QString vendorID;
    QString productID;
    QString vendorname;
    QString devicename;
    QString parent;
    QString udi;

    DeviceNotificacion Notification;
    Notification.VxP="_";
     
    //Debug
    for (int i = 0; i < b.size(); i++) {
	qDebug() << "#" << b[i].typeName() << "#";
    }

    QList < QStringVariantArray > messages =
	qdbus_cast < QList < QStringVariantArray > >(a[0]);
    qDebug() << messages;
    for (int i = 0; i < messages.size(); i++) {
	// qDebug()<<messages[i].key<<" :
	// "<<messages[i].value.toString()<<"\n";
	if (messages[i].key == "info.vendor")
	    vendorname.append(QString(messages[i].value.toString()));
	else if (messages[i].key == "info.product")
	    devicename.append(QString(messages[i].value.toString()));
	else if (messages[i].key == "info.linux.driver")
	    driver.append(QString(messages[i].value.toString()));
	else if (messages[i].key == "linux.subsystem")
	    bustype = QString(messages[i].value.toString());
	else if (messages[i].key == "usb_device.vendor_id")
	    vendorID =
		QString::number(QString(messages[i].value.toString()).
				toInt(), 16);
	else if (messages[i].key == "usb_device.product_id")
	    productID =
		QString::number(QString(messages[i].value.toString()).
				toInt(),16);
	else if (messages[i].key == "info.parent")
	    parent = messages[i].value.toString();
	else if (messages[i].key =="info.udi")
		udi.append(QString(messages[i].value.toString()));
    }

    int j = 0;

    for (j = 0; j < DevNotList.size(); j++) {
	if ((DevNotList[j].VxP == QString(vendorID + "_" + productID))
	    && (DevNotList[j].VxP.length() > 0)) {
	    // Update element
	    // 
	    qDebug()<<"Updating: "<<QString::number((long)j,10);
	    if (DevNotList[j].Vendor.length() < 1)
		DevNotList[j].Vendor.append(vendorname);
	    if (DevNotList[j].Product.length() < 1)
		DevNotList[j].Product.append(devicename);
	    if (DevNotList[j].Drivers.indexOf(driver,0)<0)
	     DevNotList[j].Drivers.append(" "+driver);
	    if (DevNotList[j].Bustype.indexOf(bustype,0)<0)
	      DevNotList[j].Bustype.append(" "+bustype);
	    Notification = DevNotList[j];
	    break;
	} else if ((parent.indexOf(DevNotList[j].VxP, 0) > 0) && (QString(vendorID + "_" + productID)=="_")) {
	    qDebug()<<"Updating (parent): "<<QString::number((long)j,10);
	    if (DevNotList[j].Drivers.indexOf(driver,0)<0)
	     DevNotList[j].Drivers.append(" "+driver);
	    if (DevNotList[j].Bustype.indexOf(bustype,0)<0)
	     DevNotList[j].Bustype.append(" "+bustype);
	    Notification = DevNotList[j];
	    break;
	}


    }
    if ((j == DevNotList.size())&&(QString(vendorID + "_" + productID)!="_")) {
	// Add element
	// 
	// 
	// 
       qDebug()<<"Adding: "<<QString::number((long)j,10);
	Notification.VxP = QString(vendorID + "_" + productID);
	Notification.Vendor.append(vendorname);
	Notification.Product.append(devicename);
	Notification.Drivers.append(driver);
        Notification.Bustype.append(bustype);
       	DevNotList.append(Notification);
    } 

    if ((Notification.VxP != "_")) {
       qDebug()<<"Notificando "<< QString(vendorID +"_"+productID+" "+QString::number((long)j,10));
	QDBusMessage msg =
	    QDBusMessage::createMethodCall("org.kde.VisualNotifications",
					   "/VisualNotifications",
					   "org.kde.VisualNotifications",
					   "Notify");
	QVariantMap paraA;
	QStringList paraB;
	bool discard;
	paraB << productID.sprintf("%04x:%04x",vendorID.toInt(&discard,16),productID.toInt(&discard,16)) << "Info"
	<<udi<<"Add";


	// sussssasa{sv}i
	msg << "Sistema" << (uint) j+1 << QString(vendorID +
						productID) << "usb-key" <<
	    QString("Hardware conectado") << QString(Notification.Vendor + " (" +Notification.VxP+")\n"+ 
					     Notification.Product + "\nDriver: " +
					     Notification.
						     Drivers + "\nTags: "+Notification.Bustype)
	   << paraB << paraA << 0;
	if (!QDBusConnection::sessionBus().send(msg)) {
	    qDebug() << "Cound't send message to knotify:";
	}
    }

}
void khusba::requestMoreInfoSlot(uint uid,const QString &text) {

	static QTime tElapsed(0,0,0,0);
	
	if (QTime::currentTime ().secsTo(tElapsed)>-3) 
		return;
	else {
		tElapsed=QTime::currentTime ();	
	}	
	
	

	qDebug()<<text;
	if (text.indexOf("/")==0) {
		// Add device
		QString driver;
		QString bustype;
		QString vendorID;
		QString productID;
		QString vendorname;
		QString devicename;
		QString parent;
		QString udi;

		QDBusMessage msg =QDBusMessage::createMethodCall("org.freedesktop.Hal", "/org/freedesktop/Hal/Manager",
				       "org.freedesktop.Hal.Manager",
				       "GetAllDevices");
    		QDBusMessage res=QDBusConnection::systemBus().call(msg);
		
		QStringList dAll= qdbus_cast < QStringList >(res.arguments()[0]);
		
		//qDebug() << res.arguments()[0];
		QList <QString> children;

		for (int j = 0; j < dAll.size(); j++) {
			if ((dAll[j].indexOf(text)==0)&&(dAll[j]!=text))
				children.append(dAll[j]);
		}
		qDebug() << children;

		// Get primary info */
		msg =QDBusMessage::createMethodCall("org.freedesktop.Hal", text,
				       "org.freedesktop.Hal.Device",
				       "GetAllProperties");
    		res=QDBusConnection::systemBus().call(msg);
		QList < QStringVariantArray > dInfo = qdbus_cast < QList < QStringVariantArray > >(res.arguments()[0]);
    		qDebug() << dInfo;
    		for (int i = 0; i < dInfo.size(); i++) {
				if (dInfo[i].key == "info.vendor")
			vendorname.append(QString(dInfo[i].value.toString()));
			else if (dInfo[i].key == "info.product")
			devicename.append(QString(dInfo[i].value.toString()));
			else if (dInfo[i].key == "info.linux.driver")
			driver.append(QString(dInfo[i].value.toString()));
			else if (dInfo[i].key == "linux.subsystem")
			bustype = QString(dInfo[i].value.toString());
			else if (dInfo[i].key == "usb_device.vendor_id")
			vendorID =
				QString::number(QString(dInfo[i].value.toString()).
						toInt(), 16);
			else if (dInfo[i].key == "usb_device.product_id")
			productID =
				QString::number(QString(dInfo[i].value.toString()).
						toInt(),16);
			else if (dInfo[i].key == "info.parent")
			parent = dInfo[i].value.toString();
			else if (dInfo[i].key =="info.udi")
				udi.append(QString(dInfo[i].value.toString()));
		}
		// Get more info from children 
		int Drivercounter=2;
		for (int j=0;j<children.size();j++) {
			msg =QDBusMessage::createMethodCall("org.freedesktop.Hal", children[j],
				       "org.freedesktop.Hal.Device",
				       "GetAllProperties");
    			res=QDBusConnection::systemBus().call(msg);
			QList < QStringVariantArray > dInfo = qdbus_cast < QList < QStringVariantArray > >(res.arguments()[0]);
			for (int i = 0; i < dInfo.size(); i++) {
				if ((dInfo[i].key == "info.linux.driver")&&(QString(dInfo[i].value.toString()).length()>0)) 
					driver.append("&driver"+QString::number(Drivercounter++,10)+"="+QString(dInfo[i].value.toString()));


			}
		}

		

		QString URL;
		bool discard;
		URL.append(productID.sprintf("vendorxproduct=%04x:%04x",vendorID.toInt(&discard,16),productID.toInt(&discard,16)));
		URL.append("&description="+devicename);
		URL.append("&bus=USB");
		URL.append("&driver1="+driver);
		URL.append("&altdescription="+vendorname);
		int name[] = {CTL_KERN, KERN_OSRELEASE};
	        int namelen = 2;
	        char oldval[32];  /* 4 would suffice */
        	size_t len = sizeof(oldval);
        	int i, error;
	        error = sysctl (name, namelen,(void *)oldval, &len, NULL, 0 );
		URL.append("&kversion="+QString(QByteArray(oldval,len)));
		URL.append("&notes=(Via khusba4)");

		URL.append("&shash="+ QCryptographicHash::hash((QByteArray)URL.toAscii(),QCryptographicHash::Md5).toBase64());
		qDebug()<<URL;	


		QSyncHttp host("luhdc.berlios.de");
		QBuffer getOutput;
		host.Get( "/public_action_send4.php?"+URL.replace(QChar(' '),"%20") ,&getOutput );
		qDebug() << getOutput.data();

	
		/*msg=QDBusMessage::createMethodCall("org.kde.klauncher", "/KLauncher",
				       "org.kde.KLauncher",
				       "exec_blind");
		msg <<"konqueror"<<QStringList(QString("http://luhdc.berlios.de/public_action_send4.php?"+URL));
        	QDBusConnection::sessionBus().send(msg);*/
		msg =QDBusMessage::createMethodCall("org.kde.VisualNotifications",
					   "/VisualNotifications",
					   "org.kde.VisualNotifications",
					   "Notify");
		QVariantMap paraA;
		QStringList paraB;
		// sussssasa{sv}i
		msg << "Sistema" << (uint)100 << "luhdc" << "usb-key" <<QString("Peticion enviada") << QString(getOutput.data()) << paraB << paraA << 5000;		
		QDBusConnection::sessionBus().send(msg);

	}
	else if (text.indexOf(":")>0) {
		// Check device
		QDBusMessage msg=QDBusMessage::createMethodCall("org.kde.klauncher", "/KLauncher",
				       "org.kde.KLauncher",
				       "exec_blind");
		msg <<"konqueror"<<QStringList(QString("http://luhdc.berlios.de/Pages/USB/View/VPID="+text));
        	QDBusConnection::sessionBus().send(msg);
	}


}

void khusba::recError(const QDBusError & err, const QDBusMessage & rep)
{
    qWarning() << "Entering recError:" << err;
}

khusba::~khusba()
{
}
