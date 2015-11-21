#include "dialogoabrir.h"
#include "ui_dialogoabrir.h"

DialogoAbrir::DialogoAbrir(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::DialogoAbrir)
{
    m_ui->setupUi(this);
}

DialogoAbrir::~DialogoAbrir()
{
    delete m_ui;
}

void DialogoAbrir::changeEvent(QEvent *e)
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
