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

    void setUser(User *sUser);

private:
    Ui::EditUserDialog *ui;
    User& mUser;

public slots:
    //! Обрабатывает подтверждение диалога.
    void accept() Q_DECL_OVERRIDE;
};

#endif // EDITUSERDIALOG_H
