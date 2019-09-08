#ifndef MANAGER_H
#define MANAGER_H

#include <QStringList>
#include <iostream>
#include "person_model.h"
using std::string;

class Manager : public Person {
public:
    Manager() {}

    Manager(QStringList datalist) {
        setID(datalist[0].toLong());
        setName(datalist[1].toStdString());
        setPassword(datalist[2].toStdString());
        setAuthority(datalist[3].toInt());
    }
    QStringList toQStringList() {
        QStringList datalist;
        datalist.append(QString::number(getID()));
        datalist.append(QString::fromStdString(getName()));
        datalist.append(QString::fromStdString(getPassword()));
        datalist.append(QString::number(getAuthority()));
        return datalist;
    }

    int getAuthority() { return authority; }
    bool setAuthority(int auth) {
        if (auth >=0 && auth <= 2) {
            authority = auth;
            return true;
        }
        return false;
    }

protected:
    int authority;
    // 0: root 1: 校教务 2: 院教务
};

#endif
