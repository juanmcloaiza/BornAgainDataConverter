#ifndef CSVDIALOG_H
#define CSVDIALOG_H

#include <QDialog>

namespace Ui {
class CsvDialog;
}

class CsvDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CsvDialog(QWidget *parent = 0);
    ~CsvDialog();

    QString filepath() const;
    char separator() const;
    uint headersLine() const;
    uint firstLine() const;
    uint lastLine() const;


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_browseButton_clicked();

private:
    Ui::CsvDialog *ui;
};

#endif // CSVDIALOG_H
