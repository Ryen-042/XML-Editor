#include "correct.h"
#include "ui_correct.h"
#include "Syntax_Highlight/xmlsyntaxhighlighter.h"
#include "check/check.h"
#include "Formating/Formating.h"

#include <vector>

correct::correct(QWidget *parent, QTextEdit* main_text) :
    QWidget(parent),
    ui(new Ui::correct),
    main_textEdit(main_text)
{
    ui->setupUi(this);
    new XmlSyntaxHighlighter(ui->textEdit->document());

}

bool correct::correct_or_not(QString input, bool &valid_xml){

    vector<string> v = check(input.toStdString());
    to_valid_xml = &valid_xml;
    if (v[0] == "true")
        return true;

    QString output;
    size_t i=2;
    output += "There are forgotten tags\n";
    output += "****************************\n";
    if(v[2] != "***"){
        while (i<v.size() && v[i] != "***") {
            output.append(QString::fromStdString(v[i]));
            output.append('\n');
            i++;
        }
    }
    i++;
    if(i<v.size()){
        output += "****************************\n";
        output += "There are wrong tags\n";
        output += "****************************\n";
        while (i<v.size()) {
            output.append(QString::fromStdString(v[i]));
            output.append('\n');
            i++;
        }
    }
    ui->textEdit->setText(output);
    correct_xml = QString::fromStdString(format(v[1], 100));

    return false;
}

void correct::on_fix_clicked()
{
    main_textEdit->setText(correct_xml);
    *to_valid_xml = true;
    close();
}


void correct::on_cancel_clicked()
{
    close();
}
correct::~correct()
{
    delete ui;
}


