#include "teachermodulewidget.h"
#include "ui_teachermodulewidget.h"
#include <QMessageBox>
#include <cmath>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>

TeacherModuleWidget::TeacherModuleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeacherModuleWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("教师 - 教务管理系统");
}

TeacherModuleWidget::~TeacherModuleWidget()
{
    delete ui;
}

void TeacherModuleWidget::initData(long id, DataRepo *repo)
{
    this->id = id;
    this->dataRepo = repo;

    // 设置教师教授课程
    for (auto it : dataRepo->classVec) {
        // 教师教授课程
        if (it.getTeacherID() == id) {
            teachClassVec.push_back(it);
            QString item = QString::number(it.getClassID()) + ", ";
            for (auto it1 : dataRepo->courseVec) {
                if (it1.getID() == it.getCourseID()) {
                    // 获取课程名称
                    item += it1.toQStringList().join(", ");
                }
            }
            ui->comboBox_course->addItem(item);
        }
    }

    initTableModel();

    on_button_change_course_clicked();
    on_button_search_clicked();
    on_button_search_2_clicked();
}

void TeacherModuleWidget::initTableModel()
{

    string labels1[4] = {"学号", "姓名", "班级", "成绩"};

    scoreModel = new QStandardItemModel();
    commentModel = new QStandardItemModel();
    for (int i = 0; i < 4; i++) {
        scoreModel->setHorizontalHeaderItem(i, new QStandardItem(QObject::tr(labels1[i].data())));
    }
}

void TeacherModuleWidget::updateTableModel(QTableView* table, QStandardItemModel* model, vector<QStringList> &datalistVec)
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

// 学生成绩查询按钮响应
void TeacherModuleWidget::on_button_search_clicked()
{
    QString keyWord = ui->edit_search->text();
    vector<QStringList> datalistVec;

    for (auto it : nowClassScore) {
        // 关键词搜索学生
        Student nowStudent = dataRepo->findStudentByID(it.getStudentID());
        if (QString::fromStdString(nowStudent.getName()).contains(keyWord)
                || QString::number(nowStudent.getID()).contains(keyWord))
        {
            QStringList datalist = nowStudent.toQStringList();// 学生信息
            datalist.removeAt(2);
            datalist.append(QString::number(it.getScore()));// 成绩
            datalistVec.push_back(datalist);
        }
    }
    updateTableModel(ui->tableView_set_score, scoreModel, datalistVec);
}

// 保存更改学生成绩按钮响应
void TeacherModuleWidget::on_button_save_score_clicked()
{
    for (int i = 0; i < scoreModel->rowCount(); i++) {
        long classID = nowClass.getClassID();
        long studentID = scoreModel->item(i, 0)->text().toLong();
        int score = scoreModel->item(i, 3)->text().toInt();

        Score temp;
        temp.setClassID(classID);
        temp.setStudentID(studentID);
        temp.setScore(score);

        dataRepo->appendScore(temp);

        nowClassScore.clear();
        for (auto it : dataRepo->scoreVec) {
            if (it.getClassID() == nowClass.getClassID()) {
                nowClassScore.push_back(it);
            }
        }
    }

    dataRepo->saveData();
}

// 学生成绩查询按钮2响应
void TeacherModuleWidget::on_button_search_2_clicked()
{
    ui->tableView_score->setSortingEnabled(true);
    QString lowMark = ui->edit_low->text().trimmed();
    QString highMark = ui->edit_high->text().trimmed();
    QString classNo = ui->comboBox_classNo->currentText().trimmed();
    QString keyWord = ui->edit_student->text().trimmed();
    vector<QStringList> datalistVec;

    for (auto it : nowClassScore) {
        Student nowStudent = dataRepo->findStudentByID(it.getStudentID());

        // 按班级筛选学生
        if (classNo == "所有班级");
        else if (classNo == QString::number(nowStudent.getClassNo()));
        else continue;

        // 关键词筛选学生
        if (QString::fromStdString(nowStudent.getName()).contains(keyWord)
                || QString::number(nowStudent.getID()).contains(keyWord));
        else continue;

        // 按成绩区间筛选
        if (lowMark == "" || highMark == "");
        else if (it.getScore() >= lowMark.toInt() && it.getScore() <= highMark.toInt());
        else continue;

        QStringList datalist = nowStudent.toQStringList();// 学生信息
        datalist.removeAt(2);
        datalist.append(QString::number(it.getScore()));// 成绩
        datalistVec.push_back(datalist);
    }
    updateTableModel(ui->tableView_score, scoreModel, datalistVec);
}



void TeacherModuleWidget::on_button_change_course_clicked()
{
    // 设置当前查询课程
    nowClass = teachClassVec.at(ui->comboBox_course->currentIndex());
    nowClassScore.clear();
    for (auto it : dataRepo->scoreVec) {
        if (it.getClassID() == nowClass.getClassID()) {
            nowClassScore.push_back(it);
        }
    }

    // 成绩查询页面
    ui->comboBox_classNo->clear();
    ui->comboBox_classNo->addItem("所有班级");
    for (auto it : nowClassScore) {
        Student nowStudent = dataRepo->findStudentByID(it.getStudentID());
        ui->comboBox_classNo->addItem(QString::number(nowStudent.getClassNo()));
    }
}

void TeacherModuleWidget::on_button_analysis_clicked()
{
    double avgScore = 0.0, stdEv = 0.0, passRate = 0.0;

    for (auto it : nowClassScore) {
        avgScore += it.getScore();
        if (it.getScore() >= 60) passRate += 1;
    }
    avgScore /= nowClassScore.size();
    passRate /= nowClassScore.size();

    for (auto it : nowClassScore) {
        stdEv += pow(it.getScore() / avgScore, 2);
    }
    stdEv = sqrt(stdEv);

    QMessageBox msgBox;
    QString showText = "平均值：  " + QString::number(avgScore)
                       + "\n标准差：  " + QString::number(stdEv)
                       + "\n通过率：  " + QString::number(passRate*100) + "%";
    msgBox.setText(showText);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Close);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void TeacherModuleWidget::on_tabWidget_tabBarClicked(int index)
{
    if (index == 2) {
        // 统计分析界面
        int data[10] = {0,0,0,0,0,0,0,0,0,0}, max = data[0];
        for (auto it : nowClassScore) {
            int index = it.getScore() / 10;
            data[index] += 1;
            max = data[index] >= max ? data[index] : max;
        }
        // 设置柱
        QChart *chart = new QChart();
        QBarSeries *series = new QBarSeries();
        QBarSet *set = new QBarSet("学生成绩");
        for (int i = 0; i < 10; i++) *set << data[i];

        series->append(set);
        chart->addSeries(series);
        chart->setTitle("学生成绩分布直方图");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        // 设置 X 轴
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        QStringList categories;
        for (int i = 0; i < 10; i++) {
            categories << QString::number(10*i) + " - " + QString::number(10*i+9);
        }
        axis->append(categories);
        chart->setAxisX(axis, series);      //设置坐标轴

        // 设置 Y 轴
        QValueAxis *yAxis = new QValueAxis;
        yAxis->setRange(0, max);
        yAxis->setMinorTickCount(10);       //设置每格小刻度线的数目
        chart->setAxisY(yAxis, series);

        ui->chartWidget->setChart(chart);
    }
    else if(index == 3) {
        // 课程评价页面
        int i = 0;
        ui->listView_comment->setModel(commentModel);
        commentModel->removeRows(0, commentModel->rowCount());
        for (auto it : nowClassScore) {
            QString commentlist = "满意度:  " + QString::number(it.getStaticScore())
                                    + "\n评   语:  " + QString::fromStdString(it.getComment());
            commentModel->setItem(i++, 0, new QStandardItem(commentlist));
        }
    }
}

void TeacherModuleWidget::on_button_readFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Text (*.txt *.csv)");
    vector<QStringList> datalistVec = DataIO::csvLoader(filePath.toStdString());

    for (auto it : datalistVec) {
        long studentid = it[0].toLong();
        int score = it[1].toInt();
        for (auto &it1 : dataRepo->scoreVec) {
            if (nowClass.getClassID() == it1.getClassID()
                    && studentid == it1.getStudentID())
            {
                it1.setScore(score);
            }
        }
    }

    nowClassScore.clear();
    for (auto it : dataRepo->scoreVec) {
        if (it.getClassID() == nowClass.getClassID()) {
            nowClassScore.push_back(it);
        }
    }
}
