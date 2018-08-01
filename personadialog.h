#ifndef PERSONADIALOG_H
#define PERSONADIALOG_H

#include <QDialog>

namespace Ui {
class PersonaDialog;
}

class PersonaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PersonaDialog(QWidget *parent = 0);
    ~PersonaDialog();

    QString nombre() const;
    int edad() const;
    double salario() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::PersonaDialog *ui;
};

#endif // PERSONADIALOG_H
