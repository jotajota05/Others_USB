/********************************************************************************
** Form generated from reading ui file 'tablero.ui'
**
** Created: Thu Jul 9 09:33:21 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TABLERO_H
#define UI_TABLERO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tablero
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QLabel *seleccion;

    void setupUi(QWidget *Tablero)
    {
        if (Tablero->objectName().isEmpty())
            Tablero->setObjectName(QString::fromUtf8("Tablero"));
        Tablero->resize(701, 621);
        Tablero->setAcceptDrops(true);
        gridLayout = new QGridLayout(Tablero);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frame = new QFrame(Tablero);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setAcceptDrops(true);
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(195, 195, 195);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        seleccion = new QLabel(frame);
        seleccion->setObjectName(QString::fromUtf8("seleccion"));
        seleccion->setGeometry(QRect(620, 10, 59, 18));

        gridLayout->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(Tablero);

        QMetaObject::connectSlotsByName(Tablero);
    } // setupUi

    void retranslateUi(QWidget *Tablero)
    {
        Tablero->setWindowTitle(QApplication::translate("Tablero", "Form", 0, QApplication::UnicodeUTF8));
        seleccion->setText(QString());
        Q_UNUSED(Tablero);
    } // retranslateUi

};

namespace Ui {
    class Tablero: public Ui_Tablero {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLERO_H
