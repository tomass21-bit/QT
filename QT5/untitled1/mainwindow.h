#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stopwatch.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void RcvSignalStop(void);
    void RcvSignalStart(QString);
private slots:
    void on_PB_start_toggled(bool checked);
    void on_PB_clear_clicked();
    void on_PB_loop_clicked();

private:
    Ui::MainWindow *ui;
    Stopwatch *sigCall;

};
#endif // MAINWINDOW_H
