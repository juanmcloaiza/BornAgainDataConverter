#include "personadialog.h"
#include "ui_personadialog.h"

PersonaDialog::PersonaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonaDialog)
{
    ui->setupUi(this);
}

PersonaDialog::~PersonaDialog()
{
    delete ui;
}

void PersonaDialog::on_buttonBox_accepted()
{
    accept();
}

void PersonaDialog::on_buttonBox_rejected()
{
    reject();
}

QString PersonaDialog::nombre() const{
    return ui->nombre->text();
}

int PersonaDialog::edad() const{
    return ui->edad->value();
}

double PersonaDialog::salario() const{
    return ui->salario->value();
}
