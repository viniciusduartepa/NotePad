#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTextDocument>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
    curDoc=curText.document();
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
    curDoc->setModified(false);
    }
}

void MainWindow::on_actionOpen_triggered()
{
     if(maybesaved()){
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
        curDoc->setModified(false);
     }
}

void MainWindow::on_actionSave_triggered()
{
    if(currentfile==""){
        on_actionSave_as_triggered();
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
    curDoc->setModified(false);


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
    curDoc->setModified(false);
}

bool MainWindow::maybesaved(){
    if(!curDoc->isModified())return true;
    int ret = QMessageBox::warning(this, tr("My Application"),
                                   tr("Do you want to save your changes?"),
                                   QMessageBox::Yes | QMessageBox::No|QMessageBox::Cancel);

    switch(ret){
    case QMessageBox::Yes:
        on_actionSave_triggered();
            return true;
           case QMessageBox::No:
        return true;
    case QMessageBox::Cancel:
        return false;
    }
    return true;
}

void MainWindow::on_textEdit_textChanged()
{
  curText.setText(ui->textEdit->toPlainText());
  curDoc->setModified(true);

}
