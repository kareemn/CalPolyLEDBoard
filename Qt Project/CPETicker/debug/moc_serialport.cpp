/****************************************************************************
** Meta object code from reading C++ file 'serialport.h'
**
** Created: Mon Jan 14 11:03:32 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qtserialport/src/serialport/serialport.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SerialPort[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
      10,  104, // properties
       9,  144, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   12,   11,   11, 0x05,
      61,   52,   11,   11, 0x05,
      94,   87,   11,   11, 0x05,
     125,  116,   11,   11, 0x05,
     156,  151,   11,   11, 0x05,
     195,  188,   11,   11, 0x05,
     239,  235,   11,   11, 0x05,
     256,  235,   11,   11, 0x05,
     279,  273,   11,   11, 0x05,
     311,  303,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     352,  235,  347,   11, 0x0a,
     365,  235,  347,   11, 0x0a,
     387,  378,  347,   11, 0x0a,
     402,   11,  347,   11, 0x2a,
     414,  235,  347,   11, 0x0a,
     429,   11,  347,   11, 0x2a,
     446,  440,  347,   11, 0x0a,
     463,   11,  347,   11, 0x2a,

 // properties: name, type, flags
     483,  476, 0x02495103,
      52,  488, 0x0049510b,
      87,  497, 0x0049510b,
     116,  504, 0x0049510b,
     525,  513, 0x0049510b,
     553,  537, 0x0049510b,
     569,  347, 0x01495103,
     573,  347, 0x01495103,
     273,  577, 0x0049500d,
     587,  347, 0x01495103,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,
       6,
       7,
       8,
       9,

 // enums: name, flags, count, data
     610, 0x0,    3,  180,
     621, 0x0,    9,  186,
     488, 0x0,    5,  204,
     497, 0x0,    6,  214,
     504, 0x0,    4,  226,
     513, 0x0,    4,  234,
     626, 0x0,    9,  242,
     537, 0x0,    5,  260,
     577, 0x0,   11,  270,

 // enum data: key, value
     632, uint(SerialPort::Input),
     638, uint(SerialPort::Output),
     645, uint(SerialPort::AllDirections),
     659, uint(SerialPort::Rate1200),
     668, uint(SerialPort::Rate2400),
     677, uint(SerialPort::Rate4800),
     686, uint(SerialPort::Rate9600),
     695, uint(SerialPort::Rate19200),
     705, uint(SerialPort::Rate38400),
     715, uint(SerialPort::Rate57600),
     725, uint(SerialPort::Rate115200),
     736, uint(SerialPort::UnknownRate),
     748, uint(SerialPort::Data5),
     754, uint(SerialPort::Data6),
     760, uint(SerialPort::Data7),
     766, uint(SerialPort::Data8),
     772, uint(SerialPort::UnknownDataBits),
     788, uint(SerialPort::NoParity),
     797, uint(SerialPort::EvenParity),
     808, uint(SerialPort::OddParity),
     818, uint(SerialPort::SpaceParity),
     830, uint(SerialPort::MarkParity),
     841, uint(SerialPort::UnknownParity),
     855, uint(SerialPort::OneStop),
     863, uint(SerialPort::OneAndHalfStop),
     878, uint(SerialPort::TwoStop),
     886, uint(SerialPort::UnknownStopBits),
     902, uint(SerialPort::NoFlowControl),
     916, uint(SerialPort::HardwareControl),
     932, uint(SerialPort::SoftwareControl),
     948, uint(SerialPort::UnknownFlowControl),
     967, uint(SerialPort::LeLine),
     974, uint(SerialPort::DtrLine),
     982, uint(SerialPort::RtsLine),
     990, uint(SerialPort::StLine),
     997, uint(SerialPort::SrLine),
    1004, uint(SerialPort::CtsLine),
    1012, uint(SerialPort::DcdLine),
    1020, uint(SerialPort::RiLine),
    1027, uint(SerialPort::DsrLine),
    1035, uint(SerialPort::SkipPolicy),
    1046, uint(SerialPort::PassZeroPolicy),
    1061, uint(SerialPort::IgnorePolicy),
    1074, uint(SerialPort::StopReceivingPolicy),
    1094, uint(SerialPort::UnknownPolicy),
    1108, uint(SerialPort::NoError),
    1116, uint(SerialPort::NoSuchDeviceError),
    1134, uint(SerialPort::PermissionDeniedError),
    1156, uint(SerialPort::DeviceAlreadyOpenedError),
    1181, uint(SerialPort::DeviceIsNotOpenedError),
    1204, uint(SerialPort::ParityError),
    1216, uint(SerialPort::FramingError),
    1229, uint(SerialPort::BreakConditionError),
    1249, uint(SerialPort::IoError),
    1257, uint(SerialPort::UnsupportedPortOperationError),
    1287, uint(SerialPort::UnknownPortError),

       0        // eod
};

static const char qt_meta_stringdata_SerialPort[] = {
    "SerialPort\0\0rate,dir\0"
    "rateChanged(qint32,Directions)\0dataBits\0"
    "dataBitsChanged(DataBits)\0parity\0"
    "parityChanged(Parity)\0stopBits\0"
    "stopBitsChanged(StopBits)\0flow\0"
    "flowControlChanged(FlowControl)\0policy\0"
    "dataErrorPolicyChanged(DataErrorPolicy)\0"
    "set\0dtrChanged(bool)\0rtsChanged(bool)\0"
    "error\0errorChanged(PortError)\0restore\0"
    "restoreSettingsOnCloseChanged(bool)\0"
    "bool\0setDtr(bool)\0setRts(bool)\0duration\0"
    "sendBreak(int)\0sendBreak()\0setBreak(bool)\0"
    "setBreak()\0clear\0clearBreak(bool)\0"
    "clearBreak()\0qint32\0rate\0DataBits\0"
    "Parity\0StopBits\0FlowControl\0flowControl\0"
    "DataErrorPolicy\0dataErrorPolicy\0dtr\0"
    "rts\0PortError\0restoreSettingsOnClose\0"
    "Directions\0Rate\0Lines\0Input\0Output\0"
    "AllDirections\0Rate1200\0Rate2400\0"
    "Rate4800\0Rate9600\0Rate19200\0Rate38400\0"
    "Rate57600\0Rate115200\0UnknownRate\0Data5\0"
    "Data6\0Data7\0Data8\0UnknownDataBits\0"
    "NoParity\0EvenParity\0OddParity\0SpaceParity\0"
    "MarkParity\0UnknownParity\0OneStop\0"
    "OneAndHalfStop\0TwoStop\0UnknownStopBits\0"
    "NoFlowControl\0HardwareControl\0"
    "SoftwareControl\0UnknownFlowControl\0"
    "LeLine\0DtrLine\0RtsLine\0StLine\0SrLine\0"
    "CtsLine\0DcdLine\0RiLine\0DsrLine\0"
    "SkipPolicy\0PassZeroPolicy\0IgnorePolicy\0"
    "StopReceivingPolicy\0UnknownPolicy\0"
    "NoError\0NoSuchDeviceError\0"
    "PermissionDeniedError\0DeviceAlreadyOpenedError\0"
    "DeviceIsNotOpenedError\0ParityError\0"
    "FramingError\0BreakConditionError\0"
    "IoError\0UnsupportedPortOperationError\0"
    "UnknownPortError\0"
};

void SerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SerialPort *_t = static_cast<SerialPort *>(_o);
        switch (_id) {
        case 0: _t->rateChanged((*reinterpret_cast< qint32(*)>(_a[1])),(*reinterpret_cast< Directions(*)>(_a[2]))); break;
        case 1: _t->dataBitsChanged((*reinterpret_cast< DataBits(*)>(_a[1]))); break;
        case 2: _t->parityChanged((*reinterpret_cast< Parity(*)>(_a[1]))); break;
        case 3: _t->stopBitsChanged((*reinterpret_cast< StopBits(*)>(_a[1]))); break;
        case 4: _t->flowControlChanged((*reinterpret_cast< FlowControl(*)>(_a[1]))); break;
        case 5: _t->dataErrorPolicyChanged((*reinterpret_cast< DataErrorPolicy(*)>(_a[1]))); break;
        case 6: _t->dtrChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->rtsChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->errorChanged((*reinterpret_cast< PortError(*)>(_a[1]))); break;
        case 9: _t->restoreSettingsOnCloseChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: { bool _r = _t->setDtr((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 11: { bool _r = _t->setRts((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 12: { bool _r = _t->sendBreak((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: { bool _r = _t->sendBreak();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 14: { bool _r = _t->setBreak((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 15: { bool _r = _t->setBreak();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 16: { bool _r = _t->clearBreak((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 17: { bool _r = _t->clearBreak();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SerialPort::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SerialPort::staticMetaObject = {
    { &QIODevice::staticMetaObject, qt_meta_stringdata_SerialPort,
      qt_meta_data_SerialPort, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SerialPort::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SerialPort))
        return static_cast<void*>(const_cast< SerialPort*>(this));
    return QIODevice::qt_metacast(_clname);
}

int SerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QIODevice::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qint32*>(_v) = rate(); break;
        case 1: *reinterpret_cast< DataBits*>(_v) = dataBits(); break;
        case 2: *reinterpret_cast< Parity*>(_v) = parity(); break;
        case 3: *reinterpret_cast< StopBits*>(_v) = stopBits(); break;
        case 4: *reinterpret_cast< FlowControl*>(_v) = flowControl(); break;
        case 5: *reinterpret_cast< DataErrorPolicy*>(_v) = dataErrorPolicy(); break;
        case 6: *reinterpret_cast< bool*>(_v) = dtr(); break;
        case 7: *reinterpret_cast< bool*>(_v) = rts(); break;
        case 8: *reinterpret_cast< PortError*>(_v) = error(); break;
        case 9: *reinterpret_cast< bool*>(_v) = restoreSettingsOnClose(); break;
        }
        _id -= 10;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setRate(*reinterpret_cast< qint32*>(_v)); break;
        case 1: setDataBits(*reinterpret_cast< DataBits*>(_v)); break;
        case 2: setParity(*reinterpret_cast< Parity*>(_v)); break;
        case 3: setStopBits(*reinterpret_cast< StopBits*>(_v)); break;
        case 4: setFlowControl(*reinterpret_cast< FlowControl*>(_v)); break;
        case 5: setDataErrorPolicy(*reinterpret_cast< DataErrorPolicy*>(_v)); break;
        case 6: setDtr(*reinterpret_cast< bool*>(_v)); break;
        case 7: setRts(*reinterpret_cast< bool*>(_v)); break;
        case 9: setRestoreSettingsOnClose(*reinterpret_cast< bool*>(_v)); break;
        }
        _id -= 10;
    } else if (_c == QMetaObject::ResetProperty) {
        switch (_id) {
        case 8: clearError(); break;
        }
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 10;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void SerialPort::rateChanged(qint32 _t1, Directions _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SerialPort::dataBitsChanged(DataBits _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SerialPort::parityChanged(Parity _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SerialPort::stopBitsChanged(StopBits _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void SerialPort::flowControlChanged(FlowControl _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SerialPort::dataErrorPolicyChanged(DataErrorPolicy _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SerialPort::dtrChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void SerialPort::rtsChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void SerialPort::errorChanged(PortError _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void SerialPort::restoreSettingsOnCloseChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_END_MOC_NAMESPACE
