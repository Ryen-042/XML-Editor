#include "convert_to_json.h"
#include "ui_convert_to_json.h"
#include "mainwindow.h"
#include "XML_to_JSON/tree.hpp"
#include "./Minify/Minify.h"
#include "Syntax_Highlight/jshighlighter.h"

Convert_to_JSON::Convert_to_JSON(QWidget *parent, QString str) :
    QWidget(parent),
    ui(new Ui::Convert_to_JSON)
{
    ui->setupUi(this);
    new JSHighlighter(ui->textEdit->document());

    Tree* XML_Tree = new Tree();

    str = QString::fromStdString(Minify(str.toStdString()));
    // make tree from string s
    XML_Tree->parse_and_bulid_xml_tree(str.toStdString());

    ui->textEdit->setText(QString::fromStdString(XML_Tree->convert_to_json()));
}

void Convert_to_JSON::on_save_clicked()
{
    MainWindow::save_file(ui->textEdit,"JSON");
}

Convert_to_JSON::~Convert_to_JSON()
{
    delete ui;
}


