#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    needsUpdate = false;
    timer = new QTimer(this);
    timer->setInterval(10000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerInterval()));
    timer->start();

    port = 0;
    ui->setupUi(this);
    settings = new QSettings("Cal Poly CPE", "CPE Display");
    if (!settings->contains("Events"))
    {
        settings->setValue("Events", QVariantList());
    }
    settings->remove("Announcements");
    if (!settings->contains("Announcements"))
    {
        settings->setValue("Announcements", QVariantList());
    }
    if (!settings->contains("OfficeHours"))
    {
        settings->setValue("OfficeHours", QVariantList());
    }

    if (!settings->contains("EventsTopColor"))
    {
        settings->setValue("EventsTopColor", QVariant(1));
    }
    if (!settings->contains("EventsDescColor"))
    {
        settings->setValue("EventsDescColor", QVariant(5));
    }
    if (!settings->contains("AnnouncementsColor"))
    {
        settings->setValue("AnnouncementsColor", QVariant(3));
    }
    if (!settings->contains("OfficeHourTopColor"))
    {
        settings->setValue("OfficeHourTopColor", QVariant(7));
    }
    if (!settings->contains("OfficeHourDescColor"))
    {
        settings->setValue("OfficeHourDescColor", QVariant(7));
    }

    ui->display_status_label->setText("Not Connected");
    ui->event_top_color->setCurrentIndex(settings->value("EventsTopColor").toInt()-1);
    ui->event_desc_color->setCurrentIndex(settings->value("EventsDescColor").toInt()-1);
    ui->announcement_color->setCurrentIndex(settings->value("AnnouncementsColor").toInt()-1);
    ui->officehours_top_color->setCurrentIndex(settings->value("OfficeHourTopColor").toInt()-1);
    ui->officehours_hours_color->setCurrentIndex(settings->value("OfficeHourDescColor").toInt()-1);

    // find all available com ports
    ui->port_comboBox->blockSignals(true);
    ui->port_comboBox->addItem("---");
    foreach (QextPortInfo info, QextSerialEnumerator::getPorts())
    {
        if (info.portName != "")
        {
            ui->port_comboBox->addItem(info.portName);
        }
    }
    ui->port_comboBox->blockSignals(false);

    if (settings->contains("COMPort"))
    {
        QString port = settings->value("COMPort").toString();
        for (int i = 0; i < ui->port_comboBox->count(); i++)
        {
            if (port == ui->port_comboBox->itemText(i))
            {
                ui->port_comboBox->setCurrentIndex(i);
                break;
            }
        }
    }

    QVariantList events = settings->value("Events").toList();
    QTableWidgetItem *item = new QTableWidgetItem("<New Event>");
    item->setTextAlignment(Qt::AlignCenter);
    QFont font = item->font();
    font.setBold(true);
    item->setFont(font);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    ui->tableWidget->insertRow(0);
    ui->tableWidget->setItem(0, 0, item);
    for (int i=0; i < events.length(); i++)
    {
        QVariantMap event = events[i].toMap();
        QString timeStr = event["date"].toDate().toString("ddd M/d") + " " + event["time"].toTime().toString("h:mm AP");
        QString eventStr = QString("%1 | %2 | %3").arg(event["title"].toString(), timeStr, event["location"].toString());
        QTableWidgetItem *item = new QTableWidgetItem(eventStr);
        ui->tableWidget->insertRow(i+1);
        ui->tableWidget->setItem(i+1, 0, item);
    }
    ui->tableWidget->selectRow(0);

    QVariantList announcements = settings->value("Announcements").toList();
    QTableWidgetItem *item2 = new QTableWidgetItem("<New Announcement>");
    item2->setTextAlignment(Qt::AlignCenter);
    QFont font2 = item2->font();
    font2.setBold(true);
    item2->setFont(font);
    item2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    ui->tableWidget_2->insertRow(0);
    ui->tableWidget_2->setItem(0, 0, item2);
    for (int i=0; i < announcements.length(); i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(announcements[i].toMap()["text"].toString());
        ui->tableWidget_2->insertRow(i+1);
        ui->tableWidget_2->setItem(i+1, 0, item);
    }
    ui->tableWidget_2->selectRow(0);

    QVariantList officeHours = settings->value("OfficeHours").toList();
    QTableWidgetItem *item3 = new QTableWidgetItem("<New Professor>");
    item3->setTextAlignment(Qt::AlignCenter);
    QFont font3 = item3->font();
    font3.setBold(true);
    item3->setFont(font);
    item3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    ui->tableWidget_3->insertRow(0);
    ui->tableWidget_3->setItem(0, 0, item3);
    for (int i=0; i < officeHours.length(); i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(QString("%1 | %2 | %3").arg(officeHours[i].toMap()["name"].toString(), officeHours[i].toMap()["officeLocation"].toString(), officeHours[i].toMap()["hours"].toString()));
        ui->tableWidget_3->insertRow(i+1);
        ui->tableWidget_3->setItem(i+1, 0, item);
    }
    ui->tableWidget_3->selectRow(0);

    // open up on the first tab
    ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    settings->sync();
    port->close();
    delete port;
}

void MainWindow::sendDataToADK()
{
    qDebug() << "here";
    QVariant comPort = settings->value("COMPort").toString();
    if (comPort.isNull() || comPort.toString().isEmpty())
    {
        qDebug() << "ERROR";
        return;
    }
    if (!port || !port->isOpen())
    {
        port = new QextSerialPort(comPort.toString());
        port->setBaudRate(BAUD9600);
        port->setTimeout(5000);
        port->open(QextSerialPort::ReadWrite);
    }
    qDebug() << "here2" << port->isOpen();

    // send the events
    port->write(QByteArray(1, 'E'));
    foreach(QVariant event_var, settings->value("Events").toList())
    {
        QVariantMap event = event_var.toMap();
        QString timeStr = event["date"].toDate().toString("ddd M/d") + " " + event["time"].toTime().toString("h:mm AP");
        char color1 = (char)settings->value("EventsTopColor").toInt();
        char color2 = (char)settings->value("EventsDescColor").toInt();
        QString str = QString("%1%2 | %3 | %4\n%5%6").arg(QString(color1), event["title"].toString(), timeStr, event["location"].toString(), QString(color2), event["description"].toString());
        port->write(str.toAscii());
        port->write(QByteArray(1, 0));
    }
    // send the annoumcents together with the events
    foreach(QVariant annoumcent, settings->value("Announcements").toList())
    {
        char color = (char)settings->value("AnnouncementsColor").toInt();
        port->write(annoumcent.toMap()["text"].toString().toAscii().prepend(color));
        port->write(QByteArray(1, 0));
    }
    port->write(QByteArray(1, 0x17));

    // send the office hours
    port->write(QByteArray(1, 'O'));
    foreach(QVariant officeHours_var, settings->value("OfficeHours").toList())
    {
        QVariantMap officeHours = officeHours_var.toMap();
        char color1 = (char)settings->value("OfficeHourTopColor").toInt();
        char color2 = (char)settings->value("OfficeHourDescColor").toInt();
        QString officeHoursStr = QString("%1%2 | %3\n%4%5").arg(QString(color1), officeHours["name"].toString(), officeHours["officeLocation"].toString(), QString(color2), officeHours["hours"].toString());
        port->write(officeHoursStr.toAscii());
        port->write(QByteArray(1, 0));
    }
    port->write(QByteArray(1, 0x17));
    ui->display_status_label->setText(QString("Last synced at %1").arg(QTime::currentTime().toString("h:m:s AP")));
    needsUpdate = false;
    qDebug() << "here3";

}
// code from: http://agnit.blogspot.com/2009/03/word-wrap-code.html
QString wordWrapHelper(const QString &str, int wrapLength)
{
    QString tempStr = str;
    int len = str.length(), pos = wrapLength-1;

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

QString wordWrap(const QString &str)
{
    QStringList lines = str.split('\n');
    for (int i = 0; i < lines.length(); i++)
    {
        if (lines.at(i).length() > DISPLAY_WIDTH)
        {
            QStringList newLines = wordWrapHelper(lines.at(i), DISPLAY_WIDTH).split('\n');
            lines.removeAt(i);
            for (int j = newLines.length()-1; j >= 0; j--)
            {
                lines.insert(i, newLines[j]);
            }
        }
    }
    return lines.join("\n");
}

QString prevText;
void wrapTextEdit(QTextEdit *edit)
{
    QString tmp = edit->toPlainText();
    tmp = wordWrap(tmp);
    if (QString::compare(tmp, prevText))
    {
        prevText = tmp;
        if (tmp != edit->toPlainText())
        {
            edit->setPlainText(tmp);
            edit->moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
        }
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
    needsUpdate = true;
}

void MainWindow::displayError(QString errMsg)
{
    QMessageBox msgBox;
    msgBox.setText(errMsg);
    msgBox.exec();
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
    QString description = wordWrap(ui->description_editbox->toPlainText());
    if (description.length() == 0)
    {
        displayError("Error saving event. The description cannot be empty.");
        return;
    }
    else if (description.split("\n").length() > EVENT_DESC_MAX_LINES)
    {
        displayError("Error saving event. The description cannot be longer than 2 lines in length.");
        return;
    }

    // validate the title
    QString title = ui->title_editbox->text();
    if (title.length() == 0)
    {
        displayError("Error saving event. The event title cannot be empty.");
        return;
    }
    else if (title.length() > EVENT_MAX_TITLE_LEN)
    {
        displayError(QString("Error saving event. The title cannot be longer than %1 characters.").arg(EVENT_MAX_TITLE_LEN));
        return;
    }

    // validate the location
    QString location = ui->location_editbox->text();
    if (location.length() == 0)
    {
        displayError("Error saving event. The location cannot be empty.");
        return;
    }
    else if (location.length() > EVENT_MAX_LOCATION_LEN)
    {
        displayError(QString("Error saving event. The location cannot be longer than %1 characters.").arg(EVENT_MAX_LOCATION_LEN));
        return;
    }

    // validate the start date and time
    QDate date = ui->date_widget->selectedDate();
    QTime time = ui->time_editbox->time();
    QTime endTime = ui->time_editbox_3->time();
    if (date < QDate::currentDate() || (date == QDate::currentDate() && endTime < QTime::currentTime()))
    {
        displayError("Error saving event. The end time / date cannot be in the past.");
        return;
    }

    // create an event QVariantMap to represent this event
    QVariantMap event;
    event["title"] = title;
    event["date"] = date;
    event["time"] = time;
    event["location"] = location;
    event["description"] = description;
    event["endTime"] = endTime;

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
        events.insert(0, event);
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
    needsUpdate = true;
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
        ui->announcement_editbox->setText(settings->value("Announcements").toList().at(row-1).toMap()["text"].toString());
        ui->delete_button_2->setDisabled(false);
    }
}

void MainWindow::on_save_button_2_clicked()
{
    // validate the description
    QString announcement = wordWrap(ui->announcement_editbox->toPlainText());
    if (announcement.length() == 0)
    {
        displayError("Error saving announcement. It cannot be empty.");
        return;
    }
    else if (announcement.split("\n").length() > ANNOUNCE_MAX_LINES)
    {
        displayError("Error saving announcement. It cannot be longer than 3 lines in length.");
        return;
    }


    // validate the start date and time
    QDateTime end;
    end.setDate(ui->date_widget_2->selectedDate());
    end.setTime(ui->time_editbox_2->time());
    if (end < QDateTime::currentDateTime())
    {
        displayError("Error saving event. The end time / date cannot be in the past.");
        return;
    }

    QVariantMap announcementMap;
    announcementMap["text"] = announcement;
    announcementMap["end"] = end;

    int row = ui->tableWidget_2->currentIndex().row();
    QString itemStr = announcement;
    itemStr.replace('\n', ' ');
    QTableWidgetItem *item = new QTableWidgetItem(itemStr);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QVariantList annoumcents = settings->value("Announcements").toList();
    if (row == 0)
    {
        ui->tableWidget_2->insertRow(1);
        ui->tableWidget_2->setItem(1, 0, item);
        ui->tableWidget_2->selectRow(0);
        annoumcents.insert(0, announcementMap);
        settings->setValue("Announcements", annoumcents);
    }
    else
    {
        ui->tableWidget_2->setItem(row, 0, item);
        ui->tableWidget_2->selectRow(0);
        annoumcents.removeAt(row-1);
        annoumcents.insert(row-1, announcementMap);
        settings->setValue("Announcements", annoumcents);
    }
    needsUpdate = true;
    resetAnnouncementTab();
}



void MainWindow::resetOfficeHoursTab()
{
    ui->professor_editbox->clear();
    ui->office_editbox->clear();
    ui->officeHours_editbox->clear();
}

void MainWindow::on_tableWidget_3_itemSelectionChanged()
{
    int row = ui->tableWidget_3->currentIndex().row();
    if (row == 0)
    {
        resetOfficeHoursTab();
        ui->delete_button_3->setDisabled(true);
    }
    else
    {
        QVariantMap officeHour = settings->value("OfficeHours").toList()[row-1].toMap();
        ui->office_editbox->setText(officeHour["officeLocation"].toString());
        ui->professor_editbox->setText(officeHour["name"].toString());
        ui->officeHours_editbox->setText(officeHour["hours"].toString());
        ui->delete_button_3->setDisabled(false);
    }
}

void MainWindow::on_save_button_3_clicked()
{
    // validate the professor name field
    QString name = ui->professor_editbox->text();
    if (name.length() == 0)
    {
        displayError("Error saving office hour. Professor name cannot be empty.");
        return;
    }
    else if (name.length() > MAX_PROFESSOR_NAME_LEN)
    {
        displayError(QString("Error saving office hour. Professor name cannot be longer than %1 characters.").arg(MAX_PROFESSOR_NAME_LEN));
        return;
    }

    // validate the office location field
    QString officeLocation = ui->office_editbox->text();
    if (officeLocation.length() == 0)
    {
        displayError("Error saving office hour. Office location cannot be empty.");
        return;
    }
    else if (officeLocation.length() > MAX_OFFICE_LOCATION_LEN)
    {
        displayError(QString("Error saving office hour. Office location cannot be longer than %1 characters.").arg(MAX_OFFICE_LOCATION_LEN));
        return;
    }

    // validate the office hours
    QString hours = wordWrap(ui->officeHours_editbox->toPlainText());
    if (hours.length() == 0)
    {
        displayError("Error saving office hour. Office hours cannot be empty.");
        return;
    }
    else if (hours.split("\n").length() > OFFICE_HOUR_MAX_LINES)
    {
        displayError(QString("Error saving office hour. Office hours cannot be longer than %1 lines.").arg(OFFICE_HOUR_MAX_LINES));
        return;
    }

    QVariantMap officeHour;
    officeHour["name"] = name;
    officeHour["officeLocation"] = officeLocation;
    officeHour["hours"] = hours;

    int row = ui->tableWidget_3->currentIndex().row();
    QString officeHourStr = QString("%1 | %2 | %3").arg(name, officeLocation, hours);
    officeHourStr.replace('\n', ' ');
    QTableWidgetItem *item = new QTableWidgetItem(officeHourStr);
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    QVariantList officeHours = settings->value("OfficeHours").toList();
    if (row == 0)
    {
        ui->tableWidget_3->insertRow(1);
        ui->tableWidget_3->setItem(1, 0, item);
        ui->tableWidget_3->selectRow(0);
        officeHours.insert(0, officeHour);
        settings->setValue("OfficeHours", officeHours);
    }
    else
    {
        ui->tableWidget_3->setItem(row, 0, item);
        ui->tableWidget_3->selectRow(0);
        officeHours.removeAt(row-1);
        officeHours.insert(row-1, officeHour);
        settings->setValue("OfficeHours", officeHours);
    }
    needsUpdate = true;
    resetOfficeHoursTab();
}

void MainWindow::on_delete_button_3_clicked()
{
    deleteRow(ui->tableWidget_3, "OfficeHours");
}

void MainWindow::on_officeHours_editbox_textChanged()
{
    wrapTextEdit(ui->officeHours_editbox);
}

void MainWindow::on_port_comboBox_currentIndexChanged(int index)
{
    QString value = ui->port_comboBox->itemText(index);
    if (value == "---")
    {
        settings->remove("COMPort");
    }
    else
    {
        settings->setValue("COMPort", QVariant(value));
        needsUpdate = true;
    }
}

void MainWindow::on_pushButton_clicked()
{
    sendDataToADK();
}

void MainWindow::on_event_top_color_currentIndexChanged(int index)
{
    settings->setValue("EventsTopColor", QVariant(index+1));
    needsUpdate = true;
}

void MainWindow::on_event_desc_color_currentIndexChanged(int index)
{
    settings->setValue("EventsDescColor", QVariant(index+1));
    needsUpdate = true;
}

void MainWindow::on_announcement_color_currentIndexChanged(int index)
{
    settings->setValue("AnnouncementsColor", QVariant(index+1));
    needsUpdate = true;
}

void MainWindow::on_officehours_top_color_currentIndexChanged(int index)
{
    settings->setValue("OfficeHourTopColor", QVariant(index+1));
    needsUpdate = true;
}

void MainWindow::on_officehours_hours_color_currentIndexChanged(int index)
{
    settings->setValue("OfficeHourDescColor", QVariant(index+1));
    needsUpdate = true;
}

void MainWindow::timerInterval()
{
    // check for events which have ended
    QVariantList events = settings->value("Events").toList();
    for (int i = events.length()-1; i >= 0; i--)
    {
        QVariantMap event = events.at(i).toMap();
        QDate endDate = event["date"].toDate();
        QTime endTime = event["endTime"].toTime();
        if (endDate < QDate::currentDate() || (endDate == QDate::currentDate() && endTime < QTime::currentTime()))
        {
            events.removeAt(i);
            ui->tableWidget->removeRow(i);
            ui->tableWidget->selectRow(0);
            needsUpdate = true;
        }
    }
    settings->setValue("Events", events);

    // check for annoumcenents which have expired
    QVariantList announcements = settings->value("Anouncements").toList();
    for (int i = announcements.length()-1; i >= 0; i--)
    {
        QVariantMap announcement = announcements.at(i).toMap();
        QDateTime end = announcement["end"].toDateTime();
        if (end < QDateTime::currentDateTime())
        {
            announcements.removeAt(i);
            ui->tableWidget->removeRow(i);
            ui->tableWidget->selectRow(0);
            needsUpdate = true;
        }
    }
    settings->setValue("Anouncements", announcements);

    if (needsUpdate)
    {
        sendDataToADK();
    }
}
