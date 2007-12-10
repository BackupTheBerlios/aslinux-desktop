/****************************************************************************
**
** DCOP Stub Definition created by dcopidl2cpp from dcopdemoiface.kidl
**
** WARNING! All changes made in this file will be lost!
**
*****************************************************************************/

#ifndef __DCOPDEMOIFACE_STUB__
#define __DCOPDEMOIFACE_STUB__

#include <dcopstub.h>
#include <dcopobject.h>


class DCOPDemoIface_stub : virtual public DCOPStub
{
public:
    DCOPDemoIface_stub( const QCString& app, const QCString& id );
    DCOPDemoIface_stub( DCOPClient* client, const QCString& app, const QCString& id );
    explicit DCOPDemoIface_stub( const DCOPRef& ref );
    virtual void setLabel( const QString& str );
    virtual void setSay( const QString& str );
    virtual void setShot( const QString& str );
    virtual void setTitle( const QString& str );
    virtual void setProgreso( int p );
    virtual void setProgresoP( unsigned long int p );
    virtual int getFile( const QString& src, const QString& dst );
    virtual int getStatus();
    virtual int errStatus();
    virtual int getWinId();
    virtual void shoshow();
protected:
    DCOPDemoIface_stub() : DCOPStub( never_use ) {};
};


#endif
