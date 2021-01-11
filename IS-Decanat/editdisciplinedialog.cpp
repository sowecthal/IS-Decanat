#include "editdisciplinedialog.h"
#include "ui_editdisciplinedialog.h"

#include <QMessageBox>
#include <QStandardItemModel>
#include <QString>
#include <QDebug>

EditDisciplineDialog::EditDisciplineDialog(Discipline &sDiscipline, DataBases &sDB, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDisciplineDialog),
    mDiscipline(sDiscipline),
    mDB(sDB)
{
    ui->setupUi(this);
    //Заполнение списка групп.
    for (int &i : mDiscipline.mGroups) {
        mGroups.append(i);
    }
    //Ограничение длины имени.
    ui->lineName->setMaxLength(150);
    //Установка текущей наименования дисциплины.
    ui->lineName->setText(mDiscipline.mName);
    //Устновка текущей формы контроля.
    ui->Form->setCurrentIndex(getFormIndex());
    //Редактирование QLabel в соответствии с полученным номером дисциплины.
    ui->labelID->setText("Внутренний номер дисциплины: " + QString::number(mDiscipline.mDisciplineID));

    setData();
}

void EditDisciplineDialog::setData()
{
    model = new QStandardItemModel(mGroups.length(), 1, this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Номер группы")));

    for (int i = 0; i < mGroups.length(); i++) {
        model->setItem(i,0,new QStandardItem(QString(mDB.findGroup(mGroups[i])->mNumber)));
    }
    ui->MyGroups->setModel(model);
}

EditDisciplineDialog::~EditDisciplineDialog()
{
    delete ui;
}

int EditDisciplineDialog::getFormIndex()
{
    if (mDiscipline.mForm == Discipline::forms::PASS) {
        return(0);
    }
    return(1);
}

Discipline::forms EditDisciplineDialog::getFormByIndex(int index)
{
    if (index == 0) {
        return(Discipline::forms::PASS);
    }
    return(Discipline::forms::EXAM);
}

void EditDisciplineDialog::accept()
{
    //Если обнаруженно несовпадение значений - вызываем метод замены, закрываем с accept.
    if (ui->lineName->text().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Заполнены не все поля.");
    } else {
        mDiscipline.mName = ui->lineName->text();
        mDiscipline.mForm = getFormByIndex(ui->Form->currentIndex());
        mDiscipline.mGroups = mGroups;
        QDialog::accept();
    }

    QDialog::close();
}

void EditDisciplineDialog::on_MyGroups_activated(const QModelIndex &index)
{
    mGroups.removeAt(index.row());
    setData();
}

void EditDisciplineDialog::find()
{
    Group* foundGroup = mDB.findGroupName(ui->lineFind->text());
    if (foundGroup->mGroupID != 0 && !mGroups.contains(foundGroup->mGroupID)) {
        mGroups.append(foundGroup->mGroupID);
    }
    setData();
}
