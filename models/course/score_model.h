#ifndef COURSE_SCORE_H
#define COURSE_SCORE_H

#include <iostream>
#include <vector>
#include "teaching_class.h"
using std::string;

class Score {
public:
    Score() {}

    Score(QStringList datalist) {
        setClassID(datalist[0].toLong());
        setStudentID(datalist[1].toLong());
        setScore(datalist[2].toInt());
        setStaticScore(datalist[3].toInt());
        setComment(datalist[4].toStdString());
    }
    QStringList toQStringList() {
        QStringList datalist;
        datalist.append(QString::number(getClassID()));
        datalist.append(QString::number(getStudentID()));
        datalist.append(QString::number(getScore()));
        datalist.append(QString::number(getStaticScore()));
        datalist.append(QString::fromStdString(getComment()));
        return datalist;
    }

    long getClassID() { return classID; }
    long getStudentID() { return studentID; }
    int getScore() { return score; }
    string getComment() { return comment; }
    int getStaticScore() { return statisScore; }

    bool setClassID(long id) {
        if (id < 0)
            return false;
        else
            classID = id;
        return true;
    }
    bool setStudentID(long id) {
        if (id < 0)
            return false;
        else
            studentID = id;
        return true;
    }
    bool setScore(int score) {
        if (score < 0 || score > 100)
            return false;
        else
            this->score = score;
        return true;
    }
    bool setComment(string comment) {
        this->comment = comment;
        return true;
    }
    bool setStaticScore(int score) {
        if (score < 0 || score > 10)
            return false;
        else
            this->statisScore = score;
        return true;
    }

protected:
    long classID;
    long studentID;
    int score = 0;
    int statisScore = 0;
    string comment = "请填写对老师的教学评价";
};

#endif
