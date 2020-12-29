#include "editdisciplinedialog.h"
#include "ui_editdisciplinedialog.h"

#include <QMessageBox>
#include <QStandardItemModel>
#include <QString>
#include <QDebug>

EditDisciplineDialog::EditDisciplineDialog(Discipline &sDiscipline, QList<Group> allGroups, QWidget *parent) : mDiscipline(sDiscipline),
    oGroups(allGroups),
    QDialog(parent),
    ui(new Ui::EditDisciplineDialog)
{
    mGroups = mDiscipline.mGroups;
    ui->setupUi(this);
    ui->lineName->setMaxLength(150);
    ui->lineName->setText(mDiscipline.mName);
    ui->Form->setCurrentIndex(mDiscipline.mForm);
    ui->labelID->setText("Внутренний номер дисциплины: " + QString::number(mDiscipline.mDisciplineID));

    setData();
}

void EditDisciplineDialog::setData()
{
    mModel = new QStandardItemModel(mDiscipline.mGroups.length(), 1, this);
    oModel = new QStandardItemModel(oGroups.length() - mDiscipline.mGroups.length(), 1, this);
    mModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Номер группы")));
    oModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Номер группы")));

    for(int i = 0; i<oGroups.length(); i++)
    {
        qDebug() << oGroups[i].mNumber;
        if (mDiscipline.mGroups.contains(oGroups[i].mGroupID))
        {
            mModel->setItem(i,0,new QStandardItem(QString(oGroups[i].mNumber)));
        }
        else
        {
            oModel->setItem(i,0,new QStandardItem(QString(oGroups[i].mNumber)));
        }
    }
    ui->MyGroups->setModel(mModel);
    ui->OtherGroups->setModel(oModel);
}


EditDisciplineDialog::~EditDisciplineDialog()
{
    delete ui;
}

void EditDisciplineDialog::accept()
{
    //Если обнаруженно несовпадение значений - вызываем метод замены, закрываем с accept
    if (ui->lineName->text().isEmpty())
        QMessageBox::warning(this, "Ошибка", "Заполнены не все поля.");
    else if (mDiscipline.mName != ui->lineName->text() ||
             mDiscipline.mForm !=  ui->Form->currentIndex())
    {
        mDiscipline.mName = ui->lineName->text();
        mDiscipline.mForm = ui->Form->currentIndex();
        mDiscipline.mGroups = mGroups;
        QDialog::accept();
    }
    else QDialog::close();
}
