#ifndef DATA_REPO_H
#define DATA_REPO_H

#include <iostream>
#include <vector>
#include "../models/course/course_model.h"
#include "../models/course/score_model.h"
#include "../models/person/manager_model.h"
#include "../models/person/student_model.h"
#include "../models/person/teacher_model.h"
#include "data_io.h"

class DataRepo
{
public:
    DataRepo();
    void saveData();

    // 查询信息
    Course& findCourseByID(long id);
    Teacher& findTeacherByID(long id);
    Student& findStudentByID(long id);

    // 添加信息
    bool appendStudent(Student& student);
    bool appendTeacher(Teacher& teacher);
    bool appendManager(Manager& manager);
    bool appendCourse(Course& course);
    bool appendClass(TeachingClass& t_class);
    bool appendScore(Score& score);

    // 删除信息
    bool removeStudent(Student& student);
    bool removeTeacher(Teacher& teacher);
    bool removeManager(Manager& manager);
    bool removeCourse(Course& course);
    bool removeClass(TeachingClass& t_class);
    bool removeScore(Score& score);


    // 人员数据
    std::vector<Student> studentVec;
    std::vector<Teacher> teacherVec;
    std::vector<Manager> managerVec;
    // 课程/成绩数据
    std::vector<Course> courseVec;
    std::vector<TeachingClass> classVec;
    std::vector<Score> scoreVec;

};

#endif // DATA_REPO_H
