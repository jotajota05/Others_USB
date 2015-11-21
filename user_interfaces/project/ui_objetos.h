/********************************************************************************
** Form generated from reading ui file 'objetos.ui'
**
** Created: Thu Jul 9 09:33:21 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_OBJETOS_H
#define UI_OBJETOS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Objetos
{
public:
    QGridLayout *gridLayout_2;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *Objetos)
    {
        if (Objetos->objectName().isEmpty())
            Objetos->setObjectName(QString::fromUtf8("Objetos"));
        Objetos->resize(200, 376);
        gridLayout_2 = new QGridLayout(Objetos);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        treeWidget = new QTreeWidget(Objetos);
        QFont font;
        font.setPointSize(18);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setTextAlignment(0, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtreewidgetitem->setFont(0, font);
        treeWidget->setHeaderItem(__qtreewidgetitem);
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/mesa.gif")), QIcon::Normal, QIcon::Off);
        QFont font1;
        font1.setPointSize(16);
        QIcon icon1;
        icon1.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/bar.png")), QIcon::Normal, QIcon::Off);
        QIcon icon2;
        icon2.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/obstaculo.png")), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem1->setFont(0, font1);
        __qtreewidgetitem1->setIcon(0, icon);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem2->setFont(0, font1);
        __qtreewidgetitem2->setIcon(0, icon1);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem3->setFont(0, font1);
        __qtreewidgetitem3->setIcon(0, icon2);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setFrameShape(QFrame::VLine);
        treeWidget->setIconSize(QSize(32, 32));
        treeWidget->header()->setVisible(false);

        gridLayout_2->addWidget(treeWidget, 0, 0, 1, 1);


        retranslateUi(Objetos);
        QObject::connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), Objetos, SLOT(newObs(QTreeWidgetItem*,int)));

        QMetaObject::connectSlotsByName(Objetos);
    } // setupUi

    void retranslateUi(QWidget *Objetos)
    {
        Objetos->setWindowTitle(QApplication::translate("Objetos", "Form", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("Objetos", "Objetos", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("Objetos", "Mesas", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("Objetos", "Redondas", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("Objetos", "Cuadradas", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem4 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem4->setText(0, QApplication::translate("Objetos", "Bares", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem4->child(0);
        ___qtreewidgetitem5->setText(0, QApplication::translate("Objetos", "Redondos", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem4->child(1);
        ___qtreewidgetitem6->setText(0, QApplication::translate("Objetos", "Cuadrados", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem4->child(2);
        ___qtreewidgetitem7->setText(0, QApplication::translate("Objetos", "Arcos", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem8 = treeWidget->topLevelItem(2);
        ___qtreewidgetitem8->setText(0, QApplication::translate("Objetos", "Obstaculos", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem8->child(0);
        ___qtreewidgetitem9->setText(0, QApplication::translate("Objetos", "Columnas", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem8->child(1);
        ___qtreewidgetitem10->setText(0, QApplication::translate("Objetos", "Muros", 0, QApplication::UnicodeUTF8));
        treeWidget->setSortingEnabled(__sortingEnabled);

        Q_UNUSED(Objetos);
    } // retranslateUi

};

namespace Ui {
    class Objetos: public Ui_Objetos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJETOS_H
