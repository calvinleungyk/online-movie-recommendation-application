/****************************************************************************
** Meta object code from reading C++ file 'mainmenu.h'
**
** Created: Wed Dec 10 03:55:26 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainmenu.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Mainmenu[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      37,    9,    9,    9, 0x08,
      63,    9,    9,    9, 0x08,
      87,    9,    9,    9, 0x08,
     114,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Mainmenu[] = {
    "Mainmenu\0\0on_newUserButton_clicked()\0"
    "on_cancelButton_clicked()\0"
    "on_quitButton_clicked()\0"
    "on_confirmButton_clicked()\0"
    "on_loginButton_clicked()\0"
};

void Mainmenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Mainmenu *_t = static_cast<Mainmenu *>(_o);
        switch (_id) {
        case 0: _t->on_newUserButton_clicked(); break;
        case 1: _t->on_cancelButton_clicked(); break;
        case 2: _t->on_quitButton_clicked(); break;
        case 3: _t->on_confirmButton_clicked(); break;
        case 4: _t->on_loginButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Mainmenu::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Mainmenu::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Mainmenu,
      qt_meta_data_Mainmenu, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Mainmenu::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Mainmenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Mainmenu::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Mainmenu))
        return static_cast<void*>(const_cast< Mainmenu*>(this));
    return QDialog::qt_metacast(_clname);
}

int Mainmenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
