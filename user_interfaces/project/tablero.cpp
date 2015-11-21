#include "tablero.h"
#include "ui_tablero.h"
#include "tilda.h"
#include "object.h"
#include "arepera.h"
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <QtGui/QLabel>
#include <QtGui/QFrame>
#include <QtGui>
#include <typeinfo>
#include <QPainter>

static int mesas;
static int bares;
static int obts;

static char st[30];
//static QLabel *ql;


Tablero::Tablero(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::Tablero)
{
    m_ui->setupUi(this);
    //st = '\0';
    //ql = new QLabel(m_ui->frame);

}

Object* Tablero::getObject(){
    return this->obj;
}

void Tablero::nuevoProducto(QTreeWidgetItem *item,int n,int can){
     if (this->obj == NULL || this->obj->tipo == "Obstaculo") {
        cout << "No hay ninguna mesa seleccionada " << typeid(this->parentWidget()).name() <<endl;
        Arepera *are = (Arepera*) parentWidget();
        cout << "pude crear la variable" << endl;
        //are->showStatus();
       //showMessage(item->text(n),2000);
        //are->
        return;
    }
    Product *pro = new Product();
    QByteArray ba = item->text(n).toLatin1();
    string s = ba.data();
    if (s == "Arepa de Chicharron" || s == "Arepa de Queso Amarillo" || s == "Arepa de Queso Guayanes" || s == "Arepa de Carne Mechada" || s == "Arepa Pelua" || s == "Arepa Reina Pepeada") pro->precio = 15;
    else if (s == "Empanada de Queso" || s == "Empanada de Carne Mechada" || s == "Empana de Carne Molida" || s == "Empanada Domino" || s == "Empanada de Pollo") pro->precio = 5;
    else if (s == "Sandwich de Jamon y Queso" || s == "Sandwich de Atun" || s == "Club House") pro->precio = 8;
    else if (s == "Pepsi" || s == "Coca-Cola" || s == "Frescolita" || s == "7up" || s == "Coca-Cola Zero") pro->precio = 4;
    else if (s == "Naranja" || s == "Melon" || s == "Lechoza" || s == "Fresa" || s == "Durazno") pro->precio = 5;
    else if (s == "Negro" || s == "Marron" || s == "Marron Oscuro" || s == "Con Leche" || s == "Guayoyo") pro->precio = 3;
    pro->nombre = ba.data();//item->text(n);
    pro->cantidad = can;
    //if (s ==)
    cout << "Le agregue al objeto " << this->obj->tipo << " con id " << this->obj->nombre << " el item " << ba.data() << " con cantidad " << can << " y precio " << pro->precio << endl;
    this->obj->productos.push_back(*pro);
}

void Tablero::nuevoObjeto(QString s){
    cout << "Estoy creando objeto" << endl;
    stringstream out;
    if (s == "Mesas" || s == "Obstaculos" || s == "Bares"){
       cout << "es una mesa" << endl;
       return;
   }


    cout << "Estoy creando objeto2" << endl;
    cout << "frame " << typeid(m_ui->frame).name() <<endl;
    Object *obs3 = new Object(m_ui->frame);
    cout << "cree el objeto" << endl;
    //QLabel *obs3 = new QLabel(m_ui->frame);

    //QLabel *obs3 = new QLabel(m_ui->frame);
    if (s == "Redondas"){
        //obs3->setPixmap(QPixmap(":/new/prefix1/images/mesaCircular.png"));
        QPixmap imagen = QPixmap(":/new/prefix1/images/mesaCircular.png");
        QPixmap imagen2 = imagen.scaledToHeight(100);
        QPixmap imagen3 = imagen2.scaledToWidth(100);
        obs3->setPixmap(imagen3);
        out << mesas;
        obs3->nombre = out.str();
        mesas++;
        obs3->tipo = "Mesa";
        //obs3->tipo
    }
    if (s == "Cuadradas"){
        //obs3->setPixmap(QPixmap(":/new/prefix1/images/mesaCuadrada.png"));
        QPixmap imagen = QPixmap(":/new/prefix1/images/mesaCuadrada.png");
        QPixmap imagen2 = imagen.scaledToHeight(100);
        QPixmap imagen3 = imagen2.scaledToWidth(100);
        obs3->setPixmap(imagen3);
        out << mesas;
        obs3->nombre = out.str();
        mesas++;
        obs3->tipo = "Mesa";
    }
     if (s == "Cuadrados"){
        //obs3->setPixmap(QPixmap(":/new/prefix1/images/barSillas.png"));
        QPixmap imagen = QPixmap(":/new/prefix1/images/barSillas.png");
        QPixmap imagen2 = imagen.scaledToHeight(200);
        QPixmap imagen3 = imagen2.scaledToWidth(200);
        obs3->setPixmap(imagen3);
        out << bares;
        obs3->nombre = out.str();
        bares++;
        obs3->tipo = "Bar";
    }
     if (s == "Columnas"){
        QPixmap imagen = QPixmap(":/new/prefix1/images/obst1.png");
        QPixmap imagen2 = imagen.scaledToHeight(80);
        QPixmap imagen3 = imagen2.scaledToWidth(80);
        obs3->setPixmap(imagen3);
        out << obts;
        obs3->nombre = out.str();
        obts++;
        obs3->tipo = "Obstaculo";
    }
     if (s == "Muros"){
        //obs3->setPixmap(QPixmap(":/new/prefix1/images/obst2.png"));
        QPixmap imagen = QPixmap(":/new/prefix1/images/obst2.png");
        QPixmap imagen2 = imagen.scaledToHeight(200);
        QPixmap imagen3 = imagen2.scaledToWidth(200);
        obs3->setPixmap(imagen3);
        out << obts;
        obs3->nombre = out.str();
        obts++;
        obs3->tipo = "Obstaculo";
    }



    cout << "Estoy aqui para mostrar" << endl;
    //obs3->nombre = "mesa1";
    obs3->move(300, 400);
    obs3->show();
    obs3->setAttribute(Qt::WA_DeleteOnClose);
}

Tablero::~Tablero()
{
    delete m_ui;
}

void Tablero::changeEvent(QEvent *e)
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

 void Tablero::dragEnterEvent(QDragEnterEvent *event)
 {
     if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
         if (event->source() == m_ui->frame) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
         } else {
             event->acceptProposedAction();
         }
     } else {
         event->ignore();
     }
 }

 void Tablero::dragMoveEvent(QDragMoveEvent *event)
 {
     if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
         if (event->source() == m_ui->frame) {
             //cout << event->
             event->setDropAction(Qt::MoveAction);
             event->accept();
         } else {
             event->acceptProposedAction();
         }
     } else {
         event->ignore();
     }
 }

 void Tablero::dropEvent(QDropEvent *event)
 {
     if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
         QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
         QDataStream dataStream(&itemData, QIODevice::ReadOnly);

         QPixmap pixmap;
         QPoint offset;
         char *nombre;
         char* tipo;
         dataStream >> pixmap >>nombre >> tipo >> offset;

         Object *newIcon = new Object(m_ui->frame);
         newIcon->setPixmap(pixmap);
         newIcon->move(event->pos() - offset);
         newIcon->show();
         newIcon->nombre = nombre;
         newIcon->tipo = tipo;
         newIcon->setAttribute(Qt::WA_DeleteOnClose);
         cout << "El objeto tiene tipo " << tipo << " y nombre " << nombre << endl;

         if (event->source() == m_ui->frame) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
         } else {
             event->acceptProposedAction();
         }
     } else {
         event->ignore();
     }
 }

 void Tablero::mousePressEvent(QMouseEvent *event)
 {
     cout << "antes de object"  << endl;
     Object *child = static_cast<Object*>(childAt(event->pos()));
     cout << "antes de child" << child << endl;
      if (strcmp(typeid(*child).name(),"6QFrame") == 0){
        cout << "hice click en la pantalla" <<endl;
        return;
    }
     this->obj = child;
     char* nombre = &child->nombre[0];
     char* tipo = &child->tipo[0];
     cout << nombre << endl;
     QPixmap pixmap = *child->pixmap();

     //strcat(st,tipo);
     //strcat(st,nombre);
     //st = st + (QString)tipo;
     sprintf(st,"%s%s",tipo,nombre);
     cout << "el nombre es" << st << endl;
     m_ui->seleccion->clear();
     m_ui->seleccion->setText(st);


     //ql->setText(strcat(tipo,nombre));
     //ql->move(child->pos().x(), child->pos().y()-20);
     //ql->show();

     //QRectF rectangle(10.0, 20.0, child->pos().x(), child->pos().y());

    //QPainter painter(this);
    //painter.drawEllipse(rectangle);

     QByteArray itemData;
     QDataStream dataStream(&itemData, QIODevice::WriteOnly);
     dataStream << pixmap << nombre << tipo << QPoint(event->pos() - child->pos());


     QMimeData *mimeData = new QMimeData;
     mimeData->setData("application/x-dnditemdata", itemData);


     QDrag *drag = new QDrag(m_ui->frame);
     drag->setMimeData(mimeData);
     drag->setPixmap(pixmap);
     drag->setHotSpot(event->pos() - child->pos());
     //drag->setUserData(1,*child);

     QPixmap tempPixmap = pixmap;

     child->setPixmap(tempPixmap);

     if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
         child->close();
     else {
         child->show();
         child->setPixmap(pixmap);
     }
 }

/*void Tablero::agregarWidget(QWidget *e){
    m_ui->graphicsView->
}*/
