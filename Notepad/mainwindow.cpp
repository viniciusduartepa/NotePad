#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    ui->textEdit->clear();
    currentfile="";
    ui->textEdit->setFocus();
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename;
    filename=QFileDialog::getOpenFileName(this,"Open File ","/c:/","Text File (*.txt)");
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QMessageBox::warning(this,"ERRO","File not opened");
        return;
    }
    ui->textEdit->clear();
    QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            ui->textEdit->append(line);
        }




}
