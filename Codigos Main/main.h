#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/sync.h"
#include "MFRC522.h"
#include "Sensor_rfid.h"
#include "lcd.h"
#include "keypad.h"

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
Fertilizante.Venta = 12000;
Fertilizante.Compra = 20000;

Producto Fungicida;
strcpy(Fungicida.Tipo, "Fungicida");
Fungicida.Cantidad = 70;
Fungicida.Venta = 8000;
Fungicida.Compra = 12000;

Producto Insecticida;
strcpy(Insecticida.Tipo, "Insecticida");
Insecticida.Cantidad = 50;
Insecticida.Venta = 8000;
Insecticida.Compra = 12000;

Producto Semillas;
strcpy(Semillas.Tipo, "Semillas");
Semillas.Cantidad = 200;
Semillas.Venta = 3000;
Semillas.Compra = 7000;

Producto Red;
strcpy(Red.Tipo, "Red");
Red.Cantidad = 10;
Red.Venta = 8000;
Red.Compra = 14000;

//Elementos de interacción con el rfid
uint8_t etapa=0;
bool identificaciones;
uint8_t infoLectura[18]; // Buffer para guardar la lectura
uint8_t infoEscritura[16] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                            0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                            0x01, 0x01, 0x01, 0x01}; // Buffer de escritura

//Caracterizacion del inventario
uint8_t num1 = 1;
uint8_t num2 = 0;
uint8_t num3 = 0;
uint8_t num4 = 1;

uint8_t InventarioTotal[7] = {0,0,0,0,0,0,500000};

#endif