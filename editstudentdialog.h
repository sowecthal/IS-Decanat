#ifndef EDITSTUDENTDIALOG_H
#define EDITSTUDENTDIALOG_H

#include "dataclasses/user.h"
#include "dataclasses/group.h"
#include "databases.h"

#include <QDialog>

namespace Ui {
class editStudentDialog;
}

class EditStudentDialog : public QDialog
{
//    Q_OBJECT

public:
    explicit EditStudentDialog(User &sStuden, QList<Group> sGroups, DataBases &sDB, QWidget *parent = nullptr);
    ~EditStudentDialog();

private slots:
    void accept() Q_DECL_OVERRIDE;

private:
    Ui::editStudentDialog *ui;
    User& mStudent;
    DataBases& mDB;
    QList<Group> mGroups;
    QList<QString> GroupsNumbers;
};

#endif // EDITSTUDENTDIALOG_H
