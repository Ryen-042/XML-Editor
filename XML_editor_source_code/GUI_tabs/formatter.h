#ifndef FORMATTER_H
#define FORMATTER_H

#include <QWidget>
#include <string>

namespace Ui {
class Formatter;
}

class Formatter : public QWidget
{
    Q_OBJECT

public:
    explicit Formatter(QWidget *parent = nullptr, QString str = "");
    ~Formatter();

private slots:
    void on_save_clicked();

private:
    Ui::Formatter *ui;
};

#endif // FORMATTER_H
