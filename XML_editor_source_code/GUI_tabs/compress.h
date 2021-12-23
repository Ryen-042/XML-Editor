#ifndef COMPRESS_H
#define COMPRESS_H

#include <QWidget>

namespace Ui {
class compress;
}

class compress : public QWidget
{
    Q_OBJECT

public:
    explicit compress(QWidget *parent = nullptr, QString str = "");
    void _compress();
    ~compress();

private slots:
    void on_decompress_clicked();

    void on_save_compress_clicked();


    void on_compress_2_clicked();

private:
    QString read_file(QString path);
    int file_size(QString path);
    QString original_file;
    Ui::compress *ui;
};

#endif // COMPRESS_H
