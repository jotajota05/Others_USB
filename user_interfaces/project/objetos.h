#ifndef OBJETOS_H
#define OBJETOS_H

#include <QtGui/QWidget>
#include <QTreeWidgetItem>

namespace Ui {
    class Objetos;
}

class Objetos : public QWidget {
    Q_OBJECT
    Q_DISABLE_COPY(Objetos)
public:
    explicit Objetos(QWidget *parent = 0);
    virtual ~Objetos();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::Objetos *m_ui;

private slots:
    void newObs(QTreeWidgetItem* item, int n);

};

#endif // OBJETOS_H
