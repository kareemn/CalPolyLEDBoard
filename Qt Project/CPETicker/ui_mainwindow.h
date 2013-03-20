/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Mar 20 08:33:46 2013
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
#include <QtGui/QComboBox>
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
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_7;
    QComboBox *port_comboBox;
    QPushButton *pushButton;
    QFrame *line_4;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_8;
    QLabel *display_status_label;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_5;
    QSpacerItem *verticalSpacer;
    QLabel *label_9;
    QWidget *event_tab;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_11;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_6;
    QComboBox *event_top_color;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_10;
    QComboBox *event_desc_color;
    QTableWidget *tableWidget;
    QFrame *line;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *title_label;
    QLineEdit *title_editbox;
    QSpacerItem *horizontalSpacer_2;
    QLabel *location_label;
    QLineEdit *location_editbox;
    QSpacerItem *horizontalSpacer_9;
    QLabel *time_label;
    QTimeEdit *time_editbox;
    QHBoxLayout *horizontalLayout;
    QLabel *description_label;
    QSpacerItem *horizontalSpacer;
    QLabel *time_label_3;
    QTimeEdit *time_editbox_3;
    QTextEdit *description_editbox;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *save_button;
    QPushButton *delete_button;
    QCalendarWidget *date_widget;
    QWidget *announcements_tab;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_12;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_14;
    QComboBox *announcement_color;
    QTableWidget *tableWidget_2;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_10;
    QLabel *announcement_label;
    QSpacerItem *horizontalSpacer_8;
    QLabel *time_label_2;
    QTimeEdit *time_editbox_2;
    QTextEdit *announcement_editbox;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *save_button_2;
    QPushButton *delete_button_2;
    QCalendarWidget *date_widget_2;
    QWidget *officeHours_tab;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_12;
    QLabel *label_15;
    QComboBox *officehours_top_color;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label_16;
    QComboBox *officehours_hours_color;
    QTableWidget *tableWidget_3;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QLineEdit *professor_editbox;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_4;
    QLineEdit *office_editbox;
    QLabel *label;
    QTextEdit *officeHours_editbox;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *save_button_3;
    QPushButton *delete_button_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(708, 358);
        MainWindow->setMinimumSize(QSize(708, 358));
        MainWindow->setMaximumSize(QSize(708, 358));
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
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_3 = new QLabel(status_tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);

        horizontalLayout_9->addWidget(label_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_4);

        label_7 = new QLabel(status_tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_9->addWidget(label_7);

        port_comboBox = new QComboBox(status_tab);
        port_comboBox->setObjectName(QString::fromUtf8("port_comboBox"));

        horizontalLayout_9->addWidget(port_comboBox);

        pushButton = new QPushButton(status_tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_9->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_9);

        line_4 = new QFrame(status_tab);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_6);

        label_8 = new QLabel(status_tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_8->addWidget(label_8);

        display_status_label = new QLabel(status_tab);
        display_status_label->setObjectName(QString::fromUtf8("display_status_label"));

        horizontalLayout_8->addWidget(display_status_label);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_10);

        label_5 = new QLabel(status_tab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(270, 130));
        label_5->setMaximumSize(QSize(270, 130));
        label_5->setPixmap(QPixmap(QString::fromUtf8("logov3.png")));
        label_5->setScaledContents(true);

        horizontalLayout_8->addWidget(label_5);


        verticalLayout->addLayout(horizontalLayout_8);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_9 = new QLabel(status_tab);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout->addWidget(label_9);

        tabWidget->addTab(status_tab, QString());
        event_tab = new QWidget();
        event_tab->setObjectName(QString::fromUtf8("event_tab"));
        verticalLayout_4 = new QVBoxLayout(event_tab);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_11 = new QLabel(event_tab);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_7->addWidget(label_11);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        label_6 = new QLabel(event_tab);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_7->addWidget(label_6);

        event_top_color = new QComboBox(event_tab);
        event_top_color->setObjectName(QString::fromUtf8("event_top_color"));

        horizontalLayout_7->addWidget(event_top_color);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        label_10 = new QLabel(event_tab);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_7->addWidget(label_10);

        event_desc_color = new QComboBox(event_tab);
        event_desc_color->setObjectName(QString::fromUtf8("event_desc_color"));

        horizontalLayout_7->addWidget(event_desc_color);


        verticalLayout_4->addLayout(horizontalLayout_7);

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

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
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

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_9);

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
        description_label = new QLabel(event_tab);
        description_label->setObjectName(QString::fromUtf8("description_label"));

        horizontalLayout->addWidget(description_label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        time_label_3 = new QLabel(event_tab);
        time_label_3->setObjectName(QString::fromUtf8("time_label_3"));

        horizontalLayout->addWidget(time_label_3);

        time_editbox_3 = new QTimeEdit(event_tab);
        time_editbox_3->setObjectName(QString::fromUtf8("time_editbox_3"));

        horizontalLayout->addWidget(time_editbox_3);


        verticalLayout_3->addLayout(horizontalLayout);

        description_editbox = new QTextEdit(event_tab);
        description_editbox->setObjectName(QString::fromUtf8("description_editbox"));
        description_editbox->setMaximumSize(QSize(16777215, 40));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Courier New"));
        font1.setPointSize(8);
        description_editbox->setFont(font1);
        description_editbox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        description_editbox->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        description_editbox->setLineWrapMode(QTextEdit::FixedColumnWidth);
        description_editbox->setLineWrapColumnOrWidth(64);
        description_editbox->setAcceptRichText(false);

        verticalLayout_3->addWidget(description_editbox);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        save_button = new QPushButton(event_tab);
        save_button->setObjectName(QString::fromUtf8("save_button"));

        horizontalLayout_3->addWidget(save_button);

        delete_button = new QPushButton(event_tab);
        delete_button->setObjectName(QString::fromUtf8("delete_button"));

        horizontalLayout_3->addWidget(delete_button);


        verticalLayout_3->addLayout(horizontalLayout_3);


        horizontalLayout_12->addLayout(verticalLayout_3);

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

        horizontalLayout_12->addWidget(date_widget);


        verticalLayout_4->addLayout(horizontalLayout_12);

        tabWidget->addTab(event_tab, QString());
        announcements_tab = new QWidget();
        announcements_tab->setObjectName(QString::fromUtf8("announcements_tab"));
        verticalLayout_5 = new QVBoxLayout(announcements_tab);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_12 = new QLabel(announcements_tab);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_13->addWidget(label_12);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_11);

        label_14 = new QLabel(announcements_tab);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_13->addWidget(label_14);

        announcement_color = new QComboBox(announcements_tab);
        announcement_color->setObjectName(QString::fromUtf8("announcement_color"));

        horizontalLayout_13->addWidget(announcement_color);


        verticalLayout_5->addLayout(horizontalLayout_13);

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

        verticalLayout_5->addWidget(tableWidget_2);

        line_2 = new QFrame(announcements_tab);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line_2);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        announcement_label = new QLabel(announcements_tab);
        announcement_label->setObjectName(QString::fromUtf8("announcement_label"));

        horizontalLayout_10->addWidget(announcement_label);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_8);

        time_label_2 = new QLabel(announcements_tab);
        time_label_2->setObjectName(QString::fromUtf8("time_label_2"));

        horizontalLayout_10->addWidget(time_label_2);

        time_editbox_2 = new QTimeEdit(announcements_tab);
        time_editbox_2->setObjectName(QString::fromUtf8("time_editbox_2"));

        horizontalLayout_10->addWidget(time_editbox_2);


        verticalLayout_7->addLayout(horizontalLayout_10);

        announcement_editbox = new QTextEdit(announcements_tab);
        announcement_editbox->setObjectName(QString::fromUtf8("announcement_editbox"));
        announcement_editbox->setMaximumSize(QSize(16777215, 60));
        announcement_editbox->setFont(font1);
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


        horizontalLayout_11->addLayout(verticalLayout_7);

        date_widget_2 = new QCalendarWidget(announcements_tab);
        date_widget_2->setObjectName(QString::fromUtf8("date_widget_2"));
        sizePolicy.setHeightForWidth(date_widget_2->sizePolicy().hasHeightForWidth());
        date_widget_2->setSizePolicy(sizePolicy);
        date_widget_2->setMaximumSize(QSize(190, 16777215));
        date_widget_2->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
        date_widget_2->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

        horizontalLayout_11->addWidget(date_widget_2);


        verticalLayout_5->addLayout(horizontalLayout_11);

        tabWidget->addTab(announcements_tab, QString());
        officeHours_tab = new QWidget();
        officeHours_tab->setObjectName(QString::fromUtf8("officeHours_tab"));
        verticalLayout_6 = new QVBoxLayout(officeHours_tab);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_13 = new QLabel(officeHours_tab);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_14->addWidget(label_13);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_12);

        label_15 = new QLabel(officeHours_tab);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_14->addWidget(label_15);

        officehours_top_color = new QComboBox(officeHours_tab);
        officehours_top_color->setObjectName(QString::fromUtf8("officehours_top_color"));

        horizontalLayout_14->addWidget(officehours_top_color);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_13);

        label_16 = new QLabel(officeHours_tab);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_14->addWidget(label_16);

        officehours_hours_color = new QComboBox(officeHours_tab);
        officehours_hours_color->setObjectName(QString::fromUtf8("officehours_hours_color"));

        horizontalLayout_14->addWidget(officehours_hours_color);


        verticalLayout_6->addLayout(horizontalLayout_14);

        tableWidget_3 = new QTableWidget(officeHours_tab);
        if (tableWidget_3->columnCount() < 1)
            tableWidget_3->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_3->setHorizontalHeaderItem(0, __qtablewidgetitem2);
        tableWidget_3->setObjectName(QString::fromUtf8("tableWidget_3"));
        tableWidget_3->setMaximumSize(QSize(16777215, 100));
        tableWidget_3->setColumnCount(1);
        tableWidget_3->horizontalHeader()->setVisible(false);
        tableWidget_3->horizontalHeader()->setStretchLastSection(true);
        tableWidget_3->verticalHeader()->setVisible(false);
        tableWidget_3->verticalHeader()->setDefaultSectionSize(20);

        verticalLayout_6->addWidget(tableWidget_3);

        line_3 = new QFrame(officeHours_tab);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_2 = new QLabel(officeHours_tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_6->addWidget(label_2);

        professor_editbox = new QLineEdit(officeHours_tab);
        professor_editbox->setObjectName(QString::fromUtf8("professor_editbox"));

        horizontalLayout_6->addWidget(professor_editbox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        label_4 = new QLabel(officeHours_tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_6->addWidget(label_4);

        office_editbox = new QLineEdit(officeHours_tab);
        office_editbox->setObjectName(QString::fromUtf8("office_editbox"));

        horizontalLayout_6->addWidget(office_editbox);


        verticalLayout_6->addLayout(horizontalLayout_6);

        label = new QLabel(officeHours_tab);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_6->addWidget(label);

        officeHours_editbox = new QTextEdit(officeHours_tab);
        officeHours_editbox->setObjectName(QString::fromUtf8("officeHours_editbox"));
        officeHours_editbox->setMaximumSize(QSize(16777215, 60));
        officeHours_editbox->setFont(font1);
        officeHours_editbox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        officeHours_editbox->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        officeHours_editbox->setLineWrapMode(QTextEdit::FixedColumnWidth);
        officeHours_editbox->setLineWrapColumnOrWidth(64);
        officeHours_editbox->setAcceptRichText(false);

        verticalLayout_6->addWidget(officeHours_editbox);

        verticalSpacer_4 = new QSpacerItem(20, 37, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        save_button_3 = new QPushButton(officeHours_tab);
        save_button_3->setObjectName(QString::fromUtf8("save_button_3"));

        horizontalLayout_5->addWidget(save_button_3);

        delete_button_3 = new QPushButton(officeHours_tab);
        delete_button_3->setObjectName(QString::fromUtf8("delete_button_3"));

        horizontalLayout_5->addWidget(delete_button_3);


        verticalLayout_6->addLayout(horizontalLayout_5);

        tabWidget->addTab(officeHours_tab, QString());

        verticalLayout_2->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "CPE Ticker Control Panel", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "CPE Ticker Control Panel", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Com Port:", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "Force Sync", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Display Status:", 0, QApplication::UnicodeUTF8));
        display_status_label->setText(QString());
        label_5->setText(QString());
        label_9->setText(QApplication::translate("MainWindow", "Made by B. Gomberg, D. Burke, D. Carteno, A. Zuffi, B. Tossoun for Capstone 2013", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(status_tab), QApplication::translate("MainWindow", "Status", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; text-decoration: underline;\">Current Events:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Title Line Color:", 0, QApplication::UnicodeUTF8));
        event_top_color->clear();
        event_top_color->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Green", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Blue", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Cyan", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Red", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Yellow", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Purple", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "White", 0, QApplication::UnicodeUTF8)
        );
        label_10->setText(QApplication::translate("MainWindow", "Description Line Color:", 0, QApplication::UnicodeUTF8));
        event_desc_color->clear();
        event_desc_color->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Green", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Blue", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Cyan", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Red", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Yellow", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Purple", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "White", 0, QApplication::UnicodeUTF8)
        );
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Event Title", 0, QApplication::UnicodeUTF8));
        title_label->setText(QApplication::translate("MainWindow", "Title", 0, QApplication::UnicodeUTF8));
        location_label->setText(QApplication::translate("MainWindow", "Location", 0, QApplication::UnicodeUTF8));
        time_label->setText(QApplication::translate("MainWindow", "Start Time", 0, QApplication::UnicodeUTF8));
        time_editbox->setDisplayFormat(QApplication::translate("MainWindow", "h:mm AP", 0, QApplication::UnicodeUTF8));
        description_label->setText(QApplication::translate("MainWindow", "Description (2 lines)", 0, QApplication::UnicodeUTF8));
        time_label_3->setText(QApplication::translate("MainWindow", "End Time", 0, QApplication::UnicodeUTF8));
        time_editbox_3->setDisplayFormat(QApplication::translate("MainWindow", "h:mm AP", 0, QApplication::UnicodeUTF8));
        save_button->setText(QApplication::translate("MainWindow", "Save Event", 0, QApplication::UnicodeUTF8));
        delete_button->setText(QApplication::translate("MainWindow", "Delete Event", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(event_tab), QApplication::translate("MainWindow", "Events", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "Current Announcements:", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "Text Color", 0, QApplication::UnicodeUTF8));
        announcement_color->clear();
        announcement_color->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Green", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Blue", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Cyan", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Red", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Yellow", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Purple", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "White", 0, QApplication::UnicodeUTF8)
        );
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Event Title", 0, QApplication::UnicodeUTF8));
        announcement_label->setText(QApplication::translate("MainWindow", "Annoumcent (3 lines max)", 0, QApplication::UnicodeUTF8));
        time_label_2->setText(QApplication::translate("MainWindow", "Display until:", 0, QApplication::UnicodeUTF8));
        time_editbox_2->setDisplayFormat(QApplication::translate("MainWindow", "h:mm AP", 0, QApplication::UnicodeUTF8));
        save_button_2->setText(QApplication::translate("MainWindow", "Save Announcement", 0, QApplication::UnicodeUTF8));
        delete_button_2->setText(QApplication::translate("MainWindow", "Delete Announcement", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(announcements_tab), QApplication::translate("MainWindow", "Announcements", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "Current Office Hours:", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "Name/Location Color", 0, QApplication::UnicodeUTF8));
        officehours_top_color->clear();
        officehours_top_color->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Green", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Blue", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Cyan", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Red", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Yellow", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Purple", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "White", 0, QApplication::UnicodeUTF8)
        );
        label_16->setText(QApplication::translate("MainWindow", "Hours Color", 0, QApplication::UnicodeUTF8));
        officehours_hours_color->clear();
        officehours_hours_color->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Green", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Blue", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Cyan", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Red", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Yellow", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Purple", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "White", 0, QApplication::UnicodeUTF8)
        );
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_3->horizontalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "Event Title", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Professor Name:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Office Location:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Office Hours (2 lines max)", 0, QApplication::UnicodeUTF8));
        save_button_3->setText(QApplication::translate("MainWindow", "Save Professor", 0, QApplication::UnicodeUTF8));
        delete_button_3->setText(QApplication::translate("MainWindow", "Delete Professor", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(officeHours_tab), QApplication::translate("MainWindow", "Office Hours", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
