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
    QChar separator() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CsvDialog *ui;
};

#endif // CSVDIALOG_H
