#ifndef UTIL_H
#define UTIL_H
#include "QFile"
#include "qdir.h"

class Util
{
public:
    Util();
    static QStringList getBookNameList(QDir dirPath);
};

#endif // UTIL_H
