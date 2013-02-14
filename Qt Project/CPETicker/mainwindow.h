#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "qextserialport.h"
#include "qextserialenumerator.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void onDataAvailable();

    void on_save_button_clicked();

private:
    Ui::MainWindow *ui;
    QextSerialPort *port;
};

#endif // MAINWINDOW_H