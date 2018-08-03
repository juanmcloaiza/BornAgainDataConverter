#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void generate_table(QString filepath, char separator, int headersLine, int firstLine, int lastLine);
    void convert_table();
    void remove_blanks();
    bool cell_is_blank(int iRow, int jCol);
};

#endif // MAINWINDOW_H
