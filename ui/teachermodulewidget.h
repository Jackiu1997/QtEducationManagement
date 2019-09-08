#ifndef TEACHERMODULEWIDGET_H
#define TEACHERMODULEWIDGET_H


#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include "models/course/course_model.h"
#include "models/course/score_model.h"
#include "models/person/manager_model.h"
#include "models/person/student_model.h"
#include "models/person/teacher_model.h"
#include "io/data_repo.h"

#include <QtCharts>
#include <QChartView>
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class TeacherModuleWidget;
}

class TeacherModuleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherModuleWidget(QWidget *parent = nullptr);
    ~TeacherModuleWidget();

    void initData(long id, DataRepo* repo);
    void initTableModel();
    void updateTableModel(QTableView *table, QStandardItemModel *model, vector<QStringList> &datalistVec);

private slots:
    void on_button_search_clicked();
    void on_button_search_2_clicked();
    void on_button_save_score_clicked();
    void on_button_change_course_clicked();
    void on_button_analysis_clicked();
    void on_button_readFile_clicked();

    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::TeacherModuleWidget *ui;

    QStandardItemModel* scoreModel;
    QStandardItemModel* commentModel;

    vector<Score> nowClassScore;
    TeachingClass nowClass;
    vector<TeachingClass> teachClassVec;

    long id;
    DataRepo* dataRepo;
};

#endif // TEACHERMODULEWIDGET_H
