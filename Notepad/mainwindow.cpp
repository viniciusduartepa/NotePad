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
    if(maybesaved()){
    ui->textEdit->clear();
    currentfile="";
    ui->textEdit->setFocus();
    }
}

void MainWindow::on_actionOpen_triggered()
{
    currentfile=QFileDialog::getOpenFileName(this,"Open File ","/c:/","Text File (*.txt)");
    QFile file(currentfile);
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
        file.close();
}

void MainWindow::on_actionSave_triggered()
{
    if(currentfile==""){
        QMessageBox::warning(this,"ERRO!","File not selected");
        return;
    }
    QFile file(currentfile);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        QMessageBox::warning(this,"ERRO","File not opened");
        return;
    }
    QString Text=ui->textEdit->toPlainText();
    file.flush();
    QTextStream out(&file);
    out << Text;
    file.close();

}

void MainWindow::on_actionSave_as_triggered()
{
    currentfile=QFileDialog::getOpenFileName(this,"Open File ","/c:/","Text File (*.txt)");
    QFile file(currentfile);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        QMessageBox::warning(this,"ERRO","File not opened");
        return;
    }
    QString Text=ui->textEdit->toPlainText();
    file.flush();
    QTextStream out(&file);
    out << Text;
    file.close();
}
bool MainWindow::maybesaved(){
    int ret = QMessageBox::warning(this, tr("My Application"),
                                   tr("Do you want to save your changes?"),
                                   QMessageBox::Yes | QMessageBox::No|QMessageBox::Cancel);

    switch(ret){
    case QMessageBox::Yes:
        on_actionSave_as_triggered();
           case QMessageBox::No:
        return true;
    case QMessageBox::Cancel:
        return false;
    }
    return true;
}
