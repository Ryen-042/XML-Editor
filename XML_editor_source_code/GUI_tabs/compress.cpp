#include "compress.h"
#include "ui_compress.h"
#include "Compress_Decompress/huffman_compress.h"
#include "Compress_Decompress/huffman_decompress.h"
#include "Syntax_Highlight/xmlsyntaxhighlighter.h"
#include "mainwindow.h"

#include <QFile>
#include <QDir>
#include <fstream>
#include <string>
#include <QMessageBox>
#include <QTextStream>

compress::compress(QWidget *parent,QString str) :
    QWidget(parent),
    original_file(str),
    ui(new Ui::compress)
{
    ui->setupUi(this);
    ui->compress_2->hide();
    new XmlSyntaxHighlighter(ui->textEdit_compress->document());
}


void compress::on_decompress_clicked()
{
    ui->decompress->hide();
    ui->compress_2->show();
    QString path = "compresed.huf";
    QString path2 = "decompresed.xml";
    huffman_decompress h1(path.toStdString(),path2.toStdString());
    h1.decompress_file();
    ui->textEdit_compress->setText(read_file(path2));

}



QString compress::read_file(QString path){
    QFile file(path);
    QTextStream in(&file);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(nullptr,"..","file not open");
        return "";
      }
    QString text = in.readAll();
    file.close();
    return text;
}

int compress::file_size(QString path){
    ifstream in_file(path.toStdString(), ios::binary);
    in_file.seekg(0, ios::end);
    return in_file.tellg();
}


void compress::on_compress_2_clicked()
{
    ui->compress_2->hide();
    ui->decompress->show();
    _compress();
}

void compress::_compress(){
    QString path = "compresed.huf";

    huffman_compress h1(original_file.toStdString(),path.toStdString());
    h1.compress_file();

   ui->textEdit_compress->setText(read_file(path));
   QString temp;

   temp = "Original File Size:  " + QString::number(file_size(original_file)) +" bytes\n";
   temp += "Compresed File Size:  " + QString::number(file_size(path)) +" bytes\n";
   QMessageBox::information(this,"Compress",temp);
}


void compress::on_save_compress_clicked()
{
    MainWindow::save_file(ui->textEdit_compress,"compress");
}

compress::~compress()
{
    delete ui;
}





