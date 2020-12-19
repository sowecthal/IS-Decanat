#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <databases.h>

#include <QDialog>

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AuthWindow(DataBases sDB, QWidget *parent = nullptr);
    ~AuthWindow();
    //Возвращает значение поля lineLogin
    QString getLineLogin();
    //Возвращает значение поля linePassword
    QString getLinePassword();



public slots:
    //! Обрабатывает подтверждение диалога.
    void accept() Q_DECL_OVERRIDE;

private:
    DataBases db;
    Ui::AuthWindow *ui;

};

#endif // AUTHWINDOW_H
