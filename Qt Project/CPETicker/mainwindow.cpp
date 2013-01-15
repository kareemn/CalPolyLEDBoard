#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    port = new QextSerialPort("COM15");
    port->setBaudRate(BAUD57600);
    qDebug() << port->baudRate();
    connect(port, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));
    port->open(QextSerialPort::ReadWrite);
    port->write("\r");

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDataAvailable()
{
    QByteArray data = port->readAll();
    qDebug() << "NEW DATA" << data;
    //processNewData(data);
}

void MainWindow::on_sendButton_clicked()
{
    QString msg = ui->msgBox->toPlainText();
    msg.replace("\r", "");
    qDebug() << msg;
    port->write("\r");
    port->write(msg.toAscii());
}
