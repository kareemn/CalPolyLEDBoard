/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Feb 27 14:54:55 2013
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
#include <QtGui/QTextEdit>
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
    QVBoxLayout *verticalLayout_6;
    QTableWidget *tableWidget;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *title_label;
    QLineEdit *title_editbox;
    QSpacerItem *horizontalSpacer_2;
    QLabel *location_label;
    QLineEdit *location_editbox;
    QSpacerItem *horizontalSpacer;
    QLabel *time_label;
    QTimeEdit *time_editbox;
    QVBoxLayout *verticalLayout_3;
    QLabel *description_label;
    QTextEdit *description_editbox;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *save_button;
    QPushButton *delete_button;
    QCalendarWidget *date_widget;
    QWidget *announcements_tab;
    QVBoxLayout *verticalLayout_8;
    QTableWidget *tableWidget_2;
    QFrame *line_2;
    QVBoxLayout *verticalLayout_7;
    QLabel *announcement_label;
    QTextEdit *announcement_editbox;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *save_button_2;
    QPushButton *delete_button_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(708, 358);
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
        verticalLayout_6 = new QVBoxLayout(event_tab);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
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

        verticalLayout_6->addWidget(tableWidget);

        line = new QFrame(event_tab);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShadow(QFrame::Sunken);
        line->setLineWidth(3);
        line->setFrameShape(QFrame::HLine);

        verticalLayout_6->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));

        verticalLayout_4->addLayout(verticalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        title_label = new QLabel(event_tab);
        title_label->setObjectName(QString::fromUtf8("title_label"));

        horizontalLayout_2->addWidget(title_label);

        title_editbox = new QLineEdit(event_tab);
        title_editbox->setObjectName(QString::fromUtf8("title_editbox"));

        horizontalLayout_2->addWidget(title_editbox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        location_label = new QLabel(event_tab);
        location_label->setObjectName(QString::fromUtf8("location_label"));

        horizontalLayout_2->addWidget(location_label);

        location_editbox = new QLineEdit(event_tab);
        location_editbox->setObjectName(QString::fromUtf8("location_editbox"));
        location_editbox->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(location_editbox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        time_label = new QLabel(event_tab);
        time_label->setObjectName(QString::fromUtf8("time_label"));

        horizontalLayout_2->addWidget(time_label);

        time_editbox = new QTimeEdit(event_tab);
        time_editbox->setObjectName(QString::fromUtf8("time_editbox"));

        horizontalLayout_2->addWidget(time_editbox);


        verticalLayout_4->addLayout(horizontalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        description_label = new QLabel(event_tab);
        description_label->setObjectName(QString::fromUtf8("description_label"));

        verticalLayout_3->addWidget(description_label);

        description_editbox = new QTextEdit(event_tab);
        description_editbox->setObjectName(QString::fromUtf8("description_editbox"));
        description_editbox->setMaximumSize(QSize(16777215, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier New"));
        font.setPointSize(8);
        description_editbox->setFont(font);
        description_editbox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        description_editbox->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        description_editbox->setLineWrapMode(QTextEdit::FixedColumnWidth);
        description_editbox->setLineWrapColumnOrWidth(64);
        description_editbox->setAcceptRichText(false);

        verticalLayout_3->addWidget(description_editbox);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);


        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        save_button = new QPushButton(event_tab);
        save_button->setObjectName(QString::fromUtf8("save_button"));

        horizontalLayout_3->addWidget(save_button);

        delete_button = new QPushButton(event_tab);
        delete_button->setObjectName(QString::fromUtf8("delete_button"));

        horizontalLayout_3->addWidget(delete_button);


        verticalLayout_4->addLayout(horizontalLayout_3);


        horizontalLayout->addLayout(verticalLayout_4);

        date_widget = new QCalendarWidget(event_tab);
        date_widget->setObjectName(QString::fromUtf8("date_widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(date_widget->sizePolicy().hasHeightForWidth());
        date_widget->setSizePolicy(sizePolicy);
        date_widget->setMaximumSize(QSize(200, 16777215));
        date_widget->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
        date_widget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

        horizontalLayout->addWidget(date_widget);


        verticalLayout_6->addLayout(horizontalLayout);

        tabWidget->addTab(event_tab, QString());
        announcements_tab = new QWidget();
        announcements_tab->setObjectName(QString::fromUtf8("announcements_tab"));
        verticalLayout_8 = new QVBoxLayout(announcements_tab);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        tableWidget_2 = new QTableWidget(announcements_tab);
        if (tableWidget_2->columnCount() < 1)
            tableWidget_2->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem1);
        tableWidget_2->setObjectName(QString::fromUtf8("tableWidget_2"));
        tableWidget_2->setMaximumSize(QSize(16777215, 100));
        tableWidget_2->setColumnCount(1);
        tableWidget_2->horizontalHeader()->setVisible(false);
        tableWidget_2->horizontalHeader()->setStretchLastSection(true);
        tableWidget_2->verticalHeader()->setVisible(false);
        tableWidget_2->verticalHeader()->setDefaultSectionSize(20);

        verticalLayout_8->addWidget(tableWidget_2);

        line_2 = new QFrame(announcements_tab);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_8->addWidget(line_2);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        announcement_label = new QLabel(announcements_tab);
        announcement_label->setObjectName(QString::fromUtf8("announcement_label"));

        verticalLayout_7->addWidget(announcement_label);

        announcement_editbox = new QTextEdit(announcements_tab);
        announcement_editbox->setObjectName(QString::fromUtf8("announcement_editbox"));
        announcement_editbox->setMaximumSize(QSize(16777215, 60));
        announcement_editbox->setFont(font);
        announcement_editbox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        announcement_editbox->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        announcement_editbox->setLineWrapMode(QTextEdit::FixedColumnWidth);
        announcement_editbox->setLineWrapColumnOrWidth(64);
        announcement_editbox->setAcceptRichText(false);

        verticalLayout_7->addWidget(announcement_editbox);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        save_button_2 = new QPushButton(announcements_tab);
        save_button_2->setObjectName(QString::fromUtf8("save_button_2"));

        horizontalLayout_4->addWidget(save_button_2);

        delete_button_2 = new QPushButton(announcements_tab);
        delete_button_2->setObjectName(QString::fromUtf8("delete_button_2"));

        horizontalLayout_4->addWidget(delete_button_2);


        verticalLayout_7->addLayout(horizontalLayout_4);


        verticalLayout_8->addLayout(verticalLayout_7);

        tabWidget->addTab(announcements_tab, QString());

        verticalLayout_2->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


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
        location_label->setText(QApplication::translate("MainWindow", "Location", 0, QApplication::UnicodeUTF8));
        time_label->setText(QApplication::translate("MainWindow", "Time", 0, QApplication::UnicodeUTF8));
        time_editbox->setDisplayFormat(QApplication::translate("MainWindow", "h:mm AP", 0, QApplication::UnicodeUTF8));
        description_label->setText(QApplication::translate("MainWindow", "Description (2 lines)", 0, QApplication::UnicodeUTF8));
        save_button->setText(QApplication::translate("MainWindow", "Save Event", 0, QApplication::UnicodeUTF8));
        delete_button->setText(QApplication::translate("MainWindow", "Delete Event", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(event_tab), QApplication::translate("MainWindow", "Events", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Event Title", 0, QApplication::UnicodeUTF8));
        announcement_label->setText(QApplication::translate("MainWindow", "Annoumcent (3 lines max)", 0, QApplication::UnicodeUTF8));
        save_button_2->setText(QApplication::translate("MainWindow", "Save Announcement", 0, QApplication::UnicodeUTF8));
        delete_button_2->setText(QApplication::translate("MainWindow", "Delete Announcement", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(announcements_tab), QApplication::translate("MainWindow", "Announcements", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
