/****************************************************************************
**
** DCOP Stub Implementation created by dcopidl2cpp from dcopdemoiface.kidl
**
** WARNING! All changes made in this file will be lost!
**
*****************************************************************************/

#include "dcopdemoiface_stub.h"
#include <dcopclient.h>

#include <kdatastream.h>


DCOPDemoIface_stub::DCOPDemoIface_stub( const QCString& app, const QCString& obj )
  : DCOPStub( app, obj )
{
}

DCOPDemoIface_stub::DCOPDemoIface_stub( DCOPClient* client, const QCString& app, const QCString& obj )
  : DCOPStub( client, app, obj )
{
}

DCOPDemoIface_stub::DCOPDemoIface_stub( const DCOPRef& ref )
  : DCOPStub( ref )
{
}

void DCOPDemoIface_stub::setLabel( const QString& arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "setLabel(QString)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void DCOPDemoIface_stub::setSay( const QString& arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "setSay(QString)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void DCOPDemoIface_stub::setShot( const QString& arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "setShot(QString)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void DCOPDemoIface_stub::setTitle( const QString& arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "setTitle(QString)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void DCOPDemoIface_stub::setProgreso( int arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "setProgreso(int)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

void DCOPDemoIface_stub::setProgresoP( unsigned long int arg0 )
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    if ( dcopClient()->call( app(), obj(), "setProgresoP(unsigned long int)", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}

int DCOPDemoIface_stub::getFile( const QString& arg0, const QString& arg1 )
{
    int result = 0;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    QDataStream arg( data, IO_WriteOnly );
    arg << arg0;
    arg << arg1;
    if ( dcopClient()->call( app(), obj(), "getFile(QString,QString)", data, replyType, replyData ) ) {
	if ( replyType == "int" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

int DCOPDemoIface_stub::getStatus()
{
    int result = 0;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "getStatus()", data, replyType, replyData ) ) {
	if ( replyType == "int" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

int DCOPDemoIface_stub::errStatus()
{
    int result = 0;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "errStatus()", data, replyType, replyData ) ) {
	if ( replyType == "int" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

int DCOPDemoIface_stub::getWinId()
{
    int result = 0;
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return result;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "getWinId()", data, replyType, replyData ) ) {
	if ( replyType == "int" ) {
	    QDataStream _reply_stream( replyData, IO_ReadOnly );
	    _reply_stream >> result;
	    setStatus( CallSucceeded );
	} else {
	    callFailed();
	}
    } else { 
	callFailed();
    }
    return result;
}

void DCOPDemoIface_stub::shoshow()
{
    if ( !dcopClient()  ) {
	setStatus( CallFailed );
	return;
    }
    QByteArray data, replyData;
    QCString replyType;
    if ( dcopClient()->call( app(), obj(), "shoshow()", data, replyType, replyData ) ) {
	setStatus( CallSucceeded );
    } else { 
	callFailed();
    }
}


