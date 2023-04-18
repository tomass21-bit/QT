#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->PB_start->setText("Старт");
    ui->PB_loop->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_PB_start_toggled(bool checked)
{
    if(ui->PB_start->isChecked()==true)
    {ui->PB_start->setText("Стоп");
     ui->PB_loop->setEnabled(true);
    }
    else
    {
      ui->PB_start->setText("Старт");
    }

}

