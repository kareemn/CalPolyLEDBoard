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
    /*QByteArray str = QByteArray();
    str.append((char)0xc);
    //str.append("Computer Engineerg Event Ticker | Capstone 2013\n\003By: Gomberg, Carteno, Tossoun, Burke, Zuffi\n\002Funding provided by \002G\004o\005o\002g\001l\004e");
    str.append("\004CPE Student Town Hall | Thurs 2/28 11am-12pm | 38-204\n\002All CPE students are invited. Dr. Smith will provide\nan update on the CPE program.");
    str.append((char)0x17);
    qDebug() << port->write(str, str.length()) << str;*/

    ui->setupUi(this);



    settings = new QSettings("Cal Poly CPE", "CPE Display");
    if (!settings->contains("Events"))
    {
        settings->setValue("Events", QVariantList());
    }
    if (!settings->contains("Announcements"))
    {
        settings->setValue("Announcements", QVariantList());
    }

    QVariantList events = settings->value("Events").toList();
    QTableWidgetItem *item = new QTableWidgetItem("<New Item>");
    item->setTextAlignment(Qt::AlignCenter);
    QFont font = item->font();
    font.setBold(true);
    item->setFont(font);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0, 0, item);
    port->write(QByteArray(1, 'E'));
    for (int i=0; i < events.length(); i++)
    {
        QVariantMap event = events[i].toMap();
        QString timeStr = event["date"].toDate().toString("ddd M/d") + " " + event["time"].toTime().toString("h:mm AP");
        QString eventStr = QString("%1 | %2 | %3").arg(event["title"].toString(), timeStr, event["location"].toString());
        QTableWidgetItem *item = new QTableWidgetItem(eventStr);
        ui->tableWidget->insertRow(i+1);
        ui->tableWidget->setItem(i+1, 0, item);
        QString str = QString("%1 | %2 | %3\n%4").arg(event["title"].toString(), timeStr, event["location"].toString(), event["description"].toString());
        port->write(str.toAscii());
        if (i != events.length()-1)
        {
            port->write(QByteArray(1, 0));
        }
    }
    port->write(QByteArray(1, 0x17));
    ui->tableWidget->selectRow(0);

    QVariantList announcements = settings->value("Announcements").toList();
    QTableWidgetItem *item2 = new QTableWidgetItem("<New Item>");
    item2->setTextAlignment(Qt::AlignCenter);
    QFont font2 = item2->font();
    font2.setBold(true);
    item2->setFont(font);
    item2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    ui->tableWidget_2->insertRow(0);
    ui->tableWidget_2->setItem(0, 0, item2);
    for (int i=0; i < announcements.length(); i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(announcements[i].toString());
        ui->tableWidget_2->insertRow(i+1);
        ui->tableWidget_2->setItem(i+1, 0, item);
    }
    ui->tableWidget_2->selectRow(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    settings->sync();
}



void MainWindow::onDataAvailable()
{
    QByteArray data = port->readAll();
    for (int i = 0; i < data.length(); i++)
    {
        qDebug() << i << QString("%1").arg(data.at(i), 0, 16);
    }
    qDebug() << "NEW DATA" << data;
}

// code from: http://agnit.blogspot.com/2009/03/word-wrap-code.html
QString wordWrap(const QString &str, int wrapLength)
{
    QString tempStr= str;
    int len = str.length(), pos= (wrapLength>1)?wrapLength -1:1;

    while (pos < len-1) {
        int tempPos = pos;
        while (tempStr.at(tempPos) != ' ' && tempPos > 0)
            tempPos--;
        if (tempPos > 0)
            pos = tempPos;

        tempStr.replace(pos, 1, '\n');
        pos += pos;
    }
    return tempStr;
}

void wrapTextEdit(QTextEdit *edit)
{
    QString tmp = edit->toPlainText();
    tmp.replace('\n', " ");
    QString text = wordWrap(tmp, DISPLAY_WIDTH);
    if (QString::compare(text, edit->toPlainText()))
    {
        edit->setPlainText(text);
        edit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
    }
}

void MainWindow::deleteRow(QTableWidget *table, QString key)
{
    int row = table->currentIndex().row();
    table->removeRow(row);
    table->selectRow(0);
    QVariantList list = settings->value(key).toList();
    list.removeAt(row-1);
    settings->setValue(key, list);
}



QVariant MainWindow::createEvent(QString title, QDate date, QTime time, QString location, QString description)
{
    QVariantMap tmp;
    tmp["title"] = title;
    tmp["date"] = date;
    tmp["time"] = time;
    tmp["location"] = location;
    tmp["description"] = description;
    return tmp;
}

void MainWindow::resetEventTab()
{
    ui->title_editbox->clear();
    ui->location_editbox->clear();
    ui->date_widget->setSelectedDate(QDate::currentDate());
    ui->time_editbox->setTime(QTime(12, 0));
    ui->description_editbox->clear();
}

void MainWindow::on_description_editbox_textChanged()
{
    wrapTextEdit(ui->description_editbox);
}

void MainWindow::on_delete_button_clicked()
{
    deleteRow(ui->tableWidget, "Events");
}

void MainWindow::on_tableWidget_itemSelectionChanged()
{
    int row = ui->tableWidget->currentIndex().row();
    if (row == 0)
    {
        resetEventTab();
        ui->delete_button->setDisabled(true);
    }
    else
    {
        QVariantMap event = settings->value("Events").toList()[row-1].toMap();
        ui->title_editbox->setText(event["title"].toString());
        ui->location_editbox->setText(event["location"].toString());
        ui->time_editbox->setTime(event["time"].toTime());
        ui->date_widget->setSelectedDate(event["date"].toDate());
        ui->description_editbox->setText(event["description"].toString());
        ui->delete_button->setDisabled(false);
    }
}

void MainWindow::on_save_button_clicked()
{
    // validate the description
    QString description = ui->description_editbox->toPlainText();
    if (description.length() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Error saving event. The description cannot be empty.");
        msgBox.exec();
        return;
    }
    else if (description.split("\n").length() > EVENT_DESC_MAX_LINES)
    {
        QMessageBox msgBox;
        msgBox.setText("Error saving event. The description cannot be longer than 2 lines in length.");
        msgBox.exec();
        return;
    }

    // validate the title
    QString title = ui->title_editbox->text();
    if (title.length() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Error saving event. The event title cannot be empty.");
        msgBox.exec();
        return;
    }
    else if (title.length() > EVENT_MAX_TITLE_LEN)
    {
        QMessageBox msgBox;
        msgBox.setText(QString("Error saving event. The title cannot be longer than %1 characters.").arg(EVENT_MAX_TITLE_LEN));
        msgBox.exec();
        return;
    }

    // validate the location
    QString location = ui->location_editbox->text();
    if (location.length() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Error saving event. The location cannot be empty.");
        msgBox.exec();
        return;
    }
    else if (location.length() > EVENT_MAX_LOCATION_LEN)
    {
        QMessageBox msgBox;
        msgBox.setText(QString("Error saving event. The location cannot be longer than %1 characters.").arg(EVENT_MAX_LOCATION_LEN));
        msgBox.exec();
        return;
    }

    // validate the date and time
    QDate date = ui->date_widget->selectedDate();
    QTime time = ui->time_editbox->time();
    if (date < QDate::currentDate() || (date == QDate::currentDate() && time < QTime::currentTime()))
    {
        QMessageBox msgBox;
        msgBox.setText("Error saving event. The date cannot be in the past.");
        msgBox.exec();
        return;
    }

    // create an event QVariantMap to represent this event
    QVariantMap event;
    event["title"] = title;
    event["date"] = date;
    event["time"] = time;
    event["location"] = location;
    event["description"] = description;

    int row = ui->tableWidget->currentIndex().row();
    QString timeStr = event["date"].toDate().toString("ddd M/d") + " " + event["time"].toTime().toString("h:mm AP");
    QString eventStr = QString("%1 | %2 | %3").arg(event["title"].toString(), timeStr, event["location"].toString());
    QTableWidgetItem *item = new QTableWidgetItem(eventStr);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QVariantList events = settings->value("Events").toList();
    if (row == 0)
    {
        // this is a new event
        ui->tableWidget->insertRow(1);
        ui->tableWidget->setItem(1, 0, item);
        ui->tableWidget->selectRow(0);
        events.append(event);
        settings->setValue("Events", events);
    }
    else
    {
        // edit of existing event
        ui->tableWidget->setItem(row, 0, item);
        ui->tableWidget->selectRow(0);
        events.removeAt(row-1);
        events.insert(row-1, event);
        settings->setValue("Events", events);
    }
    resetEventTab();
}



void MainWindow::resetAnnouncementTab()
{
    ui->announcement_editbox->clear();
}

void MainWindow::on_announcement_editbox_textChanged()
{
    wrapTextEdit(ui->announcement_editbox);
}

void MainWindow::on_delete_button_2_clicked()
{
    deleteRow(ui->tableWidget_2, "Announcements");
}

void MainWindow::on_tableWidget_2_itemSelectionChanged()
{
    int row = ui->tableWidget_2->currentIndex().row();
    if (row == 0)
    {
        resetAnnouncementTab();
        ui->delete_button_2->setDisabled(true);
    }
    else
    {
        ui->announcement_editbox->setText(settings->value("Announcements").toList()[row-1].toString());
        ui->delete_button_2->setDisabled(false);
    }
}

void MainWindow::on_save_button_2_clicked()
{
    // validate the description
    QString announcement = ui->announcement_editbox->toPlainText();
    if (announcement.length() == 0)
    {
        QMessageBox msgBox;
        msgBox.setText("Error saving announcement. It cannot be empty.");
        msgBox.exec();
        return;
    }
    else if (announcement.split("\n").length() > ANNOUNCE_MAX_LINES)
    {
        QMessageBox msgBox;
        msgBox.setText("Error saving announcement. It cannot be longer than 3 lines in length.");
        msgBox.exec();
        return;
    }

    int row = ui->tableWidget->currentIndex().row();
    QTableWidgetItem *item = new QTableWidgetItem(announcement);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QVariantList annoumcents = settings->value("Announcements").toList();
    if (row == 0)
    {
        ui->tableWidget->insertRow(1);
        ui->tableWidget->setItem(1, 0, item);
        ui->tableWidget->selectRow(0);
        annoumcents.append(announcement);
        settings->setValue("Announcements", annoumcents);
    }
    else
    {
        ui->tableWidget->setItem(row, 0, item);
        ui->tableWidget->selectRow(0);
        annoumcents.removeAt(row-1);
        annoumcents.insert(row-1, announcement);
        settings->setValue("Announcements", annoumcents);
    }
    resetAnnouncementTab();
}
