#include "tilda.h"
#include "ui_tilda.h"
#include "object.h"
#include "product.h"
#include <QtGui/QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>
#include <Qt>
#include <stdio.h>


using namespace std;

Tilda::Tilda(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::Tilda)
{
    m_ui->setupUi(this);

}

Tilda::~Tilda()
{
    delete m_ui;
}

void Tilda::set_tilda(Object *obj) {
    this->tabla = new QTableWidget(obj->productos.size(),4,this);
    QStringList lista;
    lista.append("Nombre");
    lista.append("Cantidad");
    lista.append("Precio Unit. (Bs)");
    lista.append("Total (Bs)");
    this->tabla->setHorizontalHeaderLabels(lista);

    list<Product>::iterator it = obj->productos.begin();
    QTableWidgetItem* item1;
    int row = 0;
    int total = 0;
    char aux[20];
    while (it != obj->productos.end()) {

            item1 = new QTableWidgetItem(((*it).nombre).c_str());
            //item1->setFlags(ItemFlags(2));
            this->tabla->setItem(row,0,item1);

            sprintf(aux, "%d", (*it).cantidad);
            item1 = new QTableWidgetItem(aux);
            //item1->setFlags(ItemFlags(2));
            this->tabla->setItem(row,1,item1);

            sprintf(aux, "%d", (*it).precio);
            item1 = new QTableWidgetItem(aux);
            //item1->setFlags(ItemFlags(2));
            this->tabla->setItem(row,2,item1);

            total += (*it).cantidad * (*it).precio;

            sprintf(aux, "%d", (*it).cantidad * (*it).precio);
            item1 = new QTableWidgetItem(aux);
            //item1->setFlags(ItemFlags(2));
            this->tabla->setItem(row,3,item1);
            row++;
            it++;

    }
    sprintf(aux, "%d", total);
    this->m_ui->label_2->setText(aux);
}

void Tilda::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Tilda::mostrar() {
    m_ui->gridLayout->addWidget(this->tabla,0,0);

    this->show();
}
