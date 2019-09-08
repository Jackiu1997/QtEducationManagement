#ifndef MANAGERMODULEWIDGET_H
#define MANAGERMODULEWIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include "models/course/course_model.h"
#include "models/course/score_model.h"
#include "models/person/manager_model.h"
#include "models/person/student_model.h"
#include "models/person/teacher_model.h"
#include "io/data_repo.h"

namespace Ui {
class ManagerModuleWidget;
}

class ManagerModuleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerModuleWidget(QWidget *parent = nullptr);
    ~ManagerModuleWidget();

    void initData(long id, DataRepo* repo);
    void initTableModel();
    void updateTableModel(QTableView *table, QStandardItemModel *model, vector<QStringList> &datalistVec);

private slots:
    void on_comboBox_item_currentIndexChanged(int index);
    void on_button_add_clicked();
    void on_button_delete_clicked();
    void on_button_save_change_clicked();

private:
    Ui::ManagerModuleWidget *ui;

    QStandardItemModel* studentModel;
    QStandardItemModel* teacherModel;
    QStandardItemModel* managerModel;
    QStandardItemModel* courseModel;

    long id;
    DataRepo* dataRepo;
};

#endif // MANAGERMODULEWIDGET_H
