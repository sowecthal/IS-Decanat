#ifndef EDITDISCIPLINEDIALOG_H
#define EDITDISCIPLINEDIALOG_H

#include <QDialog>

namespace Ui {
class editDisciplineDialog;
}

class editDisciplineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editDisciplineDialog(QWidget *parent = nullptr);
    ~editDisciplineDialog();

private:
    Ui::editDisciplineDialog *ui;
};

#endif // EDITDISCIPLINEDIALOG_H
