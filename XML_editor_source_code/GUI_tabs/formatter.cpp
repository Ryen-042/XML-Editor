#include <string>
#include "formatter.h"
#include "ui_formatter.h"
#include "mainwindow.h"
#include "minifing.h"
#include "Syntax_Highlight/xmlsyntaxhighlighter.h"
#include "./Formating/Formating.h"


Formatter::Formatter(QWidget *parent ,QString str) :
    QWidget(parent),
    ui(new Ui::Formatter)
{
    ui->setupUi(this);
    new XmlSyntaxHighlighter(ui->textEdit->document());
    ui->textEdit->setText(QString::fromStdString(format(str.toStdString(),100)));
}

void Formatter::on_save_clicked()
{
    MainWindow::save_file(ui->textEdit);
}

Formatter::~Formatter()
{
    delete ui;
}


