#ifndef TILDA_H
#define TILDA_H

#include <QtGui/QMainWindow>
#include <QtGui/QTableWidget>
#include "object.h"

namespace Ui {
    class Tilda;
}

class Tilda : public QMainWindow {
    Q_OBJECT
    Q_DISABLE_COPY(Tilda)
public:
    QTableWidget *tabla;
    explicit Tilda(QWidget *parent = 0);
    virtual ~Tilda();
    void set_tilda(Object *);
    void mostrar();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::Tilda *m_ui;
};

#endif // TILDA_H
