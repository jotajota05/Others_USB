/********************************************************************************
** Form generated from reading ui file 'productos.ui'
**
** Created: Thu Jul 9 09:33:21 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PRODUCTOS_H
#define UI_PRODUCTOS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Productos
{
public:
    QGridLayout *gridLayout_2;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *Productos)
    {
        if (Productos->objectName().isEmpty())
            Productos->setObjectName(QString::fromUtf8("Productos"));
        Productos->resize(213, 375);
        gridLayout_2 = new QGridLayout(Productos);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        treeWidget = new QTreeWidget(Productos);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        QFont font;
        font.setPointSize(18);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setTextAlignment(0, Qt::AlignHCenter|Qt::AlignVCenter|Qt::AlignCenter);
        __qtreewidgetitem->setFont(0, font);
        __qtreewidgetitem->setBackground(0, QColor(223, 223, 223));
        __qtreewidgetitem->setForeground(0, brush);
        treeWidget->setHeaderItem(__qtreewidgetitem);
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/arepa.png")), QIcon::Normal, QIcon::Off);
        QFont font1;
        font1.setPointSize(16);
        QIcon icon1;
        icon1.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/empanadas3.jpg")), QIcon::Normal, QIcon::Off);
        QIcon icon2;
        icon2.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/sandwich.png")), QIcon::Normal, QIcon::Off);
        QIcon icon3;
        icon3.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/refrescos.png")), QIcon::Normal, QIcon::Off);
        QIcon icon4;
        icon4.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/jugos.png")), QIcon::Normal, QIcon::Off);
        QIcon icon5;
        icon5.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/cafes.png")), QIcon::Normal, QIcon::Off);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem1->setFont(0, font1);
        __qtreewidgetitem1->setIcon(0, icon);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem2->setFont(0, font1);
        __qtreewidgetitem2->setIcon(0, icon1);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem3->setFont(0, font1);
        __qtreewidgetitem3->setIcon(0, icon2);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem4->setFont(0, font1);
        __qtreewidgetitem4->setIcon(0, icon3);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem5->setFont(0, font1);
        __qtreewidgetitem5->setIcon(0, icon4);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem5);
        QTreeWidgetItem *__qtreewidgetitem6 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem6->setFont(0, font1);
        __qtreewidgetitem6->setIcon(0, icon5);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setFrameShape(QFrame::NoFrame);
        treeWidget->setAutoScrollMargin(16);
        treeWidget->setIconSize(QSize(32, 32));
        treeWidget->setIndentation(15);
        treeWidget->header()->setVisible(false);
        treeWidget->header()->setCascadingSectionResizes(false);

        gridLayout_2->addWidget(treeWidget, 0, 0, 1, 1);


        retranslateUi(Productos);
        QObject::connect(treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)), Productos, SLOT(cantidadDialog(QTreeWidgetItem*,int)));

        QMetaObject::connectSlotsByName(Productos);
    } // setupUi

    void retranslateUi(QWidget *Productos)
    {
        Productos->setWindowTitle(QApplication::translate("Productos", "Form", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("Productos", "Productos", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("Productos", "Arepas", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("Productos", "Arepa de Chicharron", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("Productos", "Arepa de Queso Amarillo", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem1->child(2);
        ___qtreewidgetitem4->setText(0, QApplication::translate("Productos", "Arepa de Queso Guayanes", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem1->child(3);
        ___qtreewidgetitem5->setText(0, QApplication::translate("Productos", "Arepa de Carne Mechada", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem1->child(4);
        ___qtreewidgetitem6->setText(0, QApplication::translate("Productos", "Arepa Pelua", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem1->child(5);
        ___qtreewidgetitem7->setText(0, QApplication::translate("Productos", "Arepa Reina Pepeada", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem8 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem8->setText(0, QApplication::translate("Productos", "Empanadas", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem8->child(0);
        ___qtreewidgetitem9->setText(0, QApplication::translate("Productos", "Empanada de Queso", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem8->child(1);
        ___qtreewidgetitem10->setText(0, QApplication::translate("Productos", "Empanada de Carne Mechada", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem8->child(2);
        ___qtreewidgetitem11->setText(0, QApplication::translate("Productos", "Empana de Carne Molida", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem12 = ___qtreewidgetitem8->child(3);
        ___qtreewidgetitem12->setText(0, QApplication::translate("Productos", "Empanada Domino", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem13 = ___qtreewidgetitem8->child(4);
        ___qtreewidgetitem13->setText(0, QApplication::translate("Productos", "Empanada de Pollo", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem14 = treeWidget->topLevelItem(2);
        ___qtreewidgetitem14->setText(0, QApplication::translate("Productos", "Sandwich", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem15 = ___qtreewidgetitem14->child(0);
        ___qtreewidgetitem15->setText(0, QApplication::translate("Productos", "Sandwich de Jamon y Queso", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem16 = ___qtreewidgetitem14->child(1);
        ___qtreewidgetitem16->setText(0, QApplication::translate("Productos", "Sandwich de Atun", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem17 = ___qtreewidgetitem14->child(2);
        ___qtreewidgetitem17->setText(0, QApplication::translate("Productos", "Club House", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem18 = treeWidget->topLevelItem(3);
        ___qtreewidgetitem18->setText(0, QApplication::translate("Productos", "Refrescos", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem19 = ___qtreewidgetitem18->child(0);
        ___qtreewidgetitem19->setText(0, QApplication::translate("Productos", "Pepsi", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem20 = ___qtreewidgetitem18->child(1);
        ___qtreewidgetitem20->setText(0, QApplication::translate("Productos", "Coca-Cola", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem21 = ___qtreewidgetitem18->child(2);
        ___qtreewidgetitem21->setText(0, QApplication::translate("Productos", "Frescolita", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem22 = ___qtreewidgetitem18->child(3);
        ___qtreewidgetitem22->setText(0, QApplication::translate("Productos", "7up", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem23 = ___qtreewidgetitem18->child(4);
        ___qtreewidgetitem23->setText(0, QApplication::translate("Productos", "Coca-Cola Zero", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem24 = treeWidget->topLevelItem(4);
        ___qtreewidgetitem24->setText(0, QApplication::translate("Productos", "Jugos", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem25 = ___qtreewidgetitem24->child(0);
        ___qtreewidgetitem25->setText(0, QApplication::translate("Productos", "Naranja", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem26 = ___qtreewidgetitem24->child(1);
        ___qtreewidgetitem26->setText(0, QApplication::translate("Productos", "Melon", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem27 = ___qtreewidgetitem24->child(2);
        ___qtreewidgetitem27->setText(0, QApplication::translate("Productos", "Lechoza", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem28 = ___qtreewidgetitem24->child(3);
        ___qtreewidgetitem28->setText(0, QApplication::translate("Productos", "Fresa", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem29 = ___qtreewidgetitem24->child(4);
        ___qtreewidgetitem29->setText(0, QApplication::translate("Productos", "Durazno", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem30 = treeWidget->topLevelItem(5);
        ___qtreewidgetitem30->setText(0, QApplication::translate("Productos", "Cafe", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem31 = ___qtreewidgetitem30->child(0);
        ___qtreewidgetitem31->setText(0, QApplication::translate("Productos", "Negro", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem32 = ___qtreewidgetitem30->child(1);
        ___qtreewidgetitem32->setText(0, QApplication::translate("Productos", "Marron", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem33 = ___qtreewidgetitem30->child(2);
        ___qtreewidgetitem33->setText(0, QApplication::translate("Productos", "Marron Oscuro", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem34 = ___qtreewidgetitem30->child(3);
        ___qtreewidgetitem34->setText(0, QApplication::translate("Productos", "Con Leche", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem35 = ___qtreewidgetitem30->child(4);
        ___qtreewidgetitem35->setText(0, QApplication::translate("Productos", "Guayoyo", 0, QApplication::UnicodeUTF8));
        treeWidget->setSortingEnabled(__sortingEnabled);

        Q_UNUSED(Productos);
    } // retranslateUi

};

namespace Ui {
    class Productos: public Ui_Productos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCTOS_H
