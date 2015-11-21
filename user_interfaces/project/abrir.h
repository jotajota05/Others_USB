#ifndef ABRIR_H
#define ABRIR_H

#include <QtGui/QDialog>

namespace Ui {
    class Abrir;
}

class Abrir : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(Abrir)
public:
    explicit Abrir(QWidget *parent = 0);
    virtual ~Abrir();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::Abrir *m_ui;
};

#endif // ABRIR_H
