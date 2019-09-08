#include "studentmodulewidget.h"
#include "ui_studentmodulewidget.h"

#include <QMessageBox>

StudentModuleWidget::StudentModuleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentModuleWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("学生 - 教务管理系统");
}

StudentModuleWidget::~StudentModuleWidget()
{
    delete ui;
}

void StudentModuleWidget::initData(long id, DataRepo *repo)
{
    this->id = id;
    this->dataRepo = repo;

    initTableModel();

    // 设置学生信息标签
    auto datalist = dataRepo->findStudentByID(id).toQStringList();
    ui->label_id->setText(datalist[0]);
    ui->label_name->setText(datalist[1]);
    ui->label_classno->setText(datalist[3]);

    on_button_search_clicked();
}

void StudentModuleWidget::initTableModel()
{
    string labels1[7] = {"课程号", "课程名称", "学分", "学时", "课程类型", "教学班", "教师"};
    string labels2[10] = {"课程号", "课程名称", "学分", "学时", "课程类型", "教学班", "教师", "成绩", "满意度", "评语"};

    tab1Model = new QStandardItemModel();
    for (int i = 0; i < 7; i++) {
        tab1Model->setHorizontalHeaderItem(i, new QStandardItem(QObject::tr(labels1[i].data())));
    }
    tab2Model = new QStandardItemModel();
    for (int i = 0; i < 10; i++) {
        tab2Model->setHorizontalHeaderItem(i, new QStandardItem(QObject::tr(labels2[i].data())));
    }
}

void StudentModuleWidget::updateTableModel(QTableView* table, QStandardItemModel* model, vector<QStringList> &datalistVec)
{
    table->setModel(model);
    model->removeRows(0, model->rowCount());
    for (int i = 0; i < datalistVec.size(); i++) {
        QStringList datalist = datalistVec[i];
        for (int j = 0; j < datalist.size(); j++) {
            model->setItem(i, j, new QStandardItem(datalist[j]));
        }
    }
}

// 关键词搜索按钮响应
void StudentModuleWidget::on_button_search_clicked()
{
    // 开启选课按钮
    ui->button_enter_course->setEnabled(true);

    QString keyWord = ui->edit_search->text();
    vector<QStringList> datalistVec;

    for (auto it : dataRepo->courseVec) {
        if (QString::fromStdString(it.getName()).contains(keyWord)
                || QString::number(it.getID()).contains(keyWord))
        {
            QStringList datalist = it.toQStringList();// 课程信息
            for (auto it1 : dataRepo->classVec) {
                // 教学班信息
                if (it1.getCourseID() == it.getID()) {
                    QStringList listNew = datalist;
                    listNew.append(QString::number(it1.getClassID()));
                    listNew.append(QString::fromStdString(dataRepo->findTeacherByID(it1.getTeacherID()).getName()));
                    datalistVec.push_back(listNew);
                }
            }
        }
    }
    updateTableModel(ui->tableView_course, tab1Model, datalistVec);
}

// 选课按钮响应
void StudentModuleWidget::on_button_enter_course_clicked()
{
    int index = ui->tableView_course->selectionModel()->currentIndex().row();

    Score score;
    score.setClassID(tab1Model->item(index, 5)->text().toLong());
    score.setStudentID(id);
    if (dataRepo->appendScore(score)) {
        QMessageBox::information(this, "提示信息", "选课成功！", QMessageBox::Ok);
    } else {
        QMessageBox::information(this, "提示信息", "选课失败！", QMessageBox::Ok);
    }

    dataRepo->saveData();
}

// 退课按钮响应
void StudentModuleWidget::on_button_exit_course_clicked()
{
    int index = ui->tableView_course->selectionModel()->currentIndex().row();

    Score score;
    score.setClassID(tab1Model->item(index, 5)->text().toLong());
    score.setStudentID(id);
    if (dataRepo->removeScore(score)) {
        QMessageBox::information(this, "提示信息", "退课成功！", QMessageBox::Ok);
    } else {
        QMessageBox::information(this, "提示信息", "退课失败！", QMessageBox::Ok);
    }

    dataRepo->saveData();
}

// 已选课程按钮响应
void StudentModuleWidget::on_button_entered_clicked()
{
    // 关闭选课按钮
    ui->button_enter_course->setEnabled(false);

    int allCredit = 0;
    vector<QStringList> datalistVec;

    for (auto it : dataRepo->scoreVec) {
        if (it.getStudentID() == id) {// 学生ID
            for (auto it1 : dataRepo->classVec) {
                if (it1.getClassID() == it.getClassID()) {// 教学班ID
                    for (auto it2 : dataRepo->courseVec) {
                        if (it1.getCourseID() == it2.getID()) {// 课程ID
                            QStringList datalist = it2.toQStringList();// 课程信息
                            datalist.append(QString::number(it1.getClassID()));
                            datalist.append(QString::fromStdString(dataRepo->findTeacherByID(it1.getTeacherID()).getName()));
                            datalistVec.push_back(datalist);

                            allCredit += it2.getCredits();
                        }
                    }
                }
            }
        }
    }
    updateTableModel(ui->tableView_course, tab1Model, datalistVec);

    ui->button_entered->setText("已选课程（总学分：" + QString::number(allCredit) + "）");
}

void StudentModuleWidget::on_tabWidget_tabBarClicked(int index)
{
    auto datalist = dataRepo->findStudentByID(id).toQStringList();

    switch (index) {
    case 0:
        on_button_search_clicked();
        break;
    case 1:
        vector<QStringList> datalistVec;
        for (auto it : dataRepo->scoreVec) {
            if (it.getStudentID() == id) {// 学生ID
                for (auto it1 : dataRepo->classVec) {
                    if (it1.getClassID() == it.getClassID()) {// 教学班ID
                        for (auto it2 : dataRepo->courseVec) {
                            if (it1.getCourseID() == it2.getID()) {// 课程ID
                                // 课程信息
                                QStringList datalist = it2.toQStringList();
                                // 教学班信息
                                datalist.append(QString::number(it1.getClassID()));
                                datalist.append(QString::fromStdString(dataRepo->findTeacherByID(it1.getTeacherID()).getName()));
                                // 成绩信息
                                datalist.append(QString::number(it.getScore()));
                                datalist.append(QString::number(it.getStaticScore()));
                                datalist.append(QString::fromStdString(it.getComment()));
                                datalistVec.push_back(datalist);
                            }
                        }
                    }
                }
            }
        }
        updateTableModel(ui->tableView_score, tab2Model, datalistVec);
        break;
    }
}
