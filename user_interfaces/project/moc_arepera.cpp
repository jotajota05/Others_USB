/****************************************************************************
** Meta object code from reading C++ file 'arepera.h'
**
** Created: Thu Jul 9 09:33:33 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "arepera.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'arepera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Arepera[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x08,
      36,    8,    8,    8, 0x08,
      66,    8,    8,    8, 0x08,
      92,    8,    8,    8, 0x08,
     119,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Arepera[] = {
    "Arepera\0\0on_actionAbrir_triggered()\0"
    "on_actionImprimir_triggered()\0"
    "on_pushButton_2_clicked()\0"
    "on_actionSalir_triggered()\0lockDrag(QString)\0"
};

const QMetaObject Arepera::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Arepera,
      qt_meta_data_Arepera, 0 }
};

const QMetaObject *Arepera::metaObject() const
{
    return &staticMetaObject;
}

void *Arepera::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Arepera))
        return static_cast<void*>(const_cast< Arepera*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Arepera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_actionAbrir_triggered(); break;
        case 1: on_actionImprimir_triggered(); break;
        case 2: on_pushButton_2_clicked(); break;
        case 3: on_actionSalir_triggered(); break;
        case 4: lockDrag((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
