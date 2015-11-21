#include "cantidad.h"
#include "ui_cantidad.h"
#include "productos.h"

cantidad::cantidad(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::cantidad)
{
    m_ui->setupUi(this);
}

cantidad::~cantidad()
{
    delete m_ui;
}

void cantidad::comFather(){
    Productos *pro = (Productos*) parentWidget();
    pro->newProd(this->it,this->n1,this->m_ui->spinBox->value());
}

void cantidad::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
