/********************************************************************************
** Form generated from reading UI file 'cg_window.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CG_WINDOW_H
#define UI_CG_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "cg_Canvas.h"

QT_BEGIN_NAMESPACE

class Ui_CG_Window
{
public:
    QWidget *centralwidget;
    QVBoxLayout *vboxLayout;
    QFrame *frame_buttons;
    QHBoxLayout *hboxLayout;
    QPushButton *pushButton_Render;
    QPushButton *pushButton_Mode;
    QSpacerItem *spacerItem;
    QWidget *widget;
    QPushButton *pushButton_Save;
    cg_Canvas *drawCanvas;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CG_Window)
    {
        if (CG_Window->objectName().isEmpty())
            CG_Window->setObjectName(QStringLiteral("CG_Window"));
        CG_Window->resize(480, 480);
        centralwidget = new QWidget(CG_Window);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        vboxLayout = new QVBoxLayout(centralwidget);
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        frame_buttons = new QFrame(centralwidget);
        frame_buttons->setObjectName(QStringLiteral("frame_buttons"));
        frame_buttons->setFrameShape(QFrame::StyledPanel);
        frame_buttons->setFrameShadow(QFrame::Raised);
        hboxLayout = new QHBoxLayout(frame_buttons);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        pushButton_Render = new QPushButton(frame_buttons);
        pushButton_Render->setObjectName(QStringLiteral("pushButton_Render"));

        hboxLayout->addWidget(pushButton_Render);

        pushButton_Mode = new QPushButton(frame_buttons);
        pushButton_Mode->setObjectName(QStringLiteral("pushButton_Mode"));

        hboxLayout->addWidget(pushButton_Mode);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        widget = new QWidget(frame_buttons);
        widget->setObjectName(QStringLiteral("widget"));

        hboxLayout->addWidget(widget);

        pushButton_Save = new QPushButton(frame_buttons);
        pushButton_Save->setObjectName(QStringLiteral("pushButton_Save"));

        hboxLayout->addWidget(pushButton_Save);


        vboxLayout->addWidget(frame_buttons);

        drawCanvas = new cg_Canvas(centralwidget);
        drawCanvas->setObjectName(QStringLiteral("drawCanvas"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(drawCanvas->sizePolicy().hasHeightForWidth());
        drawCanvas->setSizePolicy(sizePolicy);

        vboxLayout->addWidget(drawCanvas);

        CG_Window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CG_Window);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 480, 21));
        CG_Window->setMenuBar(menubar);
        statusbar = new QStatusBar(CG_Window);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        CG_Window->setStatusBar(statusbar);

        retranslateUi(CG_Window);

        QMetaObject::connectSlotsByName(CG_Window);
    } // setupUi

    void retranslateUi(QMainWindow *CG_Window)
    {
        CG_Window->setWindowTitle(QApplication::translate("CG_Window", "Computer Graphics", 0));
        pushButton_Render->setText(QApplication::translate("CG_Window", "Trace scene", 0));
        pushButton_Mode->setText(QApplication::translate("CG_Window", " 1 sample / pixel ", 0));
        pushButton_Save->setText(QApplication::translate("CG_Window", "save image", 0));
    } // retranslateUi

};

namespace Ui {
    class CG_Window: public Ui_CG_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CG_WINDOW_H
