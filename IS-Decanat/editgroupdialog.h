#ifndef EDITGROUPDIALOG_H
#define EDITGROUPDIALOG_H

#include <QDialog>
#include "dataclasses/user.h"
#include "dataclasses/discipline.h"
#include "dataclasses/group.h"
#include <QStandardItemModel>

namespace Ui {
class EditGroupDialog;
}

class EditGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditGroupDialog(Group &sGroup, QWidget *parent = nullptr);
    ~EditGroupDialog();

private:
    void setData();
    Ui::EditGroupDialog *ui;
    Group& mGroup;
    QStandardItemModel* sModel;
    QStandardItemModel* dModel;

public slots:
    void accept() Q_DECL_OVERRIDE;
};

#endif // EDITGROUPDIALOG_H
