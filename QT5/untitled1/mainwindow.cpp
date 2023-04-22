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
    QObject::connect(sigCall, &Stopwatch::sig_SendStart, this, &MainWindow::RcvSignalStart, Qt::ConnectionType());
    QObject::connect(sigCall, &Stopwatch::sig_SendStop, this, &MainWindow::RcvSignalStop, Qt::ConnectionType());

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::RcvSignalStart()
{

   ui->lb_time->setText(sigCall->showtime());
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

     sigCall->Start();
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
    ui->lb_time->setText(sigCall->showtime());
    ui->textBrowser->clearHistory();


}


void MainWindow::on_PB_loop_clicked()
{
   sigCall->Loop();
   ui->textBrowser->append(sigCall->showloop());
}

