/********************************************************************************
** Form generated from reading ui file 'arepera.ui'
**
** Created: Thu Jul 9 09:33:21 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_AREPERA_H
#define UI_AREPERA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Arepera
{
public:
    QAction *actionNuevo;
    QAction *actionAbrir;
    QAction *actionImprimir;
    QAction *actionGuardar;
    QAction *actionCopiar;
    QAction *actionCortar;
    QAction *actionPegar;
    QAction *actionRehacer;
    QAction *actionDeshacer;
    QAction *actionAyuda;
    QAction *actionAbrir_2;
    QAction *actionImprimir_2;
    QAction *actionCopiar_2;
    QAction *actionCortar_2;
    QAction *actionPegar_2;
    QAction *actionDeshacer_2;
    QAction *actionTemas_de_Ayuda;
    QAction *actionAcerca_de;
    QAction *actionRehacer_2;
    QAction *actionSalir;
    QAction *actionPapelera;
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *gridLayoutWidget_3;
    QGridLayout *layoutObjetos;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QWidget *tab_2;
    QWidget *gridLayoutWidget_2;
    QGridLayout *layoutProductos;
    QWidget *tablero;
    QMenuBar *menuBar;
    QMenu *menuArchivo;
    QMenu *menuEditar;
    QMenu *menuAyuda;
    QToolBar *mainToolBar;
    QStatusBar *mierda;

    void setupUi(QMainWindow *Arepera)
    {
        if (Arepera->objectName().isEmpty())
            Arepera->setObjectName(QString::fromUtf8("Arepera"));
        Arepera->resize(1009, 744);
        Arepera->setStyleSheet(QString::fromUtf8(""));
        actionNuevo = new QAction(Arepera);
        actionNuevo->setObjectName(QString::fromUtf8("actionNuevo"));
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/document-new.png")), QIcon::Normal, QIcon::Off);
        actionNuevo->setIcon(icon);
        actionAbrir = new QAction(Arepera);
        actionAbrir->setObjectName(QString::fromUtf8("actionAbrir"));
        QIcon icon1;
        icon1.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/document-open.png")), QIcon::Normal, QIcon::Off);
        actionAbrir->setIcon(icon1);
        actionImprimir = new QAction(Arepera);
        actionImprimir->setObjectName(QString::fromUtf8("actionImprimir"));
        QIcon icon2;
        icon2.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/document-print.png")), QIcon::Normal, QIcon::Off);
        actionImprimir->setIcon(icon2);
        actionGuardar = new QAction(Arepera);
        actionGuardar->setObjectName(QString::fromUtf8("actionGuardar"));
        QIcon icon3;
        icon3.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/document-save.png")), QIcon::Normal, QIcon::Off);
        actionGuardar->setIcon(icon3);
        actionCopiar = new QAction(Arepera);
        actionCopiar->setObjectName(QString::fromUtf8("actionCopiar"));
        QIcon icon4;
        icon4.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/edit-copy.png")), QIcon::Normal, QIcon::Off);
        actionCopiar->setIcon(icon4);
        actionCortar = new QAction(Arepera);
        actionCortar->setObjectName(QString::fromUtf8("actionCortar"));
        QIcon icon5;
        icon5.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/edit-cut.png")), QIcon::Normal, QIcon::Off);
        actionCortar->setIcon(icon5);
        actionPegar = new QAction(Arepera);
        actionPegar->setObjectName(QString::fromUtf8("actionPegar"));
        QIcon icon6;
        icon6.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/edit-paste.png")), QIcon::Normal, QIcon::Off);
        actionPegar->setIcon(icon6);
        actionRehacer = new QAction(Arepera);
        actionRehacer->setObjectName(QString::fromUtf8("actionRehacer"));
        QIcon icon7;
        icon7.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/edit-redo.png")), QIcon::Normal, QIcon::Off);
        actionRehacer->setIcon(icon7);
        actionDeshacer = new QAction(Arepera);
        actionDeshacer->setObjectName(QString::fromUtf8("actionDeshacer"));
        QIcon icon8;
        icon8.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/edit-undo.png")), QIcon::Normal, QIcon::Off);
        actionDeshacer->setIcon(icon8);
        actionAyuda = new QAction(Arepera);
        actionAyuda->setObjectName(QString::fromUtf8("actionAyuda"));
        QIcon icon9;
        icon9.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/help-about.png")), QIcon::Normal, QIcon::Off);
        actionAyuda->setIcon(icon9);
        actionAbrir_2 = new QAction(Arepera);
        actionAbrir_2->setObjectName(QString::fromUtf8("actionAbrir_2"));
        actionAbrir_2->setIcon(icon1);
        actionImprimir_2 = new QAction(Arepera);
        actionImprimir_2->setObjectName(QString::fromUtf8("actionImprimir_2"));
        actionImprimir_2->setIcon(icon2);
        actionCopiar_2 = new QAction(Arepera);
        actionCopiar_2->setObjectName(QString::fromUtf8("actionCopiar_2"));
        actionCopiar_2->setIcon(icon4);
        actionCortar_2 = new QAction(Arepera);
        actionCortar_2->setObjectName(QString::fromUtf8("actionCortar_2"));
        actionCortar_2->setIcon(icon5);
        actionPegar_2 = new QAction(Arepera);
        actionPegar_2->setObjectName(QString::fromUtf8("actionPegar_2"));
        actionPegar_2->setIcon(icon6);
        actionDeshacer_2 = new QAction(Arepera);
        actionDeshacer_2->setObjectName(QString::fromUtf8("actionDeshacer_2"));
        actionDeshacer_2->setIcon(icon8);
        actionTemas_de_Ayuda = new QAction(Arepera);
        actionTemas_de_Ayuda->setObjectName(QString::fromUtf8("actionTemas_de_Ayuda"));
        actionTemas_de_Ayuda->setIcon(icon9);
        actionAcerca_de = new QAction(Arepera);
        actionAcerca_de->setObjectName(QString::fromUtf8("actionAcerca_de"));
        actionRehacer_2 = new QAction(Arepera);
        actionRehacer_2->setObjectName(QString::fromUtf8("actionRehacer_2"));
        actionRehacer_2->setIcon(icon7);
        actionSalir = new QAction(Arepera);
        actionSalir->setObjectName(QString::fromUtf8("actionSalir"));
        QIcon icon10;
        icon10.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/dialog-close.png")), QIcon::Normal, QIcon::Off);
        actionSalir->setIcon(icon10);
        actionPapelera = new QAction(Arepera);
        actionPapelera->setObjectName(QString::fromUtf8("actionPapelera"));
        QIcon icon11;
        icon11.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/application-x-trash.png")), QIcon::Normal, QIcon::Off);
        actionPapelera->setIcon(icon11);
        centralWidget = new QWidget(Arepera);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 10, 261, 611));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setMargin(11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(gridLayoutWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QFont font;
        font.setPointSize(10);
        tabWidget->setFont(font);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayoutWidget_3 = new QWidget(tab);
        gridLayoutWidget_3->setObjectName(QString::fromUtf8("gridLayoutWidget_3"));
        gridLayoutWidget_3->setGeometry(QRect(9, 49, 241, 521));
        layoutObjetos = new QGridLayout(gridLayoutWidget_3);
        layoutObjetos->setSpacing(6);
        layoutObjetos->setMargin(11);
        layoutObjetos->setObjectName(QString::fromUtf8("layoutObjetos"));
        layoutObjetos->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 10, 71, 31));
        QFont font1;
        font1.setPointSize(6);
        pushButton->setFont(font1);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(20, 20));
        pushButton_2 = new QPushButton(tab);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(90, 10, 71, 31));
        pushButton_2->setFont(font1);
        pushButton_2->setIcon(icon3);
        pushButton_2->setIconSize(QSize(20, 20));
        pushButton_3 = new QPushButton(tab);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(170, 10, 71, 31));
        pushButton_3->setFont(font1);
        QIcon icon12;
        icon12.addPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/images/format-fill-color.png")), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon12);
        pushButton_3->setIconSize(QSize(20, 20));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayoutWidget_2 = new QWidget(tab_2);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(9, 9, 241, 561));
        layoutProductos = new QGridLayout(gridLayoutWidget_2);
        layoutProductos->setSpacing(6);
        layoutProductos->setMargin(11);
        layoutProductos->setObjectName(QString::fromUtf8("layoutProductos"));
        layoutProductos->setContentsMargins(0, 0, 0, 0);
        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        tablero = new QWidget(centralWidget);
        tablero->setObjectName(QString::fromUtf8("tablero"));
        tablero->setGeometry(QRect(290, 10, 711, 621));
        Arepera->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Arepera);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1009, 25));
        menuArchivo = new QMenu(menuBar);
        menuArchivo->setObjectName(QString::fromUtf8("menuArchivo"));
        menuEditar = new QMenu(menuBar);
        menuEditar->setObjectName(QString::fromUtf8("menuEditar"));
        menuAyuda = new QMenu(menuBar);
        menuAyuda->setObjectName(QString::fromUtf8("menuAyuda"));
        Arepera->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Arepera);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setIconSize(QSize(36, 36));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        Arepera->addToolBar(Qt::TopToolBarArea, mainToolBar);
        mierda = new QStatusBar(Arepera);
        mierda->setObjectName(QString::fromUtf8("mierda"));
        Arepera->setStatusBar(mierda);
        QWidget::setTabOrder(tabWidget, pushButton);
        QWidget::setTabOrder(pushButton, pushButton_2);
        QWidget::setTabOrder(pushButton_2, pushButton_3);

        menuBar->addAction(menuArchivo->menuAction());
        menuBar->addAction(menuEditar->menuAction());
        menuBar->addAction(menuAyuda->menuAction());
        menuArchivo->addAction(actionAbrir_2);
        menuArchivo->addAction(actionImprimir_2);
        menuArchivo->addSeparator();
        menuArchivo->addAction(actionSalir);
        menuEditar->addAction(actionCopiar_2);
        menuEditar->addAction(actionCortar_2);
        menuEditar->addAction(actionPegar_2);
        menuEditar->addSeparator();
        menuEditar->addAction(actionDeshacer_2);
        menuEditar->addAction(actionRehacer_2);
        menuAyuda->addAction(actionTemas_de_Ayuda);
        menuAyuda->addSeparator();
        menuAyuda->addAction(actionAcerca_de);
        mainToolBar->addAction(actionAbrir);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionImprimir);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionCopiar);
        mainToolBar->addAction(actionCortar);
        mainToolBar->addAction(actionPegar);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionDeshacer);
        mainToolBar->addAction(actionRehacer);
        mainToolBar->addAction(actionPapelera);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionAyuda);

        retranslateUi(Arepera);
        QObject::connect(tabWidget, SIGNAL(selected(QString)), Arepera, SLOT(lockDrag(QString)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Arepera);
    } // setupUi

    void retranslateUi(QMainWindow *Arepera)
    {
        Arepera->setWindowTitle(QApplication::translate("Arepera", "Arepera con chicharron", 0, QApplication::UnicodeUTF8));
        actionNuevo->setText(QApplication::translate("Arepera", "Nuevo", 0, QApplication::UnicodeUTF8));
        actionAbrir->setText(QApplication::translate("Arepera", "Abrir", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAbrir->setToolTip(QApplication::translate("Arepera", "Abrir distribuci\303\263n de restaurant", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionImprimir->setText(QApplication::translate("Arepera", "Imprimir", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionImprimir->setToolTip(QApplication::translate("Arepera", "Imprimir factura", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionGuardar->setText(QApplication::translate("Arepera", "Guardar", 0, QApplication::UnicodeUTF8));
        actionCopiar->setText(QApplication::translate("Arepera", "Copiar", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCopiar->setToolTip(QApplication::translate("Arepera", "Copiar objeto o producto", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionCortar->setText(QApplication::translate("Arepera", "Cortar", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCortar->setToolTip(QApplication::translate("Arepera", "Cortar objeto o producto", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPegar->setText(QApplication::translate("Arepera", "Pegar", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPegar->setToolTip(QApplication::translate("Arepera", "Pegar objeto o producto", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionRehacer->setText(QApplication::translate("Arepera", "Rehacer", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRehacer->setToolTip(QApplication::translate("Arepera", "Rehacer ultima acci\303\263n deshecha", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionDeshacer->setText(QApplication::translate("Arepera", "Deshacer", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionDeshacer->setToolTip(QApplication::translate("Arepera", "Deshacer ultima acci\303\263n realizada", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAyuda->setText(QApplication::translate("Arepera", "Ayuda", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAyuda->setToolTip(QApplication::translate("Arepera", "Ayuda sobre el sistema", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionAbrir_2->setText(QApplication::translate("Arepera", "Abrir", 0, QApplication::UnicodeUTF8));
        actionImprimir_2->setText(QApplication::translate("Arepera", "Imprimir", 0, QApplication::UnicodeUTF8));
        actionCopiar_2->setText(QApplication::translate("Arepera", "Copiar", 0, QApplication::UnicodeUTF8));
        actionCortar_2->setText(QApplication::translate("Arepera", "Cortar", 0, QApplication::UnicodeUTF8));
        actionPegar_2->setText(QApplication::translate("Arepera", "Pegar", 0, QApplication::UnicodeUTF8));
        actionDeshacer_2->setText(QApplication::translate("Arepera", "Deshacer", 0, QApplication::UnicodeUTF8));
        actionTemas_de_Ayuda->setText(QApplication::translate("Arepera", "Temas de Ayuda", 0, QApplication::UnicodeUTF8));
        actionAcerca_de->setText(QApplication::translate("Arepera", "Acerca de...", 0, QApplication::UnicodeUTF8));
        actionRehacer_2->setText(QApplication::translate("Arepera", "Rehacer", 0, QApplication::UnicodeUTF8));
        actionSalir->setText(QApplication::translate("Arepera", "Salir", 0, QApplication::UnicodeUTF8));
        actionPapelera->setText(QApplication::translate("Arepera", "Papelera", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPapelera->setToolTip(QApplication::translate("Arepera", "Papelera de reciclaje de objetos o productos", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        tab->setToolTip(QApplication::translate("Arepera", "Secci\303\263n de dise\303\261o del restaurant", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        pushButton->setToolTip(QApplication::translate("Arepera", "Nuevo dise\303\261o de restaurant", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton->setText(QApplication::translate("Arepera", "Nuevo", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_2->setToolTip(QApplication::translate("Arepera", "Guardar dise\303\261o del restaurant", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_2->setText(QApplication::translate("Arepera", "Guardar", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_3->setToolTip(QApplication::translate("Arepera", "Seleccionar color del piso del restaurant", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_3->setText(QApplication::translate("Arepera", "Color", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Arepera", "Diseno", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        tab_2->setToolTip(QApplication::translate("Arepera", "Secci\303\263n de administracion de pedidos y mesas", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Arepera", "Administrador", 0, QApplication::UnicodeUTF8));
        menuArchivo->setTitle(QApplication::translate("Arepera", "Archivo", 0, QApplication::UnicodeUTF8));
        menuEditar->setTitle(QApplication::translate("Arepera", "Editar", 0, QApplication::UnicodeUTF8));
        menuAyuda->setTitle(QApplication::translate("Arepera", "Ayuda", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Arepera: public Ui_Arepera {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AREPERA_H
