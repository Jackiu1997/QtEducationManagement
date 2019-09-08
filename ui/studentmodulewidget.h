#ifndef STUDENTMODULEWIDGET_H
#define STUDENTMODULEWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include "models/course/course_model.h"
#include "models/course/score_model.h"
#include "models/person/manager_model.h"
#include "models/person/student_model.h"
#include "models/person/teacher_model.h"
#include "io/data_repo.h"

namespace Ui {
class StudentModuleWidget;
}

class StudentModuleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StudentModuleWidget(QWidget *parent = nullptr);
    ~StudentModuleWidget();

    void initData(long id, DataRepo* repo);
    void initTableModel();
    void updateTableModel(QTableView *table, QStandardItemModel *model, vector<QStringList> &datalistVec);

private slots:
    void on_button_search_clicked();
    void on_button_enter_course_clicked();
    void on_button_exit_course_clicked();
    void on_button_entered_clicked();

    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::StudentModuleWidget *ui;

    QStandardItemModel* tab1Model;
    QStandardItemModel* tab2Model;

    long id;
    DataRepo* dataRepo;
};

#endif // STUDENTMODULEWIDGET_H
