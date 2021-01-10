#ifndef EDITUSERDIALOG_H
#define EDITUSERDIALOG_H

#include <QDialog>
#include <dataclasses/user.h>

namespace Ui {
class EditUserDialog;
}

class EditUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserDialog(User &sUser, QWidget *parent = nullptr);
    ~EditUserDialog();

private:
    Ui::EditUserDialog *ui;
    User &mUser;

    //! Метод получения выбранной роли
    User::roles getSelectedRole();

public slots:
    //! Обрабатывает подтверждение диалога.
    void accept() Q_DECL_OVERRIDE;
};

#endif // EDITUSERDIALOG_H
