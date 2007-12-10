/****************************************************************************
** Poof2 meta object code from reading C++ file 'poof2.h'
**
** Created: Wed Sep 13 22:53:48 2006
**      by: The Qt MOC ($Id: poof2.moc.cpp,v 1.1 2007/12/10 09:16:09 actsys Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "poof2.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *Poof2::className() const
{
    return "Poof2";
}

QMetaObject *Poof2::metaObj = 0;
static QMetaObjectCleanUp cleanUp_Poof2( "Poof2", &Poof2::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString Poof2::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Poof2", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString Poof2::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "Poof2", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* Poof2::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"Poof2", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_Poof2.setMetaObject( metaObj );
    return metaObj;
}

void* Poof2::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "Poof2" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool Poof2::qt_invoke( int _id, QUObject* _o )
{
    return QWidget::qt_invoke(_id,_o);
}

bool Poof2::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool Poof2::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool Poof2::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
