/****************************************************************************
** Meta object code from reading C++ file 'objetos.h'
**
** Created: Thu Jul 9 09:33:36 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "objetos.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'objetos.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Objetos[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      16,    9,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Objetos[] = {
    "Objetos\0\0item,n\0newObs(QTreeWidgetItem*,int)\0"
};

const QMetaObject Objetos::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Objetos,
      qt_meta_data_Objetos, 0 }
};

const QMetaObject *Objetos::metaObject() const
{
    return &staticMetaObject;
}

void *Objetos::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Objetos))
        return static_cast<void*>(const_cast< Objetos*>(this));
    return QWidget::qt_metacast(_clname);
}

int Objetos::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: newObs((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
