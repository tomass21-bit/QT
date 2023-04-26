#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->PB_start->setText("Старт");
    ui->PB_loop->setEnabled(false);
    sigCall = new Stopwatch(this);

    connect(sigCall, &Stopwatch::sig_SendStop, this, &MainWindow::RcvSignalStop);
    connect(sigCall, &Stopwatch::sig_SendStart, this, &MainWindow::RcvSignalStart);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::RcvSignalStart(QString time)
{

   ui->lb_time->setText(time);
}
void MainWindow::RcvSignalStop()
{
   sigCall->Stop();
   ui->PB_start->setText("Старт");
}


void MainWindow::on_PB_start_toggled(bool checked)
{

    if(ui->PB_start->isChecked()==true)  
    {    
     sigCall->UpdateTime();
     ui->PB_start->setText("Стоп");
     ui->PB_loop->setEnabled(true);
    }
    else
    {
      sigCall->SendStopSignal();
      ui->PB_loop->setEnabled(false);
    }

}


void MainWindow::on_PB_clear_clicked()
{
    sigCall->Clear();
    ui->lb_time->setText("00:00:0");
    ui->textBrowser->clearHistory();


}


void MainWindow::on_PB_loop_clicked()
{
   sigCall->Loop();
   ui->textBrowser->append(sigCall->ShowLoop());
}

