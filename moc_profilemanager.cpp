/****************************************************************************
** Meta object code from reading C++ file 'profilemanager.h'
**
** Created: Sat Oct 23 19:41:28 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "profilemanager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'profilemanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ProfileManager[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x0a,
      31,   15,   15,   15, 0x0a,
      43,   15,   15,   15, 0x0a,
      56,   15,   15,   15, 0x0a,
      67,   15,   15,   15, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ProfileManager[] = {
    "ProfileManager\0\0saveProfiles()\0"
    "browseSrc()\0browseDest()\0doDelete()\0"
    "checkFilled()\0"
};

const QMetaObject ProfileManager::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ProfileManager,
      qt_meta_data_ProfileManager, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ProfileManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ProfileManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ProfileManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProfileManager))
        return static_cast<void*>(const_cast< ProfileManager*>(this));
    return QDialog::qt_metacast(_clname);
}

int ProfileManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: saveProfiles(); break;
        case 1: browseSrc(); break;
        case 2: browseDest(); break;
        case 3: doDelete(); break;
        case 4: checkFilled(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE