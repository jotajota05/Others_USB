#include "productos.h"
#include "ui_productos.h"
#include "arepera.h"
#include "tablero.h"
#include "tilda.h"
#include "ui_objetos.h"
#include "object.h"
#include "cantidad.h"
#include <iostream>
#include <typeinfo>
using namespace std;

Productos::Productos(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::Productos)
{
    m_ui->setupUi(this);
}

Productos::~Productos()
{
    delete m_ui;
}

void Productos::changeEvent(QEvent *e)
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

void Productos::cantidadDialog(QTreeWidgetItem* item,int n){
    QString s = item->text(n);
    if (s == "Arepas" || s == "Empanadas" || s == "Sandwich" || s == "Refrescos" || s == "Jugos" || s == "Cafe"){
        return;
    }
    cantidad *can = new cantidad(this);
    can->it = item;
    can->n1 = n;
    can-> setWindowTitle("Introduzca la cantidad");
    can->show();
    can->move(400,200);
}


void Productos::newProd(QTreeWidgetItem *item,int n,int can)
{
    cout << "Nuevo producto" << typeid(this->parentWidget()).name() <<endl;
    Arepera *are = (Arepera*) parentWidget();
    Tablero *tab = are->getTablero();
    tab->nuevoProducto(item,n,can);

    /*QString prueba = item->text(n);
    cout << "Esto es la creacion de un producto" << endl;
    Tilda *til = new Tilda(this);
    til-> setWindowTitle(prueba);
    til->show();
    til->move(400,200);*/
}
