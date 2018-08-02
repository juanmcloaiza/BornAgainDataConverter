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
    void on_pushButton_clicked();

    void on_pushButton2_clicked();

private:
    Ui::MainWindow *ui;
    enum Column
    {
     FILEPATH,
     SEPARATOR
    };
    void generate_table(QString filepath, char separator);
    void convert_table();
};

#endif // MAINWINDOW_H
