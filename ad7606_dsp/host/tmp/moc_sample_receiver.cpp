/****************************************************************************
** Meta object code from reading C++ file 'sample_receiver.h'
**
** Created: Sun Oct 28 17:25:26 2018
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../app/sample_receiver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sample_receiver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SampleReceiver[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      23,   16,   15,   15, 0x05,
      47,   16,   15,   15, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_SampleReceiver[] = {
    "SampleReceiver\0\0sample\0raw(std::vector<float>)\0"
    "fft(std::vector<float>)\0"
};

void SampleReceiver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SampleReceiver *_t = static_cast<SampleReceiver *>(_o);
        switch (_id) {
        case 0: _t->raw((*reinterpret_cast< std::vector<float>(*)>(_a[1]))); break;
        case 1: _t->fft((*reinterpret_cast< std::vector<float>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SampleReceiver::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SampleReceiver::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SampleReceiver,
      qt_meta_data_SampleReceiver, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SampleReceiver::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SampleReceiver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SampleReceiver::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SampleReceiver))
        return static_cast<void*>(const_cast< SampleReceiver*>(this));
    if (!strcmp(_clname, "base::ThreadWorker"))
        return static_cast< base::ThreadWorker*>(const_cast< SampleReceiver*>(this));
    return QObject::qt_metacast(_clname);
}

int SampleReceiver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void SampleReceiver::raw(std::vector<float> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SampleReceiver::fft(std::vector<float> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
