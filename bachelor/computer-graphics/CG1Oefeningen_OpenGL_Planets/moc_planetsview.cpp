/****************************************************************************
** PlanetsView meta object code from reading C++ file 'planetsview.h'
**
** Created: Fri May 13 15:21:50 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "planetsview.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *PlanetsView::className() const
{
    return "PlanetsView";
}

QMetaObject *PlanetsView::metaObj = 0;
static QMetaObjectCleanUp cleanUp_PlanetsView( "PlanetsView", &PlanetsView::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString PlanetsView::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PlanetsView", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString PlanetsView::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PlanetsView", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* PlanetsView::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QGLWidget::staticMetaObject();
    static const QUMethod slot_0 = {"slotDocumentChanged", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotDocumentChanged()", &slot_0, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"PlanetsView", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_PlanetsView.setMetaObject( metaObj );
    return metaObj;
}

void* PlanetsView::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "PlanetsView" ) )
	return this;
    return QGLWidget::qt_cast( clname );
}

bool PlanetsView::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotDocumentChanged(); break;
    default:
	return QGLWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool PlanetsView::qt_emit( int _id, QUObject* _o )
{
    return QGLWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool PlanetsView::qt_property( int id, int f, QVariant* v)
{
    return QGLWidget::qt_property( id, f, v);
}

bool PlanetsView::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
