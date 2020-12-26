#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void setMode(int sMode);

private slots:
    void on_lineEdit_returnPressed();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_tableView_activated(const QModelIndex &index);

private:
    DataBases& db;
    int mMode;
    Ui::MainWindow *ui;
    void setData();
};
#endif // MAINWINDOW_H
