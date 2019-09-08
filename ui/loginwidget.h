#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <vector>
#include "io/data_repo.h"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private slots:
    void on_button_login_clicked();
    void on_button_exit_clicked();

private:
    Ui::LoginWidget *ui;

    DataRepo* dataRepo;
};

#endif // LOGINWIDGET_H
