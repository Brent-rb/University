/****************************************************************************
** Meta object code from reading C++ file 'RayTracer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../CG1Oefeningen_Raytracer/RayTracer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RayTracer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RayTracer_t {
    QByteArrayData data[11];
    char stringdata[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RayTracer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RayTracer_t qt_meta_stringdata_RayTracer = {
    {
QT_MOC_LITERAL(0, 0, 9), // "RayTracer"
QT_MOC_LITERAL(1, 10, 14), // "signalSetColor"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 1), // "x"
QT_MOC_LITERAL(4, 28, 1), // "y"
QT_MOC_LITERAL(5, 30, 9), // "RGB_Color"
QT_MOC_LITERAL(6, 40, 1), // "c"
QT_MOC_LITERAL(7, 42, 10), // "slotRender"
QT_MOC_LITERAL(8, 53, 15), // "slotSizeChanged"
QT_MOC_LITERAL(9, 69, 4), // "NewW"
QT_MOC_LITERAL(10, 74, 4) // "NewH"

    },
    "RayTracer\0signalSetColor\0\0x\0y\0RGB_Color\0"
    "c\0slotRender\0slotSizeChanged\0NewW\0"
    "NewH"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RayTracer[] = {

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
       1,    3,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   36,    2, 0x0a /* Public */,
       8,    2,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 5,    3,    4,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    9,   10,

       0        // eod
};

void RayTracer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RayTracer *_t = static_cast<RayTracer *>(_o);
        switch (_id) {
        case 0: _t->signalSetColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< RGB_Color(*)>(_a[3]))); break;
        case 1: _t->slotRender(); break;
        case 2: _t->slotSizeChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RayTracer::*_t)(int , int , RGB_Color );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RayTracer::signalSetColor)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject RayTracer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_RayTracer.data,
      qt_meta_data_RayTracer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RayTracer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RayTracer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RayTracer.stringdata))
        return static_cast<void*>(const_cast< RayTracer*>(this));
    return QObject::qt_metacast(_clname);
}

int RayTracer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void RayTracer::signalSetColor(int _t1, int _t2, RGB_Color _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
