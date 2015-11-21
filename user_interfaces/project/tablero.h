#ifndef TABLERO_H
#define TABLERO_H

#include <QtGui/QWidget>
#include <QFrame>
#include <QTreeWidgetItem>
#include "object.h"


namespace Ui {
    class Tablero;
}

class Tablero : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(Tablero)
public:
    Object *obj;
    explicit Tablero(QWidget *parent = 0);
    virtual ~Tablero();
    void nuevoObjeto(QString s);
    void nuevoProducto(QTreeWidgetItem *item,int n,int can);
    Object* getObject();

protected:
    virtual void changeEvent(QEvent *e);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);


private:
    Ui::Tablero *m_ui;
};

#endif // TABLERO_H
