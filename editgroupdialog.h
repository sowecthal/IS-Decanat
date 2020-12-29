#ifndef EDITGROUPDIALOG_H
#define EDITGROUPDIALOG_H

#include <QDialog>
#include "dataclasses/user.h"
#include "dataclasses/discipline.h"
#include "dataclasses/group.h"


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
    Ui::EditGroupDialog *ui;
    Group& mGroup;

public slots:
    void accept() Q_DECL_OVERRIDE;
};

#endif // EDITGROUPDIALOG_H
