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
    mModel = new QStandardItemModel(mGroups.length(), 1, this);
    oModel = new QStandardItemModel(oGroups.length() - mGroups.length(), 1, this);
    mModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Номер группы")));
    oModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Номер группы")));

    int myIndex = 0, otherIndex = 0;
    for(int i = 0; i<oGroups.length(); i++)
    {
        if (mGroups.contains(oGroups[i].mGroupID))
        {
            mModel->setItem(myIndex,0,new QStandardItem(QString(oGroups[i].mNumber)));
            myIndex++;
        }
        else
        {
            oModel->setItem(otherIndex,0,new QStandardItem(QString(oGroups[i].mNumber)));
            otherIndex++;
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
             mDiscipline.mForm !=  ui->Form->currentIndex() ||
             mDiscipline.mGroups != mGroups)
    {
        mDiscipline.mName = ui->lineName->text();
        mDiscipline.mForm = ui->Form->currentIndex();
        mDiscipline.mGroups = mGroups;
        QDialog::accept();
    }
    else QDialog::close();
}


void EditDisciplineDialog::on_MyGroups_activated(const QModelIndex &index)
{
   int myIndex = 0;
   for(int i = 0; i<oGroups.length(); i++)
   {
       if (mGroups.contains(oGroups[i].mGroupID))
       {
           if(myIndex == index.row())
           {
               mGroups.removeAt(myIndex);
               break;
           }
           myIndex++;
       }
   }
   setData();

}

void EditDisciplineDialog::on_OtherGroups_activated(const QModelIndex &index)
{
    int otherIndex = 0;
    for(int i = 0; i<oGroups.length(); i++)
    {
        if (!mGroups.contains(oGroups[i].mGroupID))
        {
            if(otherIndex == index.row())
            {
                mGroups.append(oGroups[i].mGroupID);
                break;
            }
            otherIndex++;
        }
    }
    setData();
}
