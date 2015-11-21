/********************************************************************************
** Form generated from reading ui file 'cantidad.ui'
**
** Created: Thu Jul 9 09:33:21 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CANTIDAD_H
#define UI_CANTIDAD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_cantidad
{
public:
    QDialogButtonBox *buttonBox;
    QSpinBox *spinBox;
    QLabel *label;

    void setupUi(QDialog *cantidad)
    {
        if (cantidad->objectName().isEmpty())
            cantidad->setObjectName(QString::fromUtf8("cantidad"));
        cantidad->resize(318, 243);
        buttonBox = new QDialogButtonBox(cantidad);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 170, 301, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        spinBox = new QSpinBox(cantidad);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(170, 70, 91, 25));
        label = new QLabel(cantidad);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 80, 161, 18));

        retranslateUi(cantidad);
        QObject::connect(buttonBox, SIGNAL(accepted()), cantidad, SLOT(comFather()));
        QObject::connect(buttonBox, SIGNAL(accepted()), cantidad, SLOT(close()));

        QMetaObject::connectSlotsByName(cantidad);
    } // setupUi

    void retranslateUi(QDialog *cantidad)
    {
        cantidad->setWindowTitle(QApplication::translate("cantidad", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("cantidad", "Cantidad del Producto:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(cantidad);
    } // retranslateUi

};

namespace Ui {
    class cantidad: public Ui_cantidad {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CANTIDAD_H
