#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "csvdialog.h"
#include "csvreader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openButton_clicked();

    void on_exportButton_clicked();

private:
    Ui::MainWindow *ui;
    enum Column
    {
     FILEPATH,
     SEPARATOR
    };

    void generate_table(CsvDialog *csvd);


    void set_table_headers(CSVFile *csvFile);
    void set_table_data(CSVFile *csvFile, CsvDialog *csvd);
    void convert_table();
    void remove_blanks();
    bool cell_is_blank(int iRow, int jCol);
};

#endif // MAINWINDOW_H
