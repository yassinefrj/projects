/****************************************************************************
** Meta object code from reading C++ file 'view.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Stratego_FinalV/view/view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_stratego__View_t {
    const uint offsetsAndSize[16];
    char stringdata0[158];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_stratego__View_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_stratego__View_t qt_meta_stringdata_stratego__View = {
    {
QT_MOC_LITERAL(0, 14), // "stratego::View"
QT_MOC_LITERAL(15, 23), // "on_menuChoice_activated"
QT_MOC_LITERAL(39, 0), // ""
QT_MOC_LITERAL(40, 5), // "index"
QT_MOC_LITERAL(46, 21), // "on_file_start_clicked"
QT_MOC_LITERAL(68, 28), // "on_interactive_start_clicked"
QT_MOC_LITERAL(97, 34), // "on_actionNouvelle_Partie_trig..."
QT_MOC_LITERAL(132, 25) // "on_actionManuel_triggered"

    },
    "stratego::View\0on_menuChoice_activated\0"
    "\0index\0on_file_start_clicked\0"
    "on_interactive_start_clicked\0"
    "on_actionNouvelle_Partie_triggered\0"
    "on_actionManuel_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_stratego__View[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   44,    2, 0x08,    1 /* Private */,
       4,    0,   47,    2, 0x08,    3 /* Private */,
       5,    0,   48,    2, 0x08,    4 /* Private */,
       6,    0,   49,    2, 0x08,    5 /* Private */,
       7,    0,   50,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void stratego::View::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<View *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_menuChoice_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_file_start_clicked(); break;
        case 2: _t->on_interactive_start_clicked(); break;
        case 3: _t->on_actionNouvelle_Partie_triggered(); break;
        case 4: _t->on_actionManuel_triggered(); break;
        default: ;
        }
    }
}

const QMetaObject stratego::View::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_stratego__View.offsetsAndSize,
    qt_meta_data_stratego__View,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_stratego__View_t
, QtPrivate::TypeAndForceComplete<View, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *stratego::View::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stratego::View::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_stratego__View.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "nvs::Observer"))
        return static_cast< nvs::Observer*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int stratego::View::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
