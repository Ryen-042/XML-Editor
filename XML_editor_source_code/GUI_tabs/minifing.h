#ifndef MINIFING_H
#define MINIFING_H

#include <QWidget>

namespace Ui {
class Minifing;
}

class Minifing : public QWidget
{
    Q_OBJECT

public:
    explicit Minifing(QWidget *parent = nullptr, QString Str = "");
    ~Minifing();

private slots:
    void on_save_clicked();

private:
    Ui::Minifing *ui;
};

#endif // MINIFING_H
