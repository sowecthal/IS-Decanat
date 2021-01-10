#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dataclasses/user.h"
#include "dataclasses/discipline.h"
#include "dataclasses/group.h"

#include <QMainWindow>
#include <databases.h>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DataBases &sDB, QWidget *parent = nullptr);
    ~MainWindow();
    void setUser(User *sUser);

private slots:

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_tableView_activated(const QModelIndex &index);

    void addNoteThis();

    void removeNoteThis();


private:
    DataBases &db;
    QList <User*> students;
    int mMode;
    User *mUser;
    QStandardItemModel* model;
    Ui::MainWindow *ui;

    void setData();

    int findGrade(int fDisciplinesID);
};
#endif // MAINWINDOW_H
