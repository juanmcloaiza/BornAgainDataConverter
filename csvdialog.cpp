#include "csvdialog.h"
#include "ui_csvdialog.h"

CsvDialog::CsvDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CsvDialog)
{
    ui->setupUi(this);
}

CsvDialog::~CsvDialog()
{
    delete ui;
}

void CsvDialog::on_buttonBox_accepted()
{
    accept();
}

void CsvDialog::on_buttonBox_rejected()
{
    reject();
}

QString CsvDialog::filepath() const{
    return ui->filepathField->text();
}

QChar CsvDialog::separator() const{
    return ui->separatorField->text().at(0);
}
