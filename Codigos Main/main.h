#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <string.h>

// Definición de la estructura Producto
typedef struct {
    // Tipos de productos: Fertilizante, Insecticida, Fungicida, Semillas, Red
    char Tipo[20];
    int Cantidad;
    int Venta;
    int Compra;
} Producto;

// Creación de los productos
Producto Fertilizante;
strcpy(Fertilizante.Tipo, "Fertilizante");
Fertilizante.Cantidad = 50;
Fertilizante.Venta = 12;
Fertilizante.Compra = 20;

Producto Fungicida;
strcpy(Fungicida.Tipo, "Fungicida");
Fungicida.Cantidad = 70;
Fungicida.Venta = 8;
Fungicida.Compra = 12;

Producto Insecticida;
strcpy(Insecticida.Tipo, "Insecticida");
Insecticida.Cantidad = 50;
Insecticida.Venta = 8;
Insecticida.Compra = 12;

Producto Semillas;
strcpy(Semillas.Tipo, "Semillas");
Semillas.Cantidad = 200;
Semillas.Venta = 3;
Semillas.Compra = 7;

Producto Red;
strcpy(Red.Tipo, "Red");
Red.Cantidad = 10;
Red.Venta = 8;
Red.Compra = 14;


#endif