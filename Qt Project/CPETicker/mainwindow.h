#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "qextserialport.h"


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
    void on_sendButton_clicked();
    void onDataAvailable();

private:
    Ui::MainWindow *ui;
    QextSerialPort *port;
};

#endif // MAINWINDOW_H
