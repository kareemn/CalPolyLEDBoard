#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include <QSettings>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QTimer>

#include "qextserialport.h"
#include "qextserialenumerator.h"

#define DISPLAY_WIDTH           53
#define EVENT_DESC_MAX_LINES    2
#define EVENT_MAX_TITLE_LEN     35
#define EVENT_MAX_LOCATION_LEN  10
#define ANNOUNCE_MAX_LINES      3
#define OFFICE_HOUR_MAX_LINES   2
#define MAX_PROFESSOR_NAME_LEN  40
#define MAX_OFFICE_LOCATION_LEN 20


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
    void on_save_button_clicked();
    void on_tableWidget_itemSelectionChanged();
    void on_description_editbox_textChanged();
    void closeEvent(QCloseEvent *);
    void on_delete_button_clicked();
    void on_announcement_editbox_textChanged();
    void on_delete_button_2_clicked();
    void on_save_button_2_clicked();
    void on_tableWidget_2_itemSelectionChanged();
    void on_save_button_3_clicked();
    void on_delete_button_3_clicked();
    void on_officeHours_editbox_textChanged();
    void on_tableWidget_3_itemSelectionChanged();
    void on_port_comboBox_currentIndexChanged(int index);
    void on_pushButton_clicked();
    void on_event_top_color_currentIndexChanged(int index);
    void on_event_desc_color_currentIndexChanged(int index);
    void on_announcement_color_currentIndexChanged(int index);
    void on_officehours_top_color_currentIndexChanged(int index);
    void on_officehours_hours_color_currentIndexChanged(int index);
    void timerInterval();

private:
    Ui::MainWindow *ui;
    QSettings *settings;
    QextSerialPort *port;
    QTimer *timer;
    bool needsUpdate;

    void sendDataToADK();
    QVariant createEvent(QString name, QDate date, QTime time, QString location, QString description);
    void resetEventTab();
    void resetAnnouncementTab();
    void deleteRow(QTableWidget *table, QString key);
    void displayError(QString);
    void resetOfficeHoursTab();
};

#endif // MAINWINDOW_H
