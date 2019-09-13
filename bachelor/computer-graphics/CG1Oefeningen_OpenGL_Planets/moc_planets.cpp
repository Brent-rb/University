/****************************************************************************
** PlanetsApp meta object code from reading C++ file 'planets.h'
**
** Created: Fri May 13 15:20:43 2005
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.4   edited Jan 21 18:14 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "planets.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *PlanetsApp::className() const
{
    return "PlanetsApp";
}

QMetaObject *PlanetsApp::metaObj = 0;
static QMetaObjectCleanUp cleanUp_PlanetsApp( "PlanetsApp", &PlanetsApp::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString PlanetsApp::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PlanetsApp", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString PlanetsApp::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PlanetsApp", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* PlanetsApp::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUMethod slot_0 = {"slotFileNew", 0, 0 };
    static const QUMethod slot_1 = {"slotFileOpen", 0, 0 };
    static const QUMethod slot_2 = {"slotFileSave", 0, 0 };
    static const QUMethod slot_3 = {"slotFileSaveAs", 0, 0 };
    static const QUMethod slot_4 = {"slotFileClose", 0, 0 };
    static const QUMethod slot_5 = {"slotFilePrint", 0, 0 };
    static const QUMethod slot_6 = {"slotFileQuit", 0, 0 };
    static const QUMethod slot_7 = {"slotEditCut", 0, 0 };
    static const QUMethod slot_8 = {"slotEditCopy", 0, 0 };
    static const QUMethod slot_9 = {"slotEditPaste", 0, 0 };
    static const QUParameter param_slot_10[] = {
	{ "toggle", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_10 = {"slotViewToolBar", 1, param_slot_10 };
    static const QUParameter param_slot_11[] = {
	{ "toggle", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_11 = {"slotViewStatusBar", 1, param_slot_11 };
    static const QUMethod slot_12 = {"slotHelpAbout", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slotFileNew()", &slot_0, QMetaData::Public },
	{ "slotFileOpen()", &slot_1, QMetaData::Public },
	{ "slotFileSave()", &slot_2, QMetaData::Public },
	{ "slotFileSaveAs()", &slot_3, QMetaData::Public },
	{ "slotFileClose()", &slot_4, QMetaData::Public },
	{ "slotFilePrint()", &slot_5, QMetaData::Public },
	{ "slotFileQuit()", &slot_6, QMetaData::Public },
	{ "slotEditCut()", &slot_7, QMetaData::Public },
	{ "slotEditCopy()", &slot_8, QMetaData::Public },
	{ "slotEditPaste()", &slot_9, QMetaData::Public },
	{ "slotViewToolBar(bool)", &slot_10, QMetaData::Public },
	{ "slotViewStatusBar(bool)", &slot_11, QMetaData::Public },
	{ "slotHelpAbout()", &slot_12, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"PlanetsApp", parentObject,
	slot_tbl, 13,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_PlanetsApp.setMetaObject( metaObj );
    return metaObj;
}

void* PlanetsApp::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "PlanetsApp" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool PlanetsApp::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slotFileNew(); break;
    case 1: slotFileOpen(); break;
    case 2: slotFileSave(); break;
    case 3: slotFileSaveAs(); break;
    case 4: slotFileClose(); break;
    case 5: slotFilePrint(); break;
    case 6: slotFileQuit(); break;
    case 7: slotEditCut(); break;
    case 8: slotEditCopy(); break;
    case 9: slotEditPaste(); break;
    case 10: slotViewToolBar((bool)static_QUType_bool.get(_o+1)); break;
    case 11: slotViewStatusBar((bool)static_QUType_bool.get(_o+1)); break;
    case 12: slotHelpAbout(); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool PlanetsApp::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool PlanetsApp::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool PlanetsApp::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
