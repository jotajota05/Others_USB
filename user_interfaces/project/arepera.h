#ifndef AREPERA_H
#define AREPERA_H

#include <QtGui/QMainWindow>
#include "tablero.h"

namespace Ui
{
    class Arepera;
}

class Arepera : public QMainWindow
{
    Q_OBJECT

public:
    Arepera(QWidget *parent = 0);
    ~Arepera();
    void showStatus();
    //Tablero* tab;
    Tablero* getTablero();
    Ui::Arepera *ui;

private slots:
    void on_actionAbrir_triggered();
    void on_actionImprimir_triggered();
    void on_pushButton_2_clicked();
    void on_actionSalir_triggered();
    void lockDrag(QString);
};

#endif // AREPERA_H
