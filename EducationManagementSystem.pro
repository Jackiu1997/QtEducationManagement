#-------------------------------------------------
#
# Project created by QtCreator 2019-07-06T03:04:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += charts

TARGET = EducationManagementSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    main.cpp \
    io/data_repo.cpp \
    ui/loginwidget.cpp \
    ui/managermodulewidget.cpp \
    ui/studentmodulewidget.cpp \
    ui/teachermodulewidget.cpp

HEADERS += \
    io/data_io.h \
    io/data_repo.h \
    models/course/course_model.h \
    models/person/manager_model.h \
    models/person/person_model.h \
    models/person/student_model.h \
    models/person/teacher_model.h \
    ui/loginwidget.h \
    ui/managermodulewidget.h \
    ui/studentmodulewidget.h \
    ui/teachermodulewidget.h \
    models/course/teaching_class.h \
    models/course/score_model.h

FORMS += \
    ui/loginwidget.ui \
    ui/managermodulewidget.ui \
    ui/studentmodulewidget.ui \
    ui/teachermodulewidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc
