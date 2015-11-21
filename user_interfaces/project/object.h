#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include <iostream>
#include <list>
#include <QtGui/QLabel>
#include <QtGui/QWidget>
#include "product.h"

using namespace std;

class Object : public QLabel
{
    Q_OBJECT
public:
    string nombre;
    string tipo;
    //string icono;
    //int posicion_x;
    //int posicion_y;
    list<Product> productos;
    //static int cantidad;
    Object();
    Object(QWidget*);
    //virtual ~Object();
};
//int Object::cantidad = 0;
#endif // OBJECT_H
