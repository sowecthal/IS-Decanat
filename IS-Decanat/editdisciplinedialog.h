#ifndef EDITDISCIPLINEDIALOG_H
#define EDITDISCIPLINEDIALOG_H

#include "dataclasses/discipline.h"
#include "dataclasses/group.h"
#include <QDialog>
#include <QStandardItemModel>
#include "databases.h"

namespace Ui {
class EditDisciplineDialog;
}

class EditDisciplineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDisciplineDialog(Discipline &sDiscipline, DataBases &sDB, QWidget *parent = nullptr);
    ~EditDisciplineDialog();

private:
    Ui::EditDisciplineDialog *ui;
    //! Создает и устанавливает модели
    void setData();

    int getFormIndex();

    Discipline::forms getFormByIndex(int index);

    Discipline &mDiscipline;
    QList<int> mGroups;
    QList<Group> oGroups;
    DataBases &mDB;
    QStandardItemModel *model;

private slots:
    void accept() Q_DECL_OVERRIDE;
    void on_MyGroups_activated(const QModelIndex &index);
    void find();
};

#endif // EDITDISCIPLINEDIALOG_H
