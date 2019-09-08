#ifndef COURSE_H
#define COURSE_H

#include <QStringList>
#include <iostream>
using std::string;

enum CourseType { COMPULSORY, OPTIONAL };

class Course {
public:
    Course() {}

    Course(QStringList datalist) {
        setID(datalist[0].toLong());
        setName(datalist[1].toStdString());
        setCredits(datalist[2].toInt());
        setHours(datalist[3].toInt());
        setCourseType(datalist[4].toInt());
    }
    QStringList toQStringList() {
        QStringList datalist;
        datalist.append(QString::number(getID()));
        datalist.append(QString::fromStdString(getName()));
        datalist.append(QString::number(getCredits()));
        datalist.append(QString::number(getHours()));
        datalist.append(QString::number(getCourseType()));
        return datalist;
    }

    long getID() { return id; }
    string getName() { return name; }
    int getCredits() { return credits; }
    int getHours() { return hours; }
    int getCourseType() { return courseType; }

    bool setID(long id) {
        if (id < 0)
            return false;
        else
            this->id = id;
        return true;
    }

    bool setName(string na) {
        if (na.length() > 100 || na.length() < 1)
            return false;
        else
            this->name = na;
        return true;
    }
    bool setCredits(int credit) {
        if (credit < 0)
            return false;
        else
            this->credits = credit;
        return true;
    }
    bool setHours(int hour) {
        if (hour < 0)
            return false;
        else
            this->hours = hour;
        return true;
    }
    bool setCourseType(int type) {
        switch (type) {
        case 0:
            courseType = CourseType::COMPULSORY;
            break;
        case 1:
            courseType = CourseType::OPTIONAL;
            break;
        default:
            return false;
        }
        return true;
    }

protected:
    long id;
    string name;
    int credits;
    int hours;
    CourseType courseType;
};

#endif
