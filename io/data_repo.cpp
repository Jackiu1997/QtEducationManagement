#include "data_repo.h"

DataRepo::DataRepo()
{
    studentVec = DataIO::loadStudentFile("./assets/data/student.txt");
    teacherVec = DataIO::loadTeacherFile("./assets/data/staff.txt");
    managerVec = DataIO::loadManagerFile("./assets/data/manager.txt");
    courseVec = DataIO::loadCourseFile("./assets/data/course.txt");
    classVec = DataIO::loadClassFile("./assets/data/class.txt");
    scoreVec = DataIO::loadScoreFile("./assets/data/score.txt");
}

void DataRepo::saveData()
{
    DataIO::saveStudentFile("./assets/data/student.txt", studentVec);
    DataIO::saveTeacherFile("./assets/data/staff.txt", teacherVec);
    DataIO::saveManagerFile("./assets/data/manager.txt", managerVec);
    DataIO::saveCourseFile("./assets/data/course.txt", courseVec);
    DataIO::saveClassFile("./assets/data/class.txt", classVec);
    DataIO::saveScoreFile("./assets/data/score.txt", scoreVec);
}

Course& DataRepo::findCourseByID(long id) {
    for (auto &it : courseVec) {
        if (it.getID() == id) return it;
    }
    return *courseVec.end();
}
Teacher& DataRepo::findTeacherByID(long id) {
    for (auto &it : teacherVec) {
        if (it.getID() == id) return it;
    }
    return *teacherVec.end();
}
Student& DataRepo::findStudentByID(long id) {
    for (auto &it : studentVec) {
        if (it.getID() == id) return it;
    }
    return *studentVec.end();
}

// 添加信息
bool DataRepo::appendStudent(Student& student) {
    for (auto it : studentVec) {
        if (student.getID() == it.getID())
            return false;
    }
    studentVec.push_back(student);
    return true;
}
bool DataRepo::appendTeacher(Teacher& teacher) {
    for (auto it : teacherVec) {
        if (teacher.getID() == it.getID())
            return false;
    }
    teacherVec.push_back(teacher);
    return true;
}
bool DataRepo::appendManager(Manager& manager) {
    for (auto it : managerVec) {
        if (manager.getID() == it.getID())
            return false;
    }
    managerVec.push_back(manager);
    return true;
}
bool DataRepo::appendCourse(Course& course) {
    for (auto it : courseVec) {
        if (course.getID() == it.getID())
            return false;
    }
    courseVec.push_back(course);
    return true;
}
bool DataRepo::appendClass(TeachingClass& t_class) {
    for (auto it : classVec) {
        if (t_class.getClassID() == it.getClassID())
            return false;
    }
    for (auto it : courseVec) {
        if (t_class.getCourseID() == it.getID()) {
            for (auto it : teacherVec) {
                if (t_class.getTeacherID() == it.getID()) {
                    classVec.push_back(t_class);
                }
            }
        }
    }
    return false;
}
bool DataRepo::appendScore(Score& score) {
    for (auto &it : scoreVec) {
        if (score.getClassID() == it.getClassID()
                && score.getStudentID() == it.getStudentID())
        {
            // 替换
            if (score.getScore() != 0) it = score;
            return false;
        }
    }
    scoreVec.push_back(score);
    return true;
}

// 删除信息
bool DataRepo::removeStudent(Student& student) {
    for (auto it = studentVec.begin(); it != studentVec.end(); it++) {
        if (student.getID() == it->getID()) {
            studentVec.erase(it);
            return true;
        }
    }
    return false;
}
bool DataRepo::removeTeacher(Teacher& teacher) {
    for (auto it = teacherVec.begin(); it != teacherVec.end(); it++) {
        if (teacher.getID() == it->getID()) {
            teacherVec.erase(it);
            return true;
        }
    }
    return false;
}
bool DataRepo::removeManager(Manager& manager) {
    for (auto it = managerVec.begin(); it != managerVec.end(); it++) {
        if (manager.getID() == it->getID()) {
            managerVec.erase(it);
            return true;
        }
    }
    return false;
}
bool DataRepo::removeCourse(Course& course) {
    for (auto it = courseVec.begin(); it != courseVec.end(); it++) {
        if (course.getID() == it->getID()) {
            courseVec.erase(it);
            return true;
        }
    }
    return false;
}
bool DataRepo::removeClass(TeachingClass& t_class) {
    for (auto it = classVec.begin(); it != classVec.end(); it++) {
        if (t_class.getClassID() == it->getClassID()) {
            classVec.erase(it);
            return true;
        }
    }
    return false;
}
bool DataRepo::removeScore(Score& score) {
    for (auto it = scoreVec.begin(); it != scoreVec.end(); it++) {
        if (score.getClassID() == it->getClassID()
                && score.getStudentID() == it->getStudentID()
                && it->getScore() == 0)
        {
            scoreVec.erase(it);
            return true;
        }
    }
    return false;
}
