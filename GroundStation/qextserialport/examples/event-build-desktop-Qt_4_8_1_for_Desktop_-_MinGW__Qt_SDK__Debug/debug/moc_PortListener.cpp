/****************************************************************************
** Meta object code from reading C++ file 'PortListener.h'
**
** Created: Mon 30. Apr 10:46:18 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../event/PortListener.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PortListener.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PortListener[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x08,
      35,   28,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PortListener[] = {
    "PortListener\0\0onReadyRead()\0status\0"
    "onDsrChanged(bool)\0"
};

void PortListener::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PortListener *_t = static_cast<PortListener *>(_o);
        switch (_id) {
        case 0: _t->onReadyRead(); break;
        case 1: _t->onDsrChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PortListener::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PortListener::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PortListener,
      qt_meta_data_PortListener, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PortListener::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PortListener::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PortListener::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PortListener))
        return static_cast<void*>(const_cast< PortListener*>(this));
    return QObject::qt_metacast(_clname);
}

int PortListener::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
