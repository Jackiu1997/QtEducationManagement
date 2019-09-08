#ifndef TEACHING_CLASS_H
#define TEACHING_CLASS_H

#include <QStringList>

class TeachingClass {
public:
    TeachingClass() {}

    TeachingClass(QStringList datalist) {
        setClassID(datalist[0].toLong());
        setCourseID(datalist[1].toLong());
        setTeacherID(datalist[2].toLong());
    }
    QStringList toQStringList() {
        QStringList datalist;
        datalist.append(QString::number(getClassID()));
        datalist.append(QString::number(getCourseID()));
        datalist.append(QString::number(getTeacherID()));
        return datalist;
    }

    long getClassID() { return classID; }
    long getCourseID() { return courseID; }
    long getTeacherID() { return teacherID; }

    bool setClassID(long id) {
        if (id < 0)
            return false;
        else
            classID = id;
        return true;
    }
    bool setCourseID(long id) {
        if (id < 0)
            return false;
        else
            courseID = id;
        return true;
    }
    bool setTeacherID(long id) {
        if (id < 0)
            return false;
        else
            teacherID = id;
        return true;
    }

protected:
    long classID;
    long courseID;
    long teacherID;
};

#endif // TEACHING_CLASS_H
