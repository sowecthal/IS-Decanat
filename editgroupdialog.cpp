#include "editgroupdialog.h"
#include "ui_editgroupdialog.h"

#include <QMessageBox>
#include <QStandardItemModel>

EditGroupDialog::EditGroupDialog(Group &sGroup, QWidget *parent) :
    mGroup(sGroup),
    QDialog(parent),
    ui(new Ui::EditGroupDialog)
{
    ui->setupUi(this);
    ui->lineNumber->setText(mGroup.mNumber);
    ui->labelID->setText("Внутренний номер группы: " + QString::number(mGroup.mGroupID));
    setData();
}

void EditGroupDialog::setData()
{
    sModel = new QStandardItemModel(mGroup.mStudents.length(), 1, this);
    dModel = new QStandardItemModel(mGroup.mDisciplines.length(), 1, this);
    sModel->setHorizontalHeaderItem(0, new QStandardItem(QString("ФИО")));
    dModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Наименование")));

    for(int i = 0; i<mGroup.mStudents.length(); i++)
        sModel->setItem(i,0,new QStandardItem(QString(mGroup.mStudents[i]->mSurname + " " + mGroup.mStudents[i]->mName + " " + mGroup.mStudents[i]->mPatronymic)));
    for(int i = 0; i<mGroup.mDisciplines.length(); i++)
        dModel->setItem(i,0,new QStandardItem(QString(mGroup.mDisciplines[i]->mName)));
    ui->tableStudents->setModel(sModel);
    ui->tableDisciplines->setModel(dModel);
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
