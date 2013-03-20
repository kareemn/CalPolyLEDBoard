/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Wed Mar 13 14:25:46 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      37,   11,   11,   11, 0x08,
      75,   11,   11,   11, 0x08,
     112,   11,   11,   11, 0x08,
     137,   11,   11,   11, 0x08,
     164,   11,   11,   11, 0x08,
     202,   11,   11,   11, 0x08,
     231,   11,   11,   11, 0x08,
     258,   11,   11,   11, 0x08,
     298,   11,   11,   11, 0x08,
     325,   11,   11,   11, 0x08,
     354,   11,   11,   11, 0x08,
     391,   11,   11,   11, 0x08,
     437,  431,   11,   11, 0x08,
     479,   11,   11,   11, 0x08,
     503,  431,   11,   11, 0x08,
     547,  431,   11,   11, 0x08,
     592,  431,   11,   11, 0x08,
     639,  431,   11,   11, 0x08,
     689,  431,   11,   11, 0x08,
     741,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_save_button_clicked()\0"
    "on_tableWidget_itemSelectionChanged()\0"
    "on_description_editbox_textChanged()\0"
    "closeEvent(QCloseEvent*)\0"
    "on_delete_button_clicked()\0"
    "on_announcement_editbox_textChanged()\0"
    "on_delete_button_2_clicked()\0"
    "on_save_button_2_clicked()\0"
    "on_tableWidget_2_itemSelectionChanged()\0"
    "on_save_button_3_clicked()\0"
    "on_delete_button_3_clicked()\0"
    "on_officeHours_editbox_textChanged()\0"
    "on_tableWidget_3_itemSelectionChanged()\0"
    "index\0on_port_comboBox_currentIndexChanged(int)\0"
    "on_pushButton_clicked()\0"
    "on_event_top_color_currentIndexChanged(int)\0"
    "on_event_desc_color_currentIndexChanged(int)\0"
    "on_announcement_color_currentIndexChanged(int)\0"
    "on_officehours_top_color_currentIndexChanged(int)\0"
    "on_officehours_hours_color_currentIndexChanged(int)\0"
    "timerInterval()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_save_button_clicked(); break;
        case 1: _t->on_tableWidget_itemSelectionChanged(); break;
        case 2: _t->on_description_editbox_textChanged(); break;
        case 3: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 4: _t->on_delete_button_clicked(); break;
        case 5: _t->on_announcement_editbox_textChanged(); break;
        case 6: _t->on_delete_button_2_clicked(); break;
        case 7: _t->on_save_button_2_clicked(); break;
        case 8: _t->on_tableWidget_2_itemSelectionChanged(); break;
        case 9: _t->on_save_button_3_clicked(); break;
        case 10: _t->on_delete_button_3_clicked(); break;
        case 11: _t->on_officeHours_editbox_textChanged(); break;
        case 12: _t->on_tableWidget_3_itemSelectionChanged(); break;
        case 13: _t->on_port_comboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->on_pushButton_clicked(); break;
        case 15: _t->on_event_top_color_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_event_desc_color_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->on_announcement_color_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->on_officehours_top_color_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->on_officehours_hours_color_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->timerInterval(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
