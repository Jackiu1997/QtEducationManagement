#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <QStringList>
#include "person_model.h"
using std::string;

class Student : public Person {
public:
    Student() {}

    Student(QStringList datalist) {
        setID(datalist[0].toLong());
        setName(datalist[1].toStdString());
        setPassword(datalist[2].toStdString());
        setClassNo(datalist[3].toLong());
    }
    QStringList toQStringList() {
        QStringList datalist;
        datalist.append(QString::number(getID()));
        datalist.append(QString::fromStdString(getName()));
        datalist.append(QString::fromStdString(getPassword()));
        datalist.append(QString::number(getClassNo()));
        return datalist;
    }

    long getClassNo() { return classNo; }
    bool setClassNo(long no) {
        classNo = no;
        return true;
    }

protected:
    long classNo;
};

#endif
