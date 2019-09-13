/****************************************************************************
** Meta object code from reading C++ file 'CG1_DrawTool.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../LES1/CG1_DrawTool.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CG1_DrawTool.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CG1_DrawTool_t {
    QByteArrayData data[8];
    char stringdata[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CG1_DrawTool_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CG1_DrawTool_t qt_meta_stringdata_CG1_DrawTool = {
    {
QT_MOC_LITERAL(0, 0, 12), // "CG1_DrawTool"
QT_MOC_LITERAL(1, 13, 8), // "PutPixel"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 1), // "x"
QT_MOC_LITERAL(4, 25, 1), // "y"
QT_MOC_LITERAL(5, 27, 9), // "RGB_Color"
QT_MOC_LITERAL(6, 37, 5), // "color"
QT_MOC_LITERAL(7, 43, 12) // "UpdateWindow"

    },
    "CG1_DrawTool\0PutPixel\0\0x\0y\0RGB_Color\0"
    "color\0UpdateWindow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CG1_DrawTool[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,
       7,    0,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 5,    3,    4,    6,
    QMetaType::Void,

       0        // eod
};

void CG1_DrawTool::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CG1_DrawTool *_t = static_cast<CG1_DrawTool *>(_o);
        switch (_id) {
        case 0: _t->PutPixel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< RGB_Color(*)>(_a[3]))); break;
        case 1: _t->UpdateWindow(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CG1_DrawTool::*_t)(int , int , RGB_Color );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CG1_DrawTool::PutPixel)) {
                *result = 0;
            }
        }
        {
            typedef void (CG1_DrawTool::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CG1_DrawTool::UpdateWindow)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject CG1_DrawTool::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CG1_DrawTool.data,
      qt_meta_data_CG1_DrawTool,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CG1_DrawTool::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CG1_DrawTool::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CG1_DrawTool.stringdata))
        return static_cast<void*>(const_cast< CG1_DrawTool*>(this));
    return QObject::qt_metacast(_clname);
}

int CG1_DrawTool::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CG1_DrawTool::PutPixel(int _t1, int _t2, RGB_Color _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CG1_DrawTool::UpdateWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
