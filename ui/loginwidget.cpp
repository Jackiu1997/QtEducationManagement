#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "studentmodulewidget.h"
#include "teachermodulewidget.h"
#include "managermodulewidget.h"

#include <QMessageBox>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("教务管理系统登录");

    ui->edit_pwd->setEchoMode(QLineEdit::Password);

    dataRepo = new DataRepo();
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_button_login_clicked()
{
    long id = ui->edit_id->text().toLong();
    std::string pwd = ui->edit_pwd->text().toStdString();

    for (auto it : dataRepo->managerVec) {
        if (it.getID() == id && it.getPassword() == pwd) {
            // 管理员登陆
            auto w = new ManagerModuleWidget();
            w->initData(id, dataRepo);
            this->hide();
            w->show();
            return;
        }
    }
    for (auto it : dataRepo->teacherVec) {
        if (it.getID() == id && it.getPassword() == pwd) {
            // 教师登陆
            auto w = new TeacherModuleWidget();
            w->initData(id, dataRepo);
            this->hide();
            w->show();
            return;
        }
    }
    for (auto it : dataRepo->studentVec) {
        if (it.getID() == id && it.getPassword() == pwd) {
            // 学生登陆
            auto w = new StudentModuleWidget();
            w->initData(id, dataRepo);
            this->hide();
            w->show();
            return;
        }
    }

    QMessageBox::information(this, "登录错误", "账号或密码错误！请重新输入！", QMessageBox::Ok);
}

void LoginWidget::on_button_exit_clicked()
{
    this->close();
}
