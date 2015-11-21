#ifndef CANTIDAD_H
#define CANTIDAD_H

#include <QtGui/QDialog>
#include <QTreeWidgetItem>

namespace Ui {
    class cantidad;
}

class cantidad : public QDialog {
    Q_OBJECT
public:
    QTreeWidgetItem *it;
    int n1;
    cantidad(QWidget *parent = 0);
    ~cantidad();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::cantidad *m_ui;

private slots:
    void comFather();

};

#endif // CANTIDAD_H
