/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *leftPanel;
    QVBoxLayout *verticalLayout_2;
    QComboBox *driveComboLeft;
    QTreeView *leftView;
    QVBoxLayout *verticalLayout_3;
    QPushButton *copyButton;
    QPushButton *moveButton;
    QPushButton *deleteButton;
    QPushButton *newFolderButton;
    QPushButton *renameButton;
    QPushButton *uploadButton;
    QPushButton *downloadButton;
    QSpacerItem *verticalSpacer;
    QGroupBox *rightPanel;
    QVBoxLayout *verticalLayout_4;
    QComboBox *driveComboRight;
    QTreeView *rightView;
    QGroupBox *networkGroup;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *serverAddressEdit;
    QLabel *label_2;
    QLineEdit *serverPortEdit;
    QPushButton *connectButton;
    QPushButton *startServerButton;
    QPushButton *transferFileButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        leftPanel = new QGroupBox(centralwidget);
        leftPanel->setObjectName("leftPanel");
        verticalLayout_2 = new QVBoxLayout(leftPanel);
        verticalLayout_2->setObjectName("verticalLayout_2");
        driveComboLeft = new QComboBox(leftPanel);
        driveComboLeft->setObjectName("driveComboLeft");

        verticalLayout_2->addWidget(driveComboLeft);

        leftView = new QTreeView(leftPanel);
        leftView->setObjectName("leftView");
        leftView->setSelectionMode(QAbstractItemView::SingleSelection);
        leftView->setUniformRowHeights(true);

        verticalLayout_2->addWidget(leftView);


        horizontalLayout->addWidget(leftPanel);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        copyButton = new QPushButton(centralwidget);
        copyButton->setObjectName("copyButton");

        verticalLayout_3->addWidget(copyButton);

        moveButton = new QPushButton(centralwidget);
        moveButton->setObjectName("moveButton");

        verticalLayout_3->addWidget(moveButton);

        deleteButton = new QPushButton(centralwidget);
        deleteButton->setObjectName("deleteButton");

        verticalLayout_3->addWidget(deleteButton);

        newFolderButton = new QPushButton(centralwidget);
        newFolderButton->setObjectName("newFolderButton");

        verticalLayout_3->addWidget(newFolderButton);

        renameButton = new QPushButton(centralwidget);
        renameButton->setObjectName("renameButton");

        verticalLayout_3->addWidget(renameButton);

        uploadButton = new QPushButton(centralwidget);
        uploadButton->setObjectName("uploadButton");

        verticalLayout_3->addWidget(uploadButton);

        downloadButton = new QPushButton(centralwidget);
        downloadButton->setObjectName("downloadButton");

        verticalLayout_3->addWidget(downloadButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_3);

        rightPanel = new QGroupBox(centralwidget);
        rightPanel->setObjectName("rightPanel");
        verticalLayout_4 = new QVBoxLayout(rightPanel);
        verticalLayout_4->setObjectName("verticalLayout_4");
        driveComboRight = new QComboBox(rightPanel);
        driveComboRight->setObjectName("driveComboRight");

        verticalLayout_4->addWidget(driveComboRight);

        rightView = new QTreeView(rightPanel);
        rightView->setObjectName("rightView");
        rightView->setSelectionMode(QAbstractItemView::SingleSelection);
        rightView->setUniformRowHeights(true);

        verticalLayout_4->addWidget(rightView);


        horizontalLayout->addWidget(rightPanel);


        verticalLayout->addLayout(horizontalLayout);

        networkGroup = new QGroupBox(centralwidget);
        networkGroup->setObjectName("networkGroup");
        horizontalLayout_2 = new QHBoxLayout(networkGroup);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(networkGroup);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        serverAddressEdit = new QLineEdit(networkGroup);
        serverAddressEdit->setObjectName("serverAddressEdit");

        horizontalLayout_2->addWidget(serverAddressEdit);

        label_2 = new QLabel(networkGroup);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        serverPortEdit = new QLineEdit(networkGroup);
        serverPortEdit->setObjectName("serverPortEdit");

        horizontalLayout_2->addWidget(serverPortEdit);

        connectButton = new QPushButton(networkGroup);
        connectButton->setObjectName("connectButton");

        horizontalLayout_2->addWidget(connectButton);

        startServerButton = new QPushButton(networkGroup);
        startServerButton->setObjectName("startServerButton");

        horizontalLayout_2->addWidget(startServerButton);

        transferFileButton = new QPushButton(networkGroup);
        transferFileButton->setObjectName("transferFileButton");

        horizontalLayout_2->addWidget(transferFileButton);


        verticalLayout->addWidget(networkGroup);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "File Commander", nullptr));
        leftPanel->setTitle(QCoreApplication::translate("MainWindow", "Local Drive", nullptr));
        copyButton->setText(QCoreApplication::translate("MainWindow", "Copy \342\206\222", nullptr));
        moveButton->setText(QCoreApplication::translate("MainWindow", "Move \342\206\222", nullptr));
        deleteButton->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        newFolderButton->setText(QCoreApplication::translate("MainWindow", "New Folder", nullptr));
        renameButton->setText(QCoreApplication::translate("MainWindow", "Rename", nullptr));
        uploadButton->setText(QCoreApplication::translate("MainWindow", "Upload", nullptr));
        downloadButton->setText(QCoreApplication::translate("MainWindow", "Download", nullptr));
        rightPanel->setTitle(QCoreApplication::translate("MainWindow", "Remote/Other Drive", nullptr));
        networkGroup->setTitle(QCoreApplication::translate("MainWindow", "Network Transfer", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Server Address:", nullptr));
        serverAddressEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        serverPortEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "12345", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        startServerButton->setText(QCoreApplication::translate("MainWindow", "Start Server", nullptr));
        transferFileButton->setText(QCoreApplication::translate("MainWindow", "Transfer File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
