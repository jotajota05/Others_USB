#include <QVBoxLayout>
#include "arepera.h"
#include "ui_arepera.h"
#include "tablero.h"
#include "productos.h"
#include "objetos.h"
#include "object.h"
#include "tilda.h"
#include "abrir.h"
#include <stdio.h>
#include <iostream>
//#include <QTextOStream>
Tablero *tab;
using namespace std;

Arepera::Arepera(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Arepera)
{
    //QTextOStream cout(stdout);
    ui->setupUi(this);
    Qt::WindowFlags flags = Qt::SubWindow;
    this->setWindowFlags(flags);
    printf("Cree la arepera");
    cout << "prueba" << endl;

     QGridLayout *lay_d = new QGridLayout(ui->tablero);
     tab = new Tablero(this);
     lay_d->addWidget(tab,0,0);

     Productos *prod = new Productos(this);
     ui->layoutProductos->addWidget(prod,0,0);

     Objetos *obj = new Objetos(this);
     ui->layoutObjetos->addWidget(obj,0,0);

}

Tablero* Arepera::getTablero(){
    return tab;
}

void Arepera::on_actionSalir_triggered()
{
    close();
}


Arepera::~Arepera()
{
    delete ui;
}

void Arepera::on_actionImprimir_triggered()
{
   Tablero* tab = this->getTablero();
   Object *obj = tab->getObject();
   Tilda *til = new Tilda(obj);
   til->set_tilda(obj);
   til->mostrar();

}

void Arepera::on_actionAbrir_triggered()
{
    Abrir *abr = new Abrir(this);
    abr->show();
    abr->move(400,200);
}

void Arepera::on_pushButton_2_clicked(){
    return;
}

void Arepera::showStatus(){
    cout << "Entre en el show status" << endl;
    QString s = "hey";
    ui->mierda->showMessage(s,2000);
    return;
}

void Arepera::lockDrag(QString s)
{
    Tablero* tab = this->getTablero();
    if (s == "Diseno"){
        tab->setAcceptDrops(true);
    }
    if (s == "Administrador"){
        tab->setAcceptDrops(false);
    }
    //printf("HOLAAAAAAAAA");
    //Arepera *are = (Arepera*) parentWidget();
    //Tablero *tab = are->getTablero();
    //tab->nuevoObjeto(item->text(n));

    //QString prueba = item->text(n);
    //cout << "Esto es la creacion de un objeto" << endl;
    //printf("Estoy creando nuevo objeto");
    //Tilda *til = new Tilda(this);
    //til-> setWindowTitle(prueba);
    //til->show();
    //til->move(400,200);
}
