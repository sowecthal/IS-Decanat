#ifndef EDITGROUPDIALOG_H
#define EDITGROUPDIALOG_H

#include <QDialog>

namespace Ui {
class EditGroupDialog;
}

class EditGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditGroupDialog(QWidget *parent = nullptr);
    ~EditGroupDialog();

private:
    Ui::EditGroupDialog *ui;
};

#endif // EDITGROUPDIALOG_H
