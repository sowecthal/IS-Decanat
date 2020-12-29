#ifndef EDITDISCIPLINEDIALOG_H
#define EDITDISCIPLINEDIALOG_H

#include "dataclasses/discipline.h"
#include "dataclasses/group.h"
#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class EditDisciplineDialog;
}

class EditDisciplineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDisciplineDialog(Discipline &sDiscipline, QList<Group> allGroups, QWidget *parent = nullptr);
    ~EditDisciplineDialog();

private:
    Ui::EditDisciplineDialog *ui;
    //! Создает и устанавливает модели
    void setData();

    Discipline& mDiscipline;
    QList<Group> oGroups;
    QList<int> mGroups;
    QStandardItemModel* mModel;
    QStandardItemModel* oModel;

private slots:
    void accept() Q_DECL_OVERRIDE;
    void on_MyGroups_activated(const QModelIndex &index);
    void on_OtherGroups_activated(const QModelIndex &index);
};

#endif // EDITDISCIPLINEDIALOG_H
