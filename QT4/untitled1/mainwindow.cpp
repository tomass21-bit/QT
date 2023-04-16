#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_PB_bar_toggled(bool checked)
{
    if(ui->progressBar->value()==10){
       ui->progressBar->setValue(0);
    }
    else{
     unsigned m=ui->progressBar->maximum();
     m*=0.1;
     unsigned v=ui->progressBar->value();
     v+=m;
    ui->progressBar->setValue(v);
    }
}

