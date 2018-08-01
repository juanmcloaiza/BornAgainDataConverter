#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvreader.h"
#include "personadialog.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList titulos;

    setWindowTitle("Empleados");
    ui->tableWidget->setColumnCount(3);
    titulos << "Nommbre" << "Edad" << "Salario";
    ui->tableWidget->setHorizontalHeaderLabels(titulos);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::on_pushButton_clicked()
//{
//    double salario;
//    int res, edad, fila;
//    QString nombre;
//    PersonaDialog pd(this);
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


void MainWindow::on_pushButton_clicked()
{

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    int fila = 0;

    try{
    io::CSVReader<3> in("ram.csv");

    in.read_header(io::ignore_extra_column, "vendor", "size", "speed");
    string vendor;
    int size;
    double speed;
    cout << "Hello" << endl;
    while(in.read_row(vendor, size, speed)){
        cout << vendor <<", "<< size <<", "<< speed <<", "<< endl;
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        fila = ui->tableWidget->rowCount()-1;
        ui->tableWidget->setItem(fila,NOMBRE,new QTableWidgetItem(QString::fromStdString(vendor)));
        ui->tableWidget->setItem(fila,EDAD,new QTableWidgetItem(QString::number(size)));
        ui->tableWidget->setItem(fila,SALARIO,new QTableWidgetItem(QString::number(speed)));
    }

    }
    catch(const std::exception& e){
        cout << e.what() << endl;
    }
}
