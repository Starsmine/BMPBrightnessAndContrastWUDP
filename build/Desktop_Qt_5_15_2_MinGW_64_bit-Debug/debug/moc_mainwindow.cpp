/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[352];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 22), // "on_pushButton_released"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 24), // "on_pushButton_2_released"
QT_MOC_LITERAL(4, 60, 31), // "on_horizontalSlider_sliderMoved"
QT_MOC_LITERAL(5, 92, 8), // "position"
QT_MOC_LITERAL(6, 101, 33), // "on_horizontalSlider_2_sliderM..."
QT_MOC_LITERAL(7, 135, 33), // "on_graphicsView_windowIconCha..."
QT_MOC_LITERAL(8, 169, 4), // "icon"
QT_MOC_LITERAL(9, 174, 10), // "setOverlay"
QT_MOC_LITERAL(10, 185, 24), // "on_pushButton_4_released"
QT_MOC_LITERAL(11, 210, 24), // "on_pushButton_5_released"
QT_MOC_LITERAL(12, 235, 24), // "on_pushButton_3_released"
QT_MOC_LITERAL(13, 260, 9), // "UDPoutput"
QT_MOC_LITERAL(14, 270, 24), // "on_TransferPhoto_pressed"
QT_MOC_LITERAL(15, 295, 26), // "on_TransferOverlay_pressed"
QT_MOC_LITERAL(16, 322, 24), // "on_checkBox_stateChanged"
QT_MOC_LITERAL(17, 347, 4) // "arg1"

    },
    "MainWindow\0on_pushButton_released\0\0"
    "on_pushButton_2_released\0"
    "on_horizontalSlider_sliderMoved\0"
    "position\0on_horizontalSlider_2_sliderMoved\0"
    "on_graphicsView_windowIconChanged\0"
    "icon\0setOverlay\0on_pushButton_4_released\0"
    "on_pushButton_5_released\0"
    "on_pushButton_3_released\0UDPoutput\0"
    "on_TransferPhoto_pressed\0"
    "on_TransferOverlay_pressed\0"
    "on_checkBox_stateChanged\0arg1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    1,   81,    2, 0x08 /* Private */,
       6,    1,   84,    2, 0x08 /* Private */,
       7,    1,   87,    2, 0x08 /* Private */,
       9,    0,   90,    2, 0x08 /* Private */,
      10,    0,   91,    2, 0x08 /* Private */,
      11,    0,   92,    2, 0x08 /* Private */,
      12,    0,   93,    2, 0x08 /* Private */,
      13,    0,   94,    2, 0x08 /* Private */,
      14,    0,   95,    2, 0x08 /* Private */,
      15,    0,   96,    2, 0x08 /* Private */,
      16,    1,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::QIcon,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_released(); break;
        case 1: _t->on_pushButton_2_released(); break;
        case 2: _t->on_horizontalSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_horizontalSlider_2_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_graphicsView_windowIconChanged((*reinterpret_cast< const QIcon(*)>(_a[1]))); break;
        case 5: _t->setOverlay(); break;
        case 6: _t->on_pushButton_4_released(); break;
        case 7: _t->on_pushButton_5_released(); break;
        case 8: _t->on_pushButton_3_released(); break;
        case 9: _t->UDPoutput(); break;
        case 10: _t->on_TransferPhoto_pressed(); break;
        case 11: _t->on_TransferOverlay_pressed(); break;
        case 12: _t->on_checkBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
