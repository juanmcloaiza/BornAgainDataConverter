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
    char csvSeparator;
    CsvDialog csvd(this);
    csvd.setWindowTitle("Input File Details");
    int res = csvd.exec();
    if(res == QDialog::Rejected)
        return;
    csvFile = csvd.filepath();
    csvSeparator = csvd.separator();
    MainWindow::generate_table(csvFile, csvSeparator);
}

void MainWindow::on_pushButton2_clicked()
{
    MainWindow::convert_table();
}




void MainWindow::generate_table(QString filepath, char separator)
{
    std::ifstream       file(filepath.toStdString());
    QStringList titulos;
    for(CSVIterator loop(file, separator); loop != CSVIterator(); ++loop){
        ui->tableWidget->setColumnCount(loop->size());

        for(uint j = 0; j < loop->size(); j++){
            titulos << QString::fromStdString((*loop)[j]);
        }
        break;
    }
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setHorizontalHeaderLabels(titulos);
    int fila = 0;

    try{

        cout << "Hello" << endl;
        std::ifstream       file(filepath.toStdString());

        int i =0;

        for(CSVIterator loop(file, separator); loop != CSVIterator(); ++loop)
        {
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            fila = ui->tableWidget->rowCount()-1;
            for(uint j = 0; j < loop->size(); j++){
            //std::cout << "4th Element(" << (*loop)[3] << ")\n";


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



