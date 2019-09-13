/****************************************************************************
** Meta object code from reading C++ file 'CG1_Canvas.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../LES1/CG1_Canvas.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CG1_Canvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CG1_Canvas_t {
    QByteArrayData data[9];
    char stringdata[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CG1_Canvas_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CG1_Canvas_t qt_meta_stringdata_CG1_Canvas = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CG1_Canvas"
QT_MOC_LITERAL(1, 11, 11), // "SizeChanged"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 17), // "slotGetPixelColor"
QT_MOC_LITERAL(4, 42, 1), // "x"
QT_MOC_LITERAL(5, 44, 1), // "y"
QT_MOC_LITERAL(6, 46, 9), // "RGB_Color"
QT_MOC_LITERAL(7, 56, 1), // "c"
QT_MOC_LITERAL(8, 58, 13) // "slotSaveImage"

    },
    "CG1_Canvas\0SizeChanged\0\0slotGetPixelColor\0"
    "x\0y\0RGB_Color\0c\0slotSaveImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CG1_Canvas[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    3,   30,    2, 0x0a /* Public */,
       8,    0,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 6,    4,    5,    7,
    QMetaType::Void,

       0        // eod
};

void CG1_Canvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CG1_Canvas *_t = static_cast<CG1_Canvas *>(_o);
        switch (_id) {
        case 0: _t->SizeChanged(); break;
        case 1: _t->slotGetPixelColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< RGB_Color(*)>(_a[3]))); break;
        case 2: _t->slotSaveImage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CG1_Canvas::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CG1_Canvas::SizeChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject CG1_Canvas::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CG1_Canvas.data,
      qt_meta_data_CG1_Canvas,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CG1_Canvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CG1_Canvas::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CG1_Canvas.stringdata))
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
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CG1_Canvas::SizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
