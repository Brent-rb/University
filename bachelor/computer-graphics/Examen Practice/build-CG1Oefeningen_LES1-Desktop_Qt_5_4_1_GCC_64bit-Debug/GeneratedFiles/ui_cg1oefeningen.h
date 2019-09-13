/********************************************************************************
** Form generated from reading UI file 'cg1oefeningen.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CG1OEFENINGEN_H
#define UI_CG1OEFENINGEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CG1OefeningenClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CG1OefeningenClass)
    {
        if (CG1OefeningenClass->objectName().isEmpty())
            CG1OefeningenClass->setObjectName(QStringLiteral("CG1OefeningenClass"));
        CG1OefeningenClass->setObjectName("CG1OefeningenClass");
        CG1OefeningenClass->resize(600, 400);
        menuBar = new QMenuBar(CG1OefeningenClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CG1OefeningenClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CG1OefeningenClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CG1OefeningenClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CG1OefeningenClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CG1OefeningenClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CG1OefeningenClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CG1OefeningenClass->setStatusBar(statusBar);

        retranslateUi(CG1OefeningenClass);

        QMetaObject::connectSlotsByName(CG1OefeningenClass);
    } // setupUi

    void retranslateUi(QMainWindow *CG1OefeningenClass)
    {
        CG1OefeningenClass->setWindowTitle(QApplication::translate("CG1OefeningenClass", "CG1Oefeningen", 0));
    } // retranslateUi

};

namespace Ui {
    class CG1OefeningenClass: public Ui_CG1OefeningenClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CG1OEFENINGEN_H
