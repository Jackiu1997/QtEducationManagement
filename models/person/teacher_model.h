#ifndef TEACHER_H
#define TEACHER_H

#include <QStringList>
#include <iostream>
#include "person_model.h"
using std::string;

class Teacher : public Person {
public:
    Teacher() {}

    Teacher(QStringList datalist) {
        setID(datalist[0].toLong());
        setName(datalist[1].toStdString());
        setPassword(datalist[2].toStdString());
        setAvgStaticScore(datalist[3].toFloat());
    }
    QStringList toQStringList() {
        QStringList datalist;
        datalist.append(QString::number(getID()));
        datalist.append(QString::fromStdString(getName()));
        datalist.append(QString::fromStdString(getPassword()));
        datalist.append(QString::number(getAvgStaticScore()));
        return datalist;
    }

    float getAvgStaticScore() { return avgStatisScore; }
    bool setAvgStaticScore(float score) {
        if (score < 0 || score > 10)
            return false;
        else
            this->avgStatisScore = score;
        return true;
    }

protected:
    float avgStatisScore;
};

#endif
