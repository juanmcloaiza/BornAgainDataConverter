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
    QChar csvSeparator;
    CsvDialog csvd(this);
    csvd.setWindowTitle("Input File Details");
    int res = csvd.exec();
    if(res == QDialog::Rejected)
        return;
    csvFile = csvd.filepath();
    csvSeparator = csvd.separator();
    MainWindow::generate_table(csvFile, csvSeparator);
}
//void MainWindow::on_pushButton_clicked()
//{
//    double salario;
//    int res, edad, fila;
//    QString nombre;
//    CsvDialog pd(this);
//    pd.setWindowTitle("Captura de Empleado");
//    res = pd.exec();
//    if(res == QDialog::Rejected)
//        return;
//    nombre = pd.nombre();
//    edad = pd.edad();
//    salario = pd.salario();
//    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
//    fila = ui->tableWidget->rowCount()-1;
//    ui->tableWidget->setItem(fila,NOMBRE,new QTableWidgetItem(nombre));
//    ui->tableWidget->setItem(fila,EDAD,new QTableWidgetItem(QString::number(edad)));
//    ui->tableWidget->setItem(fila,SALARIO,new QTableWidgetItem(QString::number(salario)));


//}


void MainWindow::generate_table(QString filepath, QChar separator)
{
    std::ifstream       file(filepath.toStdString());
    QStringList titulos;
    for(CSVIterator loop(file); loop != CSVIterator(); ++loop){
        ui->tableWidget->setColumnCount(loop->size());

        for(int j = 0; j < loop->size(); j++){
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

        for(CSVIterator loop(file); loop != CSVIterator(); ++loop)
        {
            int j = 0;
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            fila = ui->tableWidget->rowCount()-1;
            for(int j = 0; j < loop->size(); j++){
            //std::cout << "4th Element(" << (*loop)[3] << ")\n";


            ui->tableWidget->setItem(fila,j,new QTableWidgetItem(QString::fromStdString((*loop)[j])));
            }
            i++;
        }

    }catch(const std::exception& e){
        cout << e.what() << endl;
    }
}
