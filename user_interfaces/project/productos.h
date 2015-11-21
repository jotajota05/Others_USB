#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#include <QtGui/QWidget>
#include <QTreeWidgetItem>
#include "object.h"

namespace Ui {
    class Productos;
}

class Productos : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(Productos)
public:
    explicit Productos(QWidget *parent = 0);
    virtual ~Productos();
    void newProd(QTreeWidgetItem* item, int n,int can);

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::Productos *m_ui;
private slots:
    void cantidadDialog(QTreeWidgetItem* item,int n);

};



#endif // PRODUCTOS_H
