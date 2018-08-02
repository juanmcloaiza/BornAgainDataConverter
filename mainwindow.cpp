#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvreader.h"
#include "csvdialog.h"
#include <iostream>
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

void MainWindow::on_pushButton_clicked()
{
	QString csvFile;
	QString csvSeparator;
	CsvDialog csvd(this);
	csvd.setWindowTitle("Input File Details");
	int res = csvd.exec();
	if(res == QDialog::Rejected)
		return;
	csvFile = csvd.filepath();
	csvSeparator = csvd.separator();
	MainWindow::generate_table(csvd.filepath(), csvd.separator(), csvd.firstLine(), csvd.lastLine());
}

void MainWindow::on_pushButton2_clicked()
{
	MainWindow::convert_table();
}

void MainWindow::on_removeBlankColsButton_clicked()
{
	MainWindow::remove_blanks();
}



void MainWindow::generate_table(QString filepath, char separator, int firstLine, int lastLine)
{
	std::ifstream file(filepath.toStdString());
	QStringList titulos;
	int currentLine = 0;
	for(CSVIterator loop(file, separator); loop != CSVIterator(); ++loop){
		currentLine++;
		if(currentLine <= firstLine)
			continue;

		ui->tableWidget->setColumnCount(loop->size());
		for(uint j = 0; j < loop->size(); j++){
			//titulos << QString::fromStdString((*loop)[j]);
			titulos << QString::fromStdString(std::string("Column ") + std::to_string(j) );
		}

		break;
	}
	ui->tableWidget->clearContents();
	ui->tableWidget->setRowCount(0);
	ui->tableWidget->setHorizontalHeaderLabels(titulos);
	int fila = 0;

	try{
		cout << "Hello" << endl;
		std::ifstream file(filepath.toStdString());

		int i =0;
		currentLine = 0;
		for(CSVIterator loop(file, separator); loop != CSVIterator(); ++loop)
		{
			currentLine++;
			if(currentLine < firstLine)
				continue;
			if (lastLine > 0)
                if(currentLine > lastLine)
					break;


			ui->tableWidget->insertRow(ui->tableWidget->rowCount());
			fila = ui->tableWidget->rowCount()-1;
			for(uint j = 0; j < loop->size(); j++){
				ui->tableWidget->setItem(fila,j,new QTableWidgetItem(QString::fromStdString((*loop)[j])));
			}
			i++;
		}

	}catch(const std::exception& e){
		cout << e.what() << endl;
	}
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
            cout<<B.back();
        }
        A.push_back(B);
        cout<<A[i].back();
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


//    for(uint j = 0; j < blank_cols.size() ;j++)
//        std::cout << blank_cols[j] << endl;

    cout << "finished" << endl;

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
