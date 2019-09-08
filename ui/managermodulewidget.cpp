#include "managermodulewidget.h"
#include "ui_managermodulewidget.h"


ManagerModuleWidget::ManagerModuleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerModuleWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("管理员 - 教务管理系统");
}

ManagerModuleWidget::~ManagerModuleWidget()
{
    delete ui;
}

void ManagerModuleWidget::initData(long id, DataRepo *repo)
{
    this->id = id;
    this->dataRepo = repo;

    initTableModel();

    on_comboBox_item_currentIndexChanged(0);
}

void ManagerModuleWidget::initTableModel()
{
    string studentLabels[4] = {"学号", "姓名", "密码", "班级"};
    string teacherLabels[4] = {"教师号", "姓名", "密码", "教学评价"};
    string managerLables[4] = {"账号", "姓名", "密码", "权限"};
    string courseLabels[5] = {"课程号", "课程名称", "学分", "学时", "课程类型"};

    studentModel = new QStandardItemModel();
    for (int i = 0; i < 4; i++) {
        studentModel->setHorizontalHeaderItem(i, new QStandardItem(QObject::tr(studentLabels[i].data())));
    }
    teacherModel = new QStandardItemModel();
    for (int i = 0; i < 4; i++) {
        teacherModel->setHorizontalHeaderItem(i, new QStandardItem(QObject::tr(teacherLabels[i].data())));
    }
    managerModel = new QStandardItemModel();
    for (int i = 0; i < 4; i++) {
        managerModel->setHorizontalHeaderItem(i, new QStandardItem(QObject::tr(managerLables[i].data())));
    }
    courseModel = new QStandardItemModel();
    for (int i = 0; i < 5; i++) {
        courseModel->setHorizontalHeaderItem(i, new QStandardItem(QObject::tr(courseLabels[i].data())));
    }
}

void ManagerModuleWidget::updateTableModel(QTableView* table, QStandardItemModel* model, vector<QStringList> &datalistVec)
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

void ManagerModuleWidget::on_comboBox_item_currentIndexChanged(int index)
{
    vector<QStringList> datalistVec;
    switch (index) {
    case 0:
        for (auto it : dataRepo->studentVec) {
            QStringList datalist = it.toQStringList();
            datalistVec.push_back(datalist);
        }
        updateTableModel(ui->tableView, studentModel, datalistVec);
        break;
    case 1:
        for (auto it : dataRepo->teacherVec) {
            QStringList datalist = it.toQStringList();
            datalistVec.push_back(datalist);
        }
        updateTableModel(ui->tableView, teacherModel, datalistVec);
        break;
    case 2:
        for (auto it : dataRepo->managerVec) {
            QStringList datalist = it.toQStringList();
            datalistVec.push_back(datalist);
        }
        updateTableModel(ui->tableView, managerModel, datalistVec);
        break;
    case 3:
        for (auto it : dataRepo->courseVec) {
            QStringList datalist = it.toQStringList();
            datalistVec.push_back(datalist);
        }
        updateTableModel(ui->tableView, courseModel, datalistVec);
        break;
    default: return;
    }
}

void ManagerModuleWidget::on_button_add_clicked()
{
    switch (ui->comboBox_item->currentIndex()) {
    case 0:
        if (ui->button_add->text() == "添加") {
            ui->button_add->setText("确定");
            studentModel->setItem(studentModel->rowCount(), new QStandardItem(""));
        } else {
            ui->button_add->setText("添加");
            QStringList datalist;
            for (int i = 0; i < 4; i++) {
                datalist.push_back(studentModel->item(studentModel->rowCount()-1, i)->text());
            }
            dataRepo->appendStudent(*(new Student(datalist)));
        }
        break;
    case 1:
        if (ui->button_add->text() == "添加") {
            ui->button_add->setText("确定");
            teacherModel->setItem(teacherModel->rowCount(), new QStandardItem(""));
        } else {
            ui->button_add->setText("添加");
            QStringList datalist;
            for (int i = 0; i < 4; i++) {
                datalist.push_back(teacherModel->item(teacherModel->rowCount()-1, i)->text());
            }
            dataRepo->appendTeacher(*(new Teacher(datalist)));
        }
        break;
    case 2:
        if (ui->button_add->text() == "添加") {
            ui->button_add->setText("确定");
            managerModel->setItem(managerModel->rowCount(), new QStandardItem(""));
        } else {
            ui->button_add->setText("添加");
            QStringList datalist;
            for (int i = 0; i < 4; i++) {
                datalist.push_back(managerModel->item(managerModel->rowCount()-1, i)->text());
            }
            dataRepo->appendManager(*(new Manager(datalist)));
        }
        break;
    case 3:
        if (ui->button_add->text() == "添加") {
            ui->button_add->setText("确定");
            courseModel->setItem(courseModel->rowCount(), new QStandardItem(""));
        } else {
            ui->button_add->setText("添加");
            QStringList datalist;
            for (int i = 0; i < 5; i++) {
                datalist.push_back(courseModel->item(courseModel->rowCount()-1, i)->text());
            }
            dataRepo->appendCourse(*(new Course(datalist)));
        }
        break;
    default: return;
    }
}

void ManagerModuleWidget::on_button_delete_clicked()
{
    int index = ui->tableView->selectionModel()->currentIndex().row();

    Student student;
    Teacher teacher;
    Manager manager;
    Course course;

    switch (ui->comboBox_item->currentIndex()) {
    case 0:
        student.setID(studentModel->item(index, 0)->text().toLong());
        dataRepo->removeStudent(student);
        studentModel->removeRow(index);
        break;
    case 1:
        teacher.setID(teacherModel->item(index, 0)->text().toLong());
        dataRepo->removeTeacher(teacher);
        teacherModel->removeRow(index);
        break;
    case 2:
        manager.setID(managerModel->item(index, 0)->text().toLong());
        dataRepo->removeManager(manager);
        managerModel->removeRow(index);
        break;
    case 3:
        course.setID(courseModel->item(index, 0)->text().toLong());
        dataRepo->removeCourse(course);
        courseModel->removeRow(index);
        break;
    default: return;
    }
}

void ManagerModuleWidget::on_button_save_change_clicked()
{
    dataRepo->saveData();
}
