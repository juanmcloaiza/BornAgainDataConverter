#include "csvdialog.h"
#include "ui_csvdialog.h"
#include <QFileDialog>
#include <QMessageBox>

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

char CsvDialog::separator() const{
	char separator;
	QString tmpstr = ui->separatorField->text();
	if(tmpstr.size() < 1){
		separator = ' ';
		QMessageBox msgBox;
		msgBox.setText("There was a problem with the separator given.\n Replacing it by ' ' [space]");
		msgBox.setIcon(msgBox.Information);
		msgBox.exec();
		ui->separatorField->setText(QString(QChar::fromLatin1(separator)));
	}
	else{
		separator = tmpstr.at(0).toLatin1();
	}
	return separator;
}

uint CsvDialog::headersLine() const{
	return ui->headersRowSpinBox->value();
}

uint CsvDialog::firstLine() const{
	return ui->firstDataRowSpinBox->value();
}

uint CsvDialog::lastLine() const{
	return ui->lastDataRowSpinBox->value();
}

void CsvDialog::on_browseButton_clicked()
{
	QString filename = ui->filepathField->text();
	QString tmp;
	tmp = QFileDialog::getOpenFileName(this,
			tr("Open File"),
			".",
			"Text files (*.txt *.dat *.ascii *.int);;All files (*.*)"
			);
	if(tmp != NULL)
		ui->filepathField->setText(tmp);
}
