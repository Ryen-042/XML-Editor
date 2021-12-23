#include "inputfile.h"
#include "ui_inputfile.h"
#include "Syntax_Highlight/xmlsyntaxhighlighter.h"
#include "convert_to_json.h"
#include "formatter.h"
#include "minifing.h"
#include "compress.h"
#include "correct.h"

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
inputFile::inputFile(QTabWidget *parent) :
    QWidget(nullptr),
    ui(new Ui::inputFile),
    tabWidget(parent)
{
    ui->setupUi(this);
    new XmlSyntaxHighlighter(ui->input_TextEdit->document());
}

void inputFile::open(){
    on_openFile_clicked();
}

void inputFile::on_openFile_clicked()
{
    QString filter = "XML (*.xml);;Text (*txt);;All files (*.*)";
    QString file_name = QFileDialog::getOpenFileName(this,"Open the file","C:\\",filter);
    QFile file(file_name);
    file_path_ = file_name;
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,"..","file not open");
        return;
      }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->input_TextEdit->setText(text);
    file.close();

    on_correct_clicked();
}

void inputFile::create_new_tab(QString type){
    if(ui->input_TextEdit->toPlainText()==""){
               QMessageBox::critical(this,"error","please open a XML file first 😡");
                    return;
        }
    if(!valid_xml){
               QMessageBox::critical(this,"error","please correct XML file first 😤");
                    return;
        }

    QWidget * new_tab = nullptr;
    if(type == "Minifing")
    {
        new_tab = new Minifing(nullptr , ui->input_TextEdit->toPlainText());
    }
    else if (type == "Formatter")
    {
        new_tab = new Formatter(nullptr , ui->input_TextEdit->toPlainText());
    }
    else if (type == "JSON")
    {
        new_tab = new Convert_to_JSON(nullptr , ui->input_TextEdit->toPlainText());
    }

   tabWidget->addTab(new_tab,type);
   tabWidget ->setCurrentIndex(tabWidget->count()-1);
}


void inputFile::on_correct_clicked()
{
    if(ui->input_TextEdit->toPlainText()==""){
               QMessageBox::critical(this,"error","please open a XML file first 😡");
                    return;
        }

    correct* new_correct = new correct(nullptr,ui->input_TextEdit);
    valid_xml = new_correct->correct_or_not( ui->input_TextEdit->toPlainText() ,valid_xml);
    if(!valid_xml)
        new_correct->show();
    else{
        QMessageBox::information(this,"XML File","Correct XML File 😀");
        delete new_correct;
    }
}

void inputFile::on_minifing_clicked()
{
    create_new_tab("Minifing");
}

void inputFile::on_formatter_clicked()
{
    create_new_tab("Formatter");
}


void inputFile::on_convertToJSON_clicked()
{
    create_new_tab("JSON");
}


void inputFile::on_compress_clicked()
{
    compress* new_tab = new compress(nullptr,file_path_);
    tabWidget->addTab(new_tab,"Compress");
    tabWidget ->setCurrentIndex(tabWidget->count()-1);
    new_tab->_compress();
}


inputFile::~inputFile()
{
    delete ui;
}


