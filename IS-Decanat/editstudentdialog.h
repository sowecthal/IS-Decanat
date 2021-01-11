#ifndef EDITSTUDENTDIALOG_H
#define EDITSTUDENTDIALOG_H

#include "dataclasses/user.h"
#include "dataclasses/group.h"
#include "dataclasses/grade.h"
#include "databases.h"

#include <QStandardItemModel>
#include <QDialog>

namespace Ui {
class editStudentDialog;
}

class editStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editStudentDialog(User &sStuden, QList<Group> sGroups, DataBases &sDB, QWidget *parent = nullptr);
    ~editStudentDialog();

private:
    Ui::editStudentDialog *ui;
    User& mStudent;
    DataBases& mDB;
    Group *mGroup;
    QList<Group> mGroups;
    QList<QString> GroupsNumbers;
    QStandardItemModel* model;
    //! Индикатор изменений.
    bool ind = false;
    //! Установка данных в таблицу.
    void setData();
    //! Получение индекса для QComboBox.
    int getGrantIndex();
    //! Получение enum-типа стипендии по индексу в QComboBox.
    User::grants getGrantByIndex(int index);

    Grade::grades findGrade(int fDisciplineID);

private slots:
     void accept() Q_DECL_OVERRIDE;
     void setGradeThis();
     void on_tableView_clicked(const QModelIndex &index);
};

#endif // EDITSTUDENTDIALOG_H
