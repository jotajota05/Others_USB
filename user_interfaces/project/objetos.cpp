#include "objetos.h"
#include "tablero.h"
#include "tilda.h"
#include "arepera.h"
#include "ui_objetos.h"
#include <iostream>
//#include <stdio.h>
using namespace std;

Objetos::Objetos(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::Objetos)
{
    m_ui->setupUi(this);
}

Objetos::~Objetos()
{
    delete m_ui;
}

void Objetos::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Objetos::newObs(QTreeWidgetItem *item,int n)
{
    //printf("HOLAAAAAAAAA");
    Arepera *are = (Arepera*) parentWidget();
    cout << "obteniendo el tablero" << endl;
    Tablero *tab = are->getTablero();
      cout << "obtuve el tablero" << endl;
    tab->nuevoObjeto(item->text(n));

    QString prueba = item->text(n);
    cout << "Esto es la creacion de un objeto" << endl;
    //printf("Estoy creando nuevo objeto");
    //Tilda *til = new Tilda(this);
    //til-> setWindowTitle(prueba);
    //til->show();
    //til->move(400,200);
}

