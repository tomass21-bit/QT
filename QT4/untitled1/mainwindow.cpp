#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->RB_left->setText("Left_B");
    ui->RB_right->setText("Right_B");
    ui->comboBox->addItem("июнь");
    ui->comboBox->addItem("июль");
    ui->PB_bar->setText("Progres");
    ui->PB_bar->setCheckable(true);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(10);
    ui->progressBar->setValue(0);
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

