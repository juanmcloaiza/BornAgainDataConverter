#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);


	setWindowTitle("Acquired Data");
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_openButton_clicked()
{
	CsvDialog csvd(this);
	csvd.setWindowTitle("Input File Details");
	int res = csvd.exec();
	if(res == QDialog::Rejected)
		return;

    MainWindow::generate_table(&csvd);
}

void MainWindow::on_exportButton_clicked()
{
	MainWindow::convert_table();
}

void MainWindow::generate_table(CsvDialog* csvd)
{
    CSVFile csvFile(csvd->filepath().toStdString(), csvd->separator(), csvd->headersLine());

    ui->tableWidget->clearContents();
    ui->tableWidget->setColumnCount(csvFile.NumberOfColumns());
    ui->tableWidget->setRowCount(0);

    set_table_headers(&csvFile);
    set_table_data(&csvFile,csvd);
    remove_blanks();

    return;
}

void MainWindow::set_table_headers(CSVFile* csvFile){
    QStringList titulos;

    CSVRow headers = csvFile->get_headers();

    for(uint j = 0; j < headers.size(); j++){
        std::string header = headers[j].empty() ? std::string("Column ") + std::to_string(j+1) : headers[j];
        titulos << QString::fromStdString(header);
    }
    ui->tableWidget->setHorizontalHeaderLabels(titulos);
    return;
}


void MainWindow::set_table_data(CSVFile* csvFile, CsvDialog* csvd){

    uint firstDataLine = csvd->firstLine() - 1;
    uint lastDataLine = csvd->lastLine() == 0 ? csvFile->NumberOfRows() : csvd->lastLine();

    for(uint i = firstDataLine; i < lastDataLine; i++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        uint I = ui->tableWidget->rowCount() - 1;
        for(uint j = 0; j < csvFile->NumberOfColumns(); j++){
           std::string aasdf = csvFile->operator [](i)[j];
           ui->tableWidget->setItem(I,j,new QTableWidgetItem(QString::fromStdString(aasdf)));
        }
    }
}

void MainWindow::remove_blanks(){
	int nRows = ui->tableWidget->rowCount();
	int nCols = ui->tableWidget->columnCount();
    vector<vector<string>> A;
    vector<string> B;
	vector<int> blank_cols;

    //save the inices of blank cols
	for(int j = 0; j < nCols; j++){
		int i = 0;
		bool this_col_is_blank = cell_is_blank(i,j);
        while(this_col_is_blank && i < nRows  ){
			this_col_is_blank = cell_is_blank(i,j);
			i++;
		}
		if(i == nRows){
			blank_cols.push_back(j);
		}
	}

    //save the values of the array
    for(int i = 0; i < nRows; i++){
        B.clear();
        for(int j = 0; j < nCols; j++){
           B.push_back( ui->tableWidget->item(i,j) != NULL ? ui->tableWidget->item(i,j)->text().toStdString() : "");
        }
        A.push_back(B);
    }

    //put them into a new table
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(nCols-blank_cols.size());
    for(int i = 0; i < nRows; i++){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        int J = 0;
        for(int j = 0; j < nCols; j++){
               if( std::find(blank_cols.begin(), blank_cols.end(), j) == blank_cols.end()){
                    std::string a = A[i][j];
                    ui->tableWidget->setItem(i,J,new QTableWidgetItem(QString::fromStdString(a)));
                    J++;
               }
         }

    }



    cout << "finished removing blanks" << endl;

}

void MainWindow::convert_table(){
    int nRows = ui->tableWidget->rowCount();
    int nCols = ui->tableWidget->columnCount();
    for(int i = 0; i < nRows; i++){
        for(int j = 0; j < nCols; j++){
            QString newval = QString::fromStdString(std::to_string(2 * ui->tableWidget->item(i,j)->text().toInt()));
            ui->tableWidget->setItem(i,j,new QTableWidgetItem(newval));
        }
    }
}


bool MainWindow::cell_is_blank(int iRow, int jCol){

    if ( ui->tableWidget->item(iRow,jCol) == NULL)
        return true;

    if ( ui->tableWidget->item(iRow,jCol)->text() == NULL)
        return true;

    if( ui->tableWidget->item(iRow,jCol)->text().trimmed() == "")
        return true;

    return false;
}
