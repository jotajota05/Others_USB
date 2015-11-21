#include "abrir.h"
#include "ui_abrir.h"

Abrir::Abrir(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::Abrir)
{
    m_ui->setupUi(this);
}

Abrir::~Abrir()
{
    delete m_ui;
}

void Abrir::changeEvent(QEvent *e)
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
