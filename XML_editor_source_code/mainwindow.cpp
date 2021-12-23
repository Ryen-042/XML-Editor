#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GUI_tabs/inputfile.h"

#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);
    ui->tabWidget->clear();
    ui->tabWidget->addTab(new inputFile(ui->tabWidget),"Input File");
}


void MainWindow::save_file(QTextEdit *textEdit, QString type) {
    QString filter;
    if(type == "JSON")
    {
        filter = "JSON (*.json);;Text (*.txt);;All files (*.*)";
    }
    else if (type == "compress")
    {
        filter = "HUF (*.huf);;XML (*.xml);;Text (*.txt);;All files (*.*)";
    }
    else
    {
        filter = "XML (*.xml);;Text (*.txt);;All files (*.*)";
    }

    QString file_name = QFileDialog::getSaveFileName(NULL, "Save File","C:\\",filter);
    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    QString text = textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();

}

void MainWindow::create_tab(QString type)
{
    inputFile * temp = new inputFile(ui->tabWidget);

    if(type == "open"){
        temp->open();
    }

    ui->tabWidget->addTab(temp,"Input File" + QString::number(ui->tabWidget->count()));
    ui->tabWidget ->setCurrentIndex(ui->tabWidget->count()-1);
}

void MainWindow::on_actionNew_triggered()
{
    create_tab();
}


void MainWindow::on_actionOpen_triggered()
{
    create_tab("open");
}


void MainWindow::on_actionQuit_triggered()
{
    close();
}


void MainWindow::on_actionAbout_Us_triggered()
{
    QString about_text;

    about_text  = "Auther : Data Structure Team\n";
    about_text += "Features : 1) Correct XML\n"
                         "\t  2) Minifing\n"
                         "\t  3) Formatter\n"
                         "\t  4) Convert to JSON\n"
                         "\t  3) Compress\n";


    about_text += "Date   : 12/12/2021\n";
    about_text += "(C) XML_Editor  (R)\n";

    QMessageBox::about(this,"About Notepad",about_text);
}

void MainWindow::on_actionAbout_QT_triggered(){
    QMessageBox::aboutQt(this,"About QT");
}


void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if(index != 0)
        ui->tabWidget->removeTab(index);
}

MainWindow::~MainWindow()
{
    delete ui;
}



