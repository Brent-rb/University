/****************************************************************************
** Meta object code from reading C++ file 'CG1_Canvas.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Les1/CG1_Canvas.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CG1_Canvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CG1_Canvas[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      32,   26,   11,   11, 0x0a,
      69,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CG1_Canvas[] = {
    "CG1_Canvas\0\0SizeChanged()\0x,y,c\0"
    "slotGetPixelColor(int,int,RGB_Color)\0"
    "slotSaveImage()\0"
};

void CG1_Canvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CG1_Canvas *_t = static_cast<CG1_Canvas *>(_o);
        switch (_id) {
        case 0: _t->SizeChanged(); break;
        case 1: _t->slotGetPixelColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< RGB_Color(*)>(_a[3]))); break;
        case 2: _t->slotSaveImage(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CG1_Canvas::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CG1_Canvas::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CG1_Canvas,
      qt_meta_data_CG1_Canvas, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CG1_Canvas::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CG1_Canvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CG1_Canvas::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CG1_Canvas))
        return static_cast<void*>(const_cast< CG1_Canvas*>(this));
    return QWidget::qt_metacast(_clname);
}

int CG1_Canvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CG1_Canvas::SizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
