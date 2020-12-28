#include "editdisciplinedialog.h"
#include "ui_editdisciplinedialog.h"


EditDisciplineDialog::EditDisciplineDialog(Discipline &sDiscipline, QWidget *parent) : mDiscipline(sDiscipline),
    QDialog(parent),
    ui(new Ui::EditDisciplineDialog)
{
    ui->setupUi(this);
    ui->lineName->setMaxLength(50);
    ui->lineName->setMaxLength(20);
    ui->lineName->setText(mDiscipline.mName);

    ui->Form->setCurrentIndex(mDiscipline.mForm);
}


EditDisciplineDialog::~EditDisciplineDialog()
{
    delete ui;
}
