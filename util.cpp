#include "util.h"

Util::Util(){}

QStringList Util::getBookNameList(QDir dirPath){
    QDir dir(dirPath);
    QStringList bookName;
    QStringList filter;
    filter << "*.db";
    dir.setNameFilters(filter);
    QFileInfoList fileList = dir.entryInfoList(filter);
    if(fileList.size()>0){
        for(int i=0;i<fileList.size();i++){
            bookName.append(fileList.at(i).baseName());
        }
    }
    return bookName;
}
