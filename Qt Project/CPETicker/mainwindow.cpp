#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
//    // find all available com ports
//    QStringList comPorts;
//    foreach (QextPortInfo info, QextSerialEnumerator::getPorts())
//    {
//        if (info.portName != "")
//        {
//            comPorts.append(info.portName);
//        }
//    }
//    qDebug() << comPorts;

    port = new QextSerialPort("COM26");
    port->setBaudRate(BAUD2400);
    qDebug() << port->baudRate();
    connect(port, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));
    port->open(QextSerialPort::ReadWrite);
    QByteArray str = QByteArray();
    str.append((char)0xc);
    //str.append("Computer Engineerg Event Ticker | Capstone 2013\n\003By: Gomberg, Carteno, Tossoun, Burke, Zuffi\n\002Funding provided by \002G\004o\005o\002g\001l\004e");
    str.append("\004CPE Student Town Hall | Thurs 2/28 11am-12pm | 38-204\n\002All CPE students are invited. Dr. Smith will provide\nan update on the CPE program.");
    str.append((char)0x17);
    qDebug() << port->write(str, str.length()) << str;

    if (true)
        return;

    ui->setupUi(this);

    QTableWidgetItem *item = new QTableWidgetItem("<New Item>");
    item->setTextAlignment(Qt::AlignCenter);
    QFont font = item->font();
    font.setBold(true);
    item->setFont(font);
    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0, 0, item);

    QStringList events = QStringList();
    events.append("Capstone Meeting  |  Wed 1/16 4PM  |  20-100");
    events.append("Another Awesome Event  |  Mon 1/21 2:30PM  |  14-210");

    for (int i=0; i < events.length(); i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(events[i]);
        ui->tableWidget->insertRow(i+1);
        ui->tableWidget->setItem(i+1, 0, item);
    }
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

/*void MainWindow::on_sendButton_clicked()
{
    QString msg = ui->msgBox->toPlainText();
    msg.replace("\r", "");
    qDebug() << msg;
    port->write("\r");
    port->write(msg.toAscii());
}*/

void MainWindow::on_save_button_clicked()
{
    QString title = ui->title_editbox->text();
    QString time = ui->date_widget->selectedDate().toString("ddd M/d") + " " + ui->time_editbox->time().toString("h:mm AP");
    QString location = ui->location_editbox->text();

    QTableWidgetItem *item = new QTableWidgetItem(title + "  |  " + time + "  |  " + location);
    ui->tableWidget->insertRow(1);
    ui->tableWidget->setItem(1, 0, item);

    ui->title_editbox->clear();
    ui->location_editbox->clear();
}
