#ifndef EDITDISCIPLINEDIALOG_H
#define EDITDISCIPLINEDIALOG_H

#include "dataclasses/discipline.h"
#include <QDialog>

namespace Ui {
class EditDisciplineDialog;
}

class EditDisciplineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDisciplineDialog(Discipline &sDiscipline, QWidget *parent = nullptr);
    ~EditDisciplineDialog();

private:
    Ui::EditDisciplineDialog *ui;
    Discipline& mDiscipline;
};

#endif // EDITDISCIPLINEDIALOG_H
