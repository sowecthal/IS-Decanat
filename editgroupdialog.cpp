#include "editgroupdialog.h"
#include "ui_editgroupdialog.h"

EditGroupDialog::EditGroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditGroupDialog)
{
    ui->setupUi(this);
}

EditGroupDialog::~EditGroupDialog()
{
    delete ui;
}
