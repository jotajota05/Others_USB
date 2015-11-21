#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
#include <iostream>
#include <list>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

using namespace std;

class Product
{
public:
   string nombre;
   string descripcion;
   int precio;
   int cantidad;
   string icon;
   Product();
};

#endif // PRODUCT_H
