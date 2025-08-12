/****************************************************************************
** Meta object code from reading C++ file 'cameracontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../cameracontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cameracontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CameraController_t {
    QByteArrayData data[19];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CameraController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CameraController_t qt_meta_stringdata_CameraController = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CameraController"
QT_MOC_LITERAL(1, 17, 19), // "cameraStatusChanged"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 17), // "cameraListChanged"
QT_MOC_LITERAL(4, 56, 13), // "errorOccurred"
QT_MOC_LITERAL(5, 70, 5), // "error"
QT_MOC_LITERAL(6, 76, 13), // "imageCaptured"
QT_MOC_LITERAL(7, 90, 5), // "image"
QT_MOC_LITERAL(8, 96, 11), // "startCamera"
QT_MOC_LITERAL(9, 108, 12), // "cameraDevice"
QT_MOC_LITERAL(10, 121, 10), // "stopCamera"
QT_MOC_LITERAL(11, 132, 12), // "switchCamera"
QT_MOC_LITERAL(12, 145, 12), // "captureImage"
QT_MOC_LITERAL(13, 158, 19), // "updateCameraDevices"
QT_MOC_LITERAL(14, 178, 15), // "onImageCaptured"
QT_MOC_LITERAL(15, 194, 2), // "id"
QT_MOC_LITERAL(16, 197, 7), // "preview"
QT_MOC_LITERAL(17, 205, 15), // "cameraAvailable"
QT_MOC_LITERAL(18, 221, 16) // "availableCameras"

    },
    "CameraController\0cameraStatusChanged\0"
    "\0cameraListChanged\0errorOccurred\0error\0"
    "imageCaptured\0image\0startCamera\0"
    "cameraDevice\0stopCamera\0switchCamera\0"
    "captureImage\0updateCameraDevices\0"
    "onImageCaptured\0id\0preview\0cameraAvailable\0"
    "availableCameras"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CameraController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       2,   92, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    1,   71,    2, 0x06 /* Public */,
       6,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   77,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x2a /* Public | MethodCloned */,
      10,    0,   81,    2, 0x0a /* Public */,
      11,    1,   82,    2, 0x0a /* Public */,
      12,    0,   85,    2, 0x0a /* Public */,
      13,    0,   86,    2, 0x08 /* Private */,
      14,    2,   87,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QImage,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QImage,   15,   16,

 // properties: name, type, flags
      17, QMetaType::Bool, 0x00495001,
      18, QMetaType::QStringList, 0x00495001,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void CameraController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CameraController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cameraStatusChanged(); break;
        case 1: _t->cameraListChanged(); break;
        case 2: _t->errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->imageCaptured((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        case 4: _t->startCamera((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->startCamera(); break;
        case 6: _t->stopCamera(); break;
        case 7: _t->switchCamera((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->captureImage(); break;
        case 9: _t->updateCameraDevices(); break;
        case 10: _t->onImageCaptured((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QImage(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CameraController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraController::cameraStatusChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CameraController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraController::cameraListChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CameraController::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraController::errorOccurred)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CameraController::*)(const QImage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CameraController::imageCaptured)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<CameraController *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isCameraAvailable(); break;
        case 1: *reinterpret_cast< QStringList*>(_v) = _t->availableCameras(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject CameraController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CameraController.data,
    qt_meta_data_CameraController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CameraController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CameraController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CameraController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void CameraController::cameraStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CameraController::cameraListChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void CameraController::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CameraController::imageCaptured(const QImage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
