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

    void on_tableWidget_cellActivated(int row, int column);

private:
    Ui::MainWindow *ui;
    enum Columna
    {
     NOMBRE,
     EDAD,
     SALARIO
    };
};

#endif // MAINWINDOW_H
