/****************************************************************************
** Meta object code from reading C++ file 'mkprotocol.h'
**
** Created: Sat 19. May 11:55:26 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GroundStation/MKProtocol/mkprotocol.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mkprotocol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MKProtocol[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   12,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      55,   50,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MKProtocol[] = {
    "MKProtocol\0\0,,\0dataReceived(char,char,QByteArray)\0"
    "Data\0handleBuffer(QByteArray)\0"
};

void MKProtocol::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MKProtocol *_t = static_cast<MKProtocol *>(_o);
        switch (_id) {
        case 0: _t->dataReceived((*reinterpret_cast< char(*)>(_a[1])),(*reinterpret_cast< char(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 1: _t->handleBuffer((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MKProtocol::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MKProtocol::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MKProtocol,
      qt_meta_data_MKProtocol, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MKProtocol::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MKProtocol::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MKProtocol::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MKProtocol))
        return static_cast<void*>(const_cast< MKProtocol*>(this));
    return QObject::qt_metacast(_clname);
}

int MKProtocol::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void MKProtocol::dataReceived(char _t1, char _t2, QByteArray _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
