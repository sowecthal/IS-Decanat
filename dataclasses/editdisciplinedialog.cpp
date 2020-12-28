#include "editdisciplinedialog.h"
#include "ui_editdisciplinedialog.h"

editDisciplineDialog::editDisciplineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editDisciplineDialog)
{
    ui->setupUi(this);
}

editDisciplineDialog::~editDisciplineDialog()
{
    delete ui;
}
