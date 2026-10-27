/****************************************************************************
** Meta object code from reading C++ file 'rovercontroller.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../rovercontroller.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rovercontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN15RoverControllerE_t {};
} // unnamed namespace

template <> constexpr inline auto RoverController::qt_create_metaobjectdata<qt_meta_tag_ZN15RoverControllerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "RoverController",
        "rollChanged",
        "",
        "pitchChanged",
        "yawChanged",
        "setAttitude",
        "roll",
        "pitch",
        "yaw",
        "roll_qml",
        "pitch_qml",
        "yaw_qml"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'rollChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'pitchChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'yawChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'setAttitude'
        QtMocHelpers::MethodData<void(float, float, float)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Float, 6 }, { QMetaType::Float, 7 }, { QMetaType::Float, 8 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'roll_qml'
        QtMocHelpers::PropertyData<float>(9, QMetaType::Float, QMC::DefaultPropertyFlags, 0),
        // property 'pitch_qml'
        QtMocHelpers::PropertyData<float>(10, QMetaType::Float, QMC::DefaultPropertyFlags, 1),
        // property 'yaw_qml'
        QtMocHelpers::PropertyData<float>(11, QMetaType::Float, QMC::DefaultPropertyFlags, 2),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<RoverController, qt_meta_tag_ZN15RoverControllerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject RoverController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15RoverControllerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15RoverControllerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15RoverControllerE_t>.metaTypes,
    nullptr
} };

void RoverController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<RoverController *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->rollChanged(); break;
        case 1: _t->pitchChanged(); break;
        case 2: _t->yawChanged(); break;
        case 3: _t->setAttitude((*reinterpret_cast<std::add_pointer_t<float>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<float>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<float>>(_a[3]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (RoverController::*)()>(_a, &RoverController::rollChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (RoverController::*)()>(_a, &RoverController::pitchChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (RoverController::*)()>(_a, &RoverController::yawChanged, 2))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<float*>(_v) = _t->GetRoll(); break;
        case 1: *reinterpret_cast<float*>(_v) = _t->GetPitch(); break;
        case 2: *reinterpret_cast<float*>(_v) = _t->GetYaw(); break;
        default: break;
        }
    }
}

const QMetaObject *RoverController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RoverController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15RoverControllerE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int RoverController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void RoverController::rollChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void RoverController::pitchChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void RoverController::yawChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
