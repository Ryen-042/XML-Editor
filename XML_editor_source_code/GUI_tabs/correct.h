#ifndef CORRECT_H
#define CORRECT_H

#include <QWidget>
#include <QTextEdit>

namespace Ui {
class correct;
}

class correct : public QWidget
{
    Q_OBJECT

public:
    explicit correct(QWidget *parent = nullptr, QTextEdit *main_text = nullptr);
    bool correct_or_not(QString input, bool &valid_xml);
    ~correct();

private slots:
    void on_fix_clicked();

    void on_cancel_clicked();

private:
    Ui::correct *ui;
    QString correct_xml;
    bool* to_valid_xml;
    QTextEdit* main_textEdit;
};

#endif // CORRECT_H
