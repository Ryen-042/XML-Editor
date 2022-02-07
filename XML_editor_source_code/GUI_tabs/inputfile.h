#ifndef INPUTFILE_H
#define INPUTFILE_H

#include <QWidget>
#include <QTabWidget>
#include <string>

namespace Ui {
class inputFile;
}

class inputFile : public QWidget
{
    Q_OBJECT

public:
    explicit inputFile(QTabWidget *parent = nullptr);
    void open();
    ~inputFile();

private slots:
    void on_openFile_clicked();

    void on_correct_clicked();

    void on_minifing_clicked();

    void on_formatter_clicked();

    void on_convertToJSON_clicked();

    void on_compress_clicked();

    void create_new_tab(QString type);

    void on_visualize_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::inputFile *ui;
    QTabWidget *tabWidget;
    QString file_path_;
    bool valid_xml = false;
};

#endif // INPUTFILE_H
