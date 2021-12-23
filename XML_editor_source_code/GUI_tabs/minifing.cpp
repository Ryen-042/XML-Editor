#include "minifing.h"
#include "ui_minifing.h"
#include "Syntax_Highlight/xmlsyntaxhighlighter.h"
#include "mainwindow.h"
#include "./Minify/Minify.h"

Minifing::Minifing(QWidget *parent,QString Str) :
    QWidget(parent),
    ui(new Ui::Minifing)
{
    ui->setupUi(this);
    new XmlSyntaxHighlighter(ui->textEdit->document());

    ui->textEdit->setText(QString::fromStdString(Minify(Str.toStdString())));
}

void Minifing::on_save_clicked()
{
    MainWindow::save_file(ui->textEdit);
}

Minifing::~Minifing()
{
    delete ui;
}


