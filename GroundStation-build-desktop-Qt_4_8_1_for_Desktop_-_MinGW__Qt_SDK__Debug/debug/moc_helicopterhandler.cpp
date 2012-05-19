/****************************************************************************
** Meta object code from reading C++ file 'helicopterhandler.h'
**
** Created: Sat 19. May 11:55:34 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GroundStation/helicopterhandler.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'helicopterhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HelicopterHandler[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   19,   18,   18, 0x05,
      45,   18,   18,   18, 0x05,
      57,   18,   18,   18, 0x05,
      77,   18,   18,   18, 0x05,
      97,   18,   18,   18, 0x05,
     116,   18,   18,   18, 0x05,
     163,  144,   18,   18, 0x05,

 // slots: signature, parameters, type, tag, flags
     212,  182,   18,   18, 0x08,
     246,   18,   18,   18, 0x08,
     271,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_HelicopterHandler[] = {
    "HelicopterHandler\0\0,\0dataReceived(char,char)\0"
    "commError()\0FCVersionReceived()\0"
    "NCVersionReceived()\0FC3DDatareceived()\0"
    "NumberOfWaypointsReceived()\0"
    "typeCommand,origin\0retried(char,char)\0"
    "OriginAddress,ModuleType,Data\0"
    "processData(char,char,QByteArray)\0"
    "RequestHelicopterState()\0timedOut()\0"
};

void HelicopterHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        HelicopterHandler *_t = static_cast<HelicopterHandler *>(_o);
        switch (_id) {
        case 0: _t->dataReceived((*reinterpret_cast< char(*)>(_a[1])),(*reinterpret_cast< char(*)>(_a[2]))); break;
        case 1: _t->commError(); break;
        case 2: _t->FCVersionReceived(); break;
        case 3: _t->NCVersionReceived(); break;
        case 4: _t->FC3DDatareceived(); break;
        case 5: _t->NumberOfWaypointsReceived(); break;
        case 6: _t->retried((*reinterpret_cast< char(*)>(_a[1])),(*reinterpret_cast< char(*)>(_a[2]))); break;
        case 7: _t->processData((*reinterpret_cast< char(*)>(_a[1])),(*reinterpret_cast< char(*)>(_a[2])),(*reinterpret_cast< QByteArray(*)>(_a[3]))); break;
        case 8: _t->RequestHelicopterState(); break;
        case 9: _t->timedOut(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData HelicopterHandler::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject HelicopterHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HelicopterHandler,
      qt_meta_data_HelicopterHandler, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HelicopterHandler::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HelicopterHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HelicopterHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HelicopterHandler))
        return static_cast<void*>(const_cast< HelicopterHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int HelicopterHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void HelicopterHandler::dataReceived(char _t1, char _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HelicopterHandler::commError()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void HelicopterHandler::FCVersionReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void HelicopterHandler::NCVersionReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void HelicopterHandler::FC3DDatareceived()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void HelicopterHandler::NumberOfWaypointsReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void HelicopterHandler::retried(char _t1, char _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
