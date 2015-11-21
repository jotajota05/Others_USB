/********************************************************************************
** Form generated from reading ui file 'tilda.ui'
**
** Created: Thu Jul 9 09:33:21 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TILDA_H
#define UI_TILDA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tilda
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QLabel *label;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;

    void setupUi(QMainWindow *Tilda)
    {
        if (Tilda->objectName().isEmpty())
            Tilda->setObjectName(QString::fromUtf8("Tilda"));
        Tilda->resize(592, 330);
        centralwidget = new QWidget(Tilda);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(320, 290, 85, 29));
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/view-list-text.png")), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon);
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(500, 290, 85, 29));
        QIcon icon1;
        icon1.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/dialog-close.png")), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon1);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(410, 290, 85, 29));
        QIcon icon2;
        icon2.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/dialog-ok-apply.png")), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon2);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(430, 260, 59, 21));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 20, 561, 231));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(490, 260, 59, 18));
        Tilda->setCentralWidget(centralwidget);

        retranslateUi(Tilda);
        QObject::connect(pushButton_3, SIGNAL(clicked()), Tilda, SLOT(close()));
        QObject::connect(pushButton, SIGNAL(clicked()), Tilda, SLOT(close()));

        QMetaObject::connectSlotsByName(Tilda);
    } // setupUi

    void retranslateUi(QMainWindow *Tilda)
    {
        Tilda->setWindowTitle(QApplication::translate("Tilda", "Factura de mesa", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_2->setToolTip(QApplication::translate("Tilda", "Facturar e imprimir cuenta", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_2->setText(QApplication::translate("Tilda", "Imprimir", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_3->setToolTip(QApplication::translate("Tilda", "Salir de esta ventana", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_3->setText(QApplication::translate("Tilda", "Cancelar", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton->setToolTip(QApplication::translate("Tilda", "Aceptar condici\303\263n de la cuenta", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton->setText(QApplication::translate("Tilda", "OK", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QApplication::translate("Tilda", "Total a pagar", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("Tilda", "TOTAL Bs:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
        Q_UNUSED(Tilda);
    } // retranslateUi

};

namespace Ui {
    class Tilda: public Ui_Tilda {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TILDA_H
