/********************************************************************************
** Form generated from reading ui file 'abrir.ui'
**
** Created: Thu Jul 9 09:33:21 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ABRIR_H
#define UI_ABRIR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Abrir
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLabel *label;

    void setupUi(QDialog *Abrir)
    {
        if (Abrir->objectName().isEmpty())
            Abrir->setObjectName(QString::fromUtf8("Abrir"));
        Abrir->resize(394, 141);
        buttonBox = new QDialogButtonBox(Abrir);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(20, 90, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Open);
        lineEdit = new QLineEdit(Abrir);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(30, 40, 271, 31));
        pushButton = new QPushButton(Abrir);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(300, 40, 85, 29));
        label = new QLabel(Abrir);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 110, 59, 18));

        retranslateUi(Abrir);
        QObject::connect(buttonBox, SIGNAL(accepted()), Abrir, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Abrir, SLOT(reject()));

        QMetaObject::connectSlotsByName(Abrir);
    } // setupUi

    void retranslateUi(QDialog *Abrir)
    {
        Abrir->setWindowTitle(QApplication::translate("Abrir", "Abrir", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("Abrir", "Examinar", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Abrir", "TextLabel", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Abrir);
    } // retranslateUi

};

namespace Ui {
    class Abrir: public Ui_Abrir {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABRIR_H
