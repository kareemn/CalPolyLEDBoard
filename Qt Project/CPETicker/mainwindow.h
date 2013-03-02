#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include <QSettings>
#include <QTableWidgetItem>
#include <QMessageBox>

#include "qextserialport.h"
#include "qextserialenumerator.h"

#define DISPLAY_WIDTH           64
#define EVENT_DESC_MAX_LINES    2
#define EVENT_MAX_TITLE_LEN     40
#define EVENT_MAX_LOCATION_LEN  15
#define ANNOUNCE_MAX_LINES      3


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
    void on_tableWidget_itemSelectionChanged();
    void on_description_editbox_textChanged();
    void closeEvent(QCloseEvent *);
    void on_delete_button_clicked();
    void on_announcement_editbox_textChanged();
    void on_delete_button_2_clicked();

    void on_save_button_2_clicked();

    void on_tableWidget_2_itemSelectionChanged();

private:
    Ui::MainWindow *ui;
    QextSerialPort *port;
    QSettings *settings;

    QVariant createEvent(QString name, QDate date, QTime time, QString location, QString description);
    void resetEventTab();
    void resetAnnouncementTab();
    void deleteRow(QTableWidget *table, QString key);
};

#endif // MAINWINDOW_H
