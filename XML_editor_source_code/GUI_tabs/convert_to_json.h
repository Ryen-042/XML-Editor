#ifndef CONVERT_TO_JSON_H
#define CONVERT_TO_JSON_H

#include <QWidget>

namespace Ui {
class Convert_to_JSON;
}

class Convert_to_JSON : public QWidget
{
    Q_OBJECT

public:
    explicit Convert_to_JSON(QWidget *parent = nullptr, QString str="");
    ~Convert_to_JSON();

private slots:
    void on_save_clicked();

private:
    Ui::Convert_to_JSON *ui;
};

#endif // CONVERT_TO_JSON_H
