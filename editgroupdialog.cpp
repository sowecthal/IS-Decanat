#include "editgroupdialog.h"
#include "ui_editgroupdialog.h"

#include <QMessageBox>

EditGroupDialog::EditGroupDialog(Group &sGroup, QWidget *parent) :
    mGroup(sGroup),
    QDialog(parent),
    ui(new Ui::EditGroupDialog)
{
    ui->setupUi(this);
    ui->lineNumber->setText(mGroup.mNumber);
    ui->labelID->setText("Внутренний номер группы: " + QString::number(mGroup.mGroupID));
}

EditGroupDialog::~EditGroupDialog()
{
    delete ui;
}

void EditGroupDialog::accept()
{
    if (ui->lineNumber->text().isEmpty())
        QMessageBox::warning(this, "Ошибка", "Заполнены не все поля.");
    else if (mGroup.mNumber != ui->lineNumber->text())
    {
        mGroup.mNumber = ui->lineNumber->text();
        QDialog::accept();
    }
    else QDialog::close();
}
