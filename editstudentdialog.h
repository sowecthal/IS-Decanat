#ifndef EDITSTUDENTDIALOG_H
#define EDITSTUDENTDIALOG_H

#include "dataclasses/user.h"

#include <QDialog>

namespace Ui {
class editStudentDialog;
}

class EditStudentDialog : public QDialog
{
//    Q_OBJECT

public:
    explicit EditStudentDialog(User &sStuden, QWidget *parent = nullptr);
    ~EditStudentDialog();

private slots:
    void accept() Q_DECL_OVERRIDE;

private:
    Ui::editStudentDialog *ui;
    User& mStudent;
};

#endif // EDITSTUDENTDIALOG_H
