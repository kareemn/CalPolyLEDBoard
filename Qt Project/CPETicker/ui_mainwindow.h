/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Jan 16 16:51:13 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCalendarWidget>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QTimeEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *status_tab;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QWidget *event_tab;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *tableWidget;
    QFrame *line;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *title_label;
    QLineEdit *title_editbox;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *time_label;
    QTimeEdit *time_editbox;
    QHBoxLayout *horizontalLayout;
    QLabel *location_label;
    QLineEdit *location_editbox;
    QSpacerItem *verticalSpacer_2;
    QCalendarWidget *date_widget;
    QPushButton *save_button;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(543, 360);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        status_tab = new QWidget();
        status_tab->setObjectName(QString::fromUtf8("status_tab"));
        verticalLayout = new QVBoxLayout(status_tab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_3 = new QLabel(status_tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        tabWidget->addTab(status_tab, QString());
        event_tab = new QWidget();
        event_tab->setObjectName(QString::fromUtf8("event_tab"));
        verticalLayout_4 = new QVBoxLayout(event_tab);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tableWidget = new QTableWidget(event_tab);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setMaximumSize(QSize(16777215, 100));
        tableWidget->setColumnCount(1);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setDefaultSectionSize(20);

        verticalLayout_4->addWidget(tableWidget);

        line = new QFrame(event_tab);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShadow(QFrame::Sunken);
        line->setLineWidth(3);
        line->setFrameShape(QFrame::HLine);

        verticalLayout_4->addWidget(line);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        title_label = new QLabel(event_tab);
        title_label->setObjectName(QString::fromUtf8("title_label"));

        verticalLayout_5->addWidget(title_label);

        title_editbox = new QLineEdit(event_tab);
        title_editbox->setObjectName(QString::fromUtf8("title_editbox"));

        verticalLayout_5->addWidget(title_editbox);


        verticalLayout_3->addLayout(verticalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        time_label = new QLabel(event_tab);
        time_label->setObjectName(QString::fromUtf8("time_label"));

        horizontalLayout_2->addWidget(time_label);

        time_editbox = new QTimeEdit(event_tab);
        time_editbox->setObjectName(QString::fromUtf8("time_editbox"));

        horizontalLayout_2->addWidget(time_editbox);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        location_label = new QLabel(event_tab);
        location_label->setObjectName(QString::fromUtf8("location_label"));

        horizontalLayout->addWidget(location_label);

        location_editbox = new QLineEdit(event_tab);
        location_editbox->setObjectName(QString::fromUtf8("location_editbox"));

        horizontalLayout->addWidget(location_editbox);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        horizontalLayout_3->addLayout(verticalLayout_3);

        date_widget = new QCalendarWidget(event_tab);
        date_widget->setObjectName(QString::fromUtf8("date_widget"));
        date_widget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

        horizontalLayout_3->addWidget(date_widget);


        verticalLayout_4->addLayout(horizontalLayout_3);

        save_button = new QPushButton(event_tab);
        save_button->setObjectName(QString::fromUtf8("save_button"));

        verticalLayout_4->addWidget(save_button);

        tabWidget->addTab(event_tab, QString());

        verticalLayout_2->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CPE Ticker Control Panel", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Current Events", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(status_tab), QApplication::translate("MainWindow", "Status", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Event Title", 0, QApplication::UnicodeUTF8));
        title_label->setText(QApplication::translate("MainWindow", "Event Title", 0, QApplication::UnicodeUTF8));
        time_label->setText(QApplication::translate("MainWindow", "Time", 0, QApplication::UnicodeUTF8));
        time_editbox->setDisplayFormat(QApplication::translate("MainWindow", "h:mm AP", 0, QApplication::UnicodeUTF8));
        location_label->setText(QApplication::translate("MainWindow", "Location", 0, QApplication::UnicodeUTF8));
        save_button->setText(QApplication::translate("MainWindow", "Save Event", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(event_tab), QApplication::translate("MainWindow", "Events", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
