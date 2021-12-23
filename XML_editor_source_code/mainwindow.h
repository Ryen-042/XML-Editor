#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTabWidget>
#include <QTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    static void save_file(QTextEdit *textEdit, QString type = "defult");

    ~MainWindow();

private slots:

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionQuit_triggered();

    void on_actionAbout_Us_triggered();

    void on_actionAbout_QT_triggered();

    void on_tabWidget_tabCloseRequested(int index);

private:

    void create_tab(QString type = "");

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
