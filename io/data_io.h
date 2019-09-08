#ifndef DATA_IO_H
#define DATA_IO_H

#include <fstream>
#include <iostream>
#include <vector>
#include "../models/course/course_model.h"
#include "../models/course/score_model.h"
#include "../models/person/manager_model.h"
#include "../models/person/student_model.h"
#include "../models/person/teacher_model.h"
#include <QFile>
#include <QTextStream>
using std::vector;


class DataIO {
public:
    static std::vector<QStringList> csvLoader(std::string file_path) {
        std::vector<QStringList> datalistVec;
        QFile infile(QString::fromStdString(file_path));
        if (infile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream *out = new QTextStream(&infile);
            QStringList tempOption = out->readAll().split("\n");
            for (int i = 0; i < tempOption.count(); i++) {
                QStringList dataList = tempOption.at(i).split(",");
                if (dataList[0] == "") break;
                datalistVec.push_back(dataList);
            }
        }
        infile.close();
        return datalistVec;
    }

    static bool csvSaver(std::string file_path, vector<QStringList>& datalsitVec) {
        QFile outfile(QString::fromStdString(file_path));
        if (outfile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream outStream(&outfile);
            for (auto datalist : datalsitVec) {
                for (auto data : datalist) {
                    outStream << data << ",";
                }
                outStream << "\n";
            }
            outfile.close();
        } else {
            outfile.close();
            return false;
        }
        return true;
    }

    /* 从数据文件读取信息 */
    static std::vector<Student> loadStudentFile(std::string file_path) {
        std::vector<Student> studentVec;
        std::vector<QStringList> datalistVec = csvLoader(file_path);
        for (auto data : datalistVec) {
            studentVec.push_back(Student(data));
        }
        return studentVec;
    }

    static std::vector<Teacher> loadTeacherFile(std::string file_path) {
        std::vector<Teacher> teacherVec;
        std::vector<QStringList> datalistVec = csvLoader(file_path);
        for (auto data : datalistVec) {
            teacherVec.push_back(Teacher(data));
        }
        return teacherVec;
    }

    static std::vector<Manager> loadManagerFile(std::string file_path) {
        std::vector<Manager> managerVec;
        std::vector<QStringList> datalistVec = csvLoader(file_path);
        for (auto data : datalistVec) {
            managerVec.push_back(Manager(data));
        }
        return managerVec;
    }

    static std::vector<Course> loadCourseFile(std::string file_path) {
        std::vector<Course> courseVec;
        std::vector<QStringList> datalistVec = csvLoader(file_path);
        for (auto data : datalistVec) {
            courseVec.push_back(Course(data));
        }
        return courseVec;
    }

    static std::vector<Score> loadScoreFile(std::string file_path) {
        std::vector<Score> scoreVec;
        std::vector<QStringList> datalistVec = csvLoader(file_path);
        for (auto data : datalistVec) {
            scoreVec.push_back(Score(data));
        }
        return scoreVec;
    }

    static std::vector<TeachingClass> loadClassFile(std::string file_path) {
        std::vector<TeachingClass> classVec;
        std::vector<QStringList> datalistVec = csvLoader(file_path);
        for (auto data : datalistVec) {
            classVec.push_back(TeachingClass(data));
        }
        return classVec;
    }

    /* 向数据文件存储信息 */
    static bool saveStudentFile(std::string file_path, vector<Student>& vec) {
        std::vector<QStringList> datalistVec;
        for (auto data : vec) {
            datalistVec.push_back(data.toQStringList());
        }
        csvSaver(file_path, datalistVec);
        return true;
    }

    static bool saveTeacherFile(std::string file_path, vector<Teacher>& vec) {
        std::vector<QStringList> datalistVec;
        for (auto data : vec) {
            datalistVec.push_back(data.toQStringList());
        }
        csvSaver(file_path, datalistVec);
        return true;
    }

    static bool saveManagerFile(std::string file_path, vector<Manager>& vec) {
        std::vector<QStringList> datalistVec;
        for (auto data : vec) {
            datalistVec.push_back(data.toQStringList());
        }
        csvSaver(file_path, datalistVec);
        return true;
    }

    static bool saveCourseFile(std::string file_path, vector<Course>& vec) {
        std::vector<QStringList> datalistVec;
        for (auto data : vec) {
            datalistVec.push_back(data.toQStringList());
        }
        csvSaver(file_path, datalistVec);
        return true;
    }

    static bool saveScoreFile(std::string file_path, vector<Score>& vec) {
        std::vector<QStringList> datalistVec;
        for (auto data : vec) {
            datalistVec.push_back(data.toQStringList());
        }
        csvSaver(file_path, datalistVec);
        return true;
    }

    static bool saveClassFile(std::string file_path, vector<TeachingClass>& vec) {
        std::vector<QStringList> datalistVec;
        for (auto data : vec) {
            datalistVec.push_back(data.toQStringList());
        }
        csvSaver(file_path, datalistVec);
        return true;
    }
};

#endif


