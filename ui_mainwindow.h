/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QComboBox *comboBox_2;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit_4;
    QLabel *label_7;
    QSpacerItem *horizontalSpacer;
    QLabel *label_6;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_5;
    QLabel *label_9;
    QLineEdit *lineEdit_3;
    QLabel *label_10;
    QLineEdit *lineEdit;
    QLabel *label_8;
    QLabel *label;
    QLabel *label_5;
    QLabel *label_2;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(622, 329);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 1, 1, 1, 1);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setMaximumSize(QSize(150, 16777215));
        QFont font;
        font.setPointSize(15);
        pushButton_2->setFont(font);

        gridLayout_3->addWidget(pushButton_2, 2, 1, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font1;
        font1.setPointSize(9);
        label_3->setFont(font1);

        horizontalLayout_5->addWidget(label_3);

        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QFont font2;
        font2.setPointSize(13);
        comboBox->setFont(font2);
        comboBox->setEditable(false);
        comboBox->setMinimumContentsLength(3);

        horizontalLayout_5->addWidget(comboBox);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font2);

        horizontalLayout_6->addWidget(label_4);

        comboBox_2 = new QComboBox(centralwidget);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setFont(font2);

        horizontalLayout_6->addWidget(comboBox_2);


        verticalLayout_2->addLayout(horizontalLayout_6);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lineEdit_4 = new QLineEdit(centralwidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy1);
        lineEdit_4->setMaximumSize(QSize(45, 16777215));
        QFont font3;
        font3.setPointSize(12);
        lineEdit_4->setFont(font3);

        gridLayout_2->addWidget(lineEdit_4, 3, 3, 1, 1);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 2, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 1, 0, 1, 1);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 1, 4, 1, 1);

        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setEnabled(true);
        sizePolicy1.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy1);
        lineEdit_2->setMinimumSize(QSize(22, 0));
        lineEdit_2->setMaximumSize(QSize(45, 16777215));
        lineEdit_2->setFont(font3);

        gridLayout_2->addWidget(lineEdit_2, 1, 3, 1, 1);

        lineEdit_5 = new QLineEdit(centralwidget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        sizePolicy1.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy1);
        lineEdit_5->setMaximumSize(QSize(45, 16777215));
        lineEdit_5->setFont(font3);

        gridLayout_2->addWidget(lineEdit_5, 4, 3, 1, 1);

        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 2, 4, 1, 1);

        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        sizePolicy1.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy1);
        lineEdit_3->setMaximumSize(QSize(45, 16777215));
        lineEdit_3->setFont(font3);

        gridLayout_2->addWidget(lineEdit_3, 2, 3, 1, 1);

        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 3, 4, 1, 1);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);
        lineEdit->setMaximumSize(QSize(45, 16777215));
        lineEdit->setFont(font3);

        gridLayout_2->addWidget(lineEdit, 1, 2, 1, 1);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QFont font4;
        font4.setPointSize(13);
        font4.setBold(false);
        font4.setWeight(50);
        label_8->setFont(font4);
        label_8->setMouseTracking(true);

        gridLayout_2->addWidget(label_8, 3, 1, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMouseTracking(true);

        gridLayout_2->addWidget(label, 4, 1, 1, 1);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 1, 1, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 4, 4, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);


        horizontalLayout_7->addLayout(verticalLayout_2);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy2);
        pushButton->setFont(font2);

        horizontalLayout_7->addWidget(pushButton);


        gridLayout_3->addLayout(horizontalLayout_7, 0, 0, 1, 3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 622, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        comboBox_2->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\207\320\265\321\202-\320\276\321\202\321\207\320\265\321\202", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:13pt;\">\320\242\320\270\320\277 \320\267\320\276\320\275\320\264\320\260</span></p></body></html>", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "I - \320\267\320\276\320\275\320\264 \321\201 \320\275\320\260\320\272\320\276\320\275\320\265\321\207\320\275\320\270\320\272\320\276\320\274 \320\270\320\267 \320\272\320\276\320\275\321\203\321\201\320\260 \320\270 \320\272\320\276\320\266\321\203\321\205\320\260", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "II - \320\267\320\276\320\275\320\264 \321\201 \320\275\320\260\320\272\320\276\320\275\320\265\321\207\320\275\320\270\320\272\320\276\320\274 \320\270\320\267 \320\272\320\276\320\275\321\203\321\201\320\260 \320\274\321\203\321\204\321\202\321\213 \321\202\321\200\320\265\320\275\320\270\321\217", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "III - \320\267\320\276\320\275\320\264 \321\201 \320\275\320\260\320\272\320\276\320\275\320\265\321\207\320\275\320\270\320\272\320\276\320\274 \320\270\320\267 \320\272\320\276\320\275\321\203\321\201\320\260 \320\274\321\203\321\204\321\202\321\213 \321\202\321\200\320\265\320\275\320\270\321\217 \320\270 \321\203\321\210\320\270\321\200\320\270\321\202\320\265\320\273\321\217", nullptr));

        comboBox->setCurrentText(QCoreApplication::translate("MainWindow", "I - \320\267\320\276\320\275\320\264 \321\201 \320\275\320\260\320\272\320\276\320\275\320\265\321\207\320\275\320\270\320\272\320\276\320\274 \320\270\320\267 \320\272\320\276\320\275\321\203\321\201\320\260 \320\270 \320\272\320\276\320\266\321\203\321\205\320\260", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600;\">\320\232\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202 \321\203\321\201\320\273\320\276\320\262\320\270\320\271 \321\200\320\260\320\261\320\276\321\202\321\213 \321\201\320\262\320\260\320\270 \320\262 \320\263\321\200\321\203\320\275\321\202\320\265 </span><span style=\" font-family:'Times New Roman','serif'; font-weight:600;\">\316\263</span><span style=\" font-family:'Times New Roman','serif'; font-weight:600; vertical-align:sub;\">c</span></p></body></html>", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "0.6", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("MainWindow", "0.8", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("MainWindow", "0.9", nullptr));
        comboBox_2->setItemText(3, QCoreApplication::translate("MainWindow", "1.0", nullptr));
        comboBox_2->setItemText(4, QCoreApplication::translate("MainWindow", "1.15", nullptr));
        comboBox_2->setItemText(5, QCoreApplication::translate("MainWindow", "1.2", nullptr));
        comboBox_2->setItemText(6, QCoreApplication::translate("MainWindow", "1.5", nullptr));

        label_7->setText(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'.SF NS Text'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\223\320\273\321\203\320\261\320\270\320\275\320\260 \320\262\320\265\321\200\321\205\320\260 \321\201\320\262\320\260\320\270</p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">\320\274\320\274</span></p></body></html>", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">\320\274</span></p></body></html>", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">\320\274</span></p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:12pt;\">\320\223\320\273\321\203\320\261\320\270\320\275\320\260 \320\275\320\270\320\267\320\260 \321\201\320\262\320\260\320\270</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">\320\224\320\273\320\270\320\275\320\260 \320\275\320\260\320\272\320\276\320\275\320\265\321\207\320\275\320\270\320\272\320\260</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'.SF NS Text'; font-size:13pt;\">\320\241\320\265\321\207\320\275\320\270\320\265 \320\275\320\260\321\202\321\203\321\200\320\275\320\276\320\271 \321\201\320\262\320\260\320\270</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">\320\274\320\274</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\320\276\321\200 \321\204\320\260\320\271\320\273\320\260 \n"
"Excel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
