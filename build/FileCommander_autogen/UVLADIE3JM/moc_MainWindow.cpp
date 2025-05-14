/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/MainWindow.h"
#include <QtGui/qtextcursor.h>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
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

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "onDriveComboLeftChanged",
    "",
    "index",
    "onDriveComboRightChanged",
    "onLeftViewClicked",
    "QModelIndex",
    "onRightViewClicked",
    "onCopyButtonClicked",
    "onMoveButtonClicked",
    "onDeleteButtonClicked",
    "onNewFolderButtonClicked",
    "onRenameButtonClicked",
    "onUploadButtonClicked",
    "onDownloadButtonClicked",
    "onStartServerButtonClicked",
    "onConnectButtonClicked",
    "onTransferFileButtonClicked",
    "updateStatusBar",
    "message",
    "isError",
    "updateProgress",
    "bytes",
    "total",
    "handleFileReceived",
    "filePath"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {
    uint offsetsAndSizes[52];
    char stringdata0[11];
    char stringdata1[24];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[25];
    char stringdata5[18];
    char stringdata6[12];
    char stringdata7[19];
    char stringdata8[20];
    char stringdata9[20];
    char stringdata10[22];
    char stringdata11[25];
    char stringdata12[22];
    char stringdata13[22];
    char stringdata14[24];
    char stringdata15[27];
    char stringdata16[23];
    char stringdata17[28];
    char stringdata18[16];
    char stringdata19[8];
    char stringdata20[8];
    char stringdata21[15];
    char stringdata22[6];
    char stringdata23[6];
    char stringdata24[19];
    char stringdata25[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSMainWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSMainWindowENDCLASS_t qt_meta_stringdata_CLASSMainWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "MainWindow"
        QT_MOC_LITERAL(11, 23),  // "onDriveComboLeftChanged"
        QT_MOC_LITERAL(35, 0),  // ""
        QT_MOC_LITERAL(36, 5),  // "index"
        QT_MOC_LITERAL(42, 24),  // "onDriveComboRightChanged"
        QT_MOC_LITERAL(67, 17),  // "onLeftViewClicked"
        QT_MOC_LITERAL(85, 11),  // "QModelIndex"
        QT_MOC_LITERAL(97, 18),  // "onRightViewClicked"
        QT_MOC_LITERAL(116, 19),  // "onCopyButtonClicked"
        QT_MOC_LITERAL(136, 19),  // "onMoveButtonClicked"
        QT_MOC_LITERAL(156, 21),  // "onDeleteButtonClicked"
        QT_MOC_LITERAL(178, 24),  // "onNewFolderButtonClicked"
        QT_MOC_LITERAL(203, 21),  // "onRenameButtonClicked"
        QT_MOC_LITERAL(225, 21),  // "onUploadButtonClicked"
        QT_MOC_LITERAL(247, 23),  // "onDownloadButtonClicked"
        QT_MOC_LITERAL(271, 26),  // "onStartServerButtonClicked"
        QT_MOC_LITERAL(298, 22),  // "onConnectButtonClicked"
        QT_MOC_LITERAL(321, 27),  // "onTransferFileButtonClicked"
        QT_MOC_LITERAL(349, 15),  // "updateStatusBar"
        QT_MOC_LITERAL(365, 7),  // "message"
        QT_MOC_LITERAL(373, 7),  // "isError"
        QT_MOC_LITERAL(381, 14),  // "updateProgress"
        QT_MOC_LITERAL(396, 5),  // "bytes"
        QT_MOC_LITERAL(402, 5),  // "total"
        QT_MOC_LITERAL(408, 18),  // "handleFileReceived"
        QT_MOC_LITERAL(427, 8)   // "filePath"
    },
    "MainWindow",
    "onDriveComboLeftChanged",
    "",
    "index",
    "onDriveComboRightChanged",
    "onLeftViewClicked",
    "QModelIndex",
    "onRightViewClicked",
    "onCopyButtonClicked",
    "onMoveButtonClicked",
    "onDeleteButtonClicked",
    "onNewFolderButtonClicked",
    "onRenameButtonClicked",
    "onUploadButtonClicked",
    "onDownloadButtonClicked",
    "onStartServerButtonClicked",
    "onConnectButtonClicked",
    "onTransferFileButtonClicked",
    "updateStatusBar",
    "message",
    "isError",
    "updateProgress",
    "bytes",
    "total",
    "handleFileReceived",
    "filePath"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  116,    2, 0x08,    1 /* Private */,
       4,    1,  119,    2, 0x08,    3 /* Private */,
       5,    1,  122,    2, 0x08,    5 /* Private */,
       7,    1,  125,    2, 0x08,    7 /* Private */,
       8,    0,  128,    2, 0x08,    9 /* Private */,
       9,    0,  129,    2, 0x08,   10 /* Private */,
      10,    0,  130,    2, 0x08,   11 /* Private */,
      11,    0,  131,    2, 0x08,   12 /* Private */,
      12,    0,  132,    2, 0x08,   13 /* Private */,
      13,    0,  133,    2, 0x08,   14 /* Private */,
      14,    0,  134,    2, 0x08,   15 /* Private */,
      15,    0,  135,    2, 0x08,   16 /* Private */,
      16,    0,  136,    2, 0x08,   17 /* Private */,
      17,    0,  137,    2, 0x08,   18 /* Private */,
      18,    2,  138,    2, 0x08,   19 /* Private */,
      21,    2,  143,    2, 0x08,   22 /* Private */,
      24,    1,  148,    2, 0x08,   25 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 6,    3,
    QMetaType::Void, 0x80000000 | 6,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   19,   20,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   22,   23,
    QMetaType::Void, QMetaType::QString,   25,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'onDriveComboLeftChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onDriveComboRightChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onLeftViewClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'onRightViewClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'onCopyButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onMoveButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDeleteButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onNewFolderButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onRenameButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onUploadButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDownloadButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onStartServerButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onConnectButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onTransferFileButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateStatusBar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'updateProgress'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        QtPrivate::TypeAndForceComplete<qint64, std::false_type>,
        // method 'handleFileReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onDriveComboLeftChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->onDriveComboRightChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->onLeftViewClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 3: _t->onRightViewClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 4: _t->onCopyButtonClicked(); break;
        case 5: _t->onMoveButtonClicked(); break;
        case 6: _t->onDeleteButtonClicked(); break;
        case 7: _t->onNewFolderButtonClicked(); break;
        case 8: _t->onRenameButtonClicked(); break;
        case 9: _t->onUploadButtonClicked(); break;
        case 10: _t->onDownloadButtonClicked(); break;
        case 11: _t->onStartServerButtonClicked(); break;
        case 12: _t->onConnectButtonClicked(); break;
        case 13: _t->onTransferFileButtonClicked(); break;
        case 14: _t->updateStatusBar((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 15: _t->updateProgress((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qint64>>(_a[2]))); break;
        case 16: _t->handleFileReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
