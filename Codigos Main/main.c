/**
 * @file main.c
 * @brief Sistema de inventario con RFID.
 *
 * Este archivo contiene la implementación principal del sistema de inventario utilizando RFID,
 * un teclado matricial y una pantalla LCD.
 */

#include "main.h"

#define RST_PIN 0   ///< Pin 9 para el reset del RC522
#define SS_PIN  17  ///< Pin 10 para el SS (SDA) del RC522
#define SPI_PORT 0

/**
 * @brief Función principal del sistema.
 *
 * Esta función inicializa los periféricos y maneja el flujo principal del programa.
 *
 * @return int Código de retorno del programa.
 */
int main() {
    stdio_init_all();
    sleep_ms(7000);

    // Inicialización del teclado y LCD
    setup();
    lcd_init();
    printf("Sistema de Inventario con RFID\n");

    // Inicialización del lector RFID
    MFRC522Ptr_t mfrc522 = MFRC522_Init();
    PCD_Init(mfrc522, SPI_PORT);

    while (1) {
        switch (etapa) {
            case 0:
                lcd_clear();
                lcd_string("Escanee tarjeta");
                if (LeerTarjeta(mfrc522)) {
                    etapa++;
                }
                break;

            case 1:
                lcd_clear();
                lcd_string("Ingrese Clave:");
                char key = get_key_pressed();
                if (key != '\0') {
                    lcd_set_cursor(1, 0);
                    lcd_char(key);
                    if (key == 'A') {  // Simulación de clave correcta con 'A'
                        etapa++;
                    } else {
                        etapa = 0;  // Clave incorrecta
                    }
                }
                break;

            case 2:
                lcd_clear();
                lcd_string("Leyendo datos...");
                LeerBloque(mfrc522, 1, infoLectura);
                sleep_ms(3000);
                etapa++;
                break;

            case 3:
                lcd_clear();
                lcd_string("Operacion:");
                key = get_key_pressed();
                if (key == 'B') {
                    manejar_compra();
                    etapa = 0;
                } else if (key == 'C') {
                    manejar_venta();
                    etapa = 0;
                } else if (key == 'D') {
                    lcd_clear();
                    lcd_string("Invalido");
                    etapa = 0;
                }
                break;

            default:
                etapa = 0;
                break;
        }

        tight_loop_contents();
    }

    return 0;
}

/**
 * @brief Maneja la lógica de compra.
 */
void manejar_compra() {
    lcd_clear();
    lcd_string("Compra");
    // Lógica de compra
    // Ejemplo de compra:
    if (InventarioTotal[6] < (infoLectura[1] * infoLectura[3])) {
        lcd_clear();
        lcd_string("Compra denegada");
        sleep_ms(2000);
        return;
    }

    switch (infoLectura[0]) {
        case 0:
            actualizar_inventario(&Fertilizante, infoLectura[1]);
            break;
        case 1:
            actualizar_inventario(&Fungicida, infoLectura[1]);
            break;
        case 2:
            actualizar_inventario(&Insecticida, infoLectura[1]);
            break;
        case 3:
            actualizar_inventario(&Semillas, infoLectura[1]);
            break;
        case 4:
            actualizar_inventario(&Red, infoLectura[1]);
            break;
        default:
            lcd_clear();
            lcd_string("Producto invalido");
            sleep_ms(2000);
            break;
    }
}

/**
 * @brief Maneja la lógica de venta.
 */
void manejar_venta() {
    lcd_clear();
    lcd_string("Venta");
    // Lógica de venta
    // Ejemplo de venta:
    if (infoLectura[1] > InventarioTotal[infoLectura[0]]) {
        lcd_clear();
        lcd_string("Venta denegada");
        sleep_ms(2000);
        return;
    }

    switch (infoLectura[0]) {
        case 0:
            descontar_inventario(&Fertilizante, infoLectura[1]);
            break;
        case 1:
            descontar_inventario(&Fungicida, infoLectura[1]);
            break;
        case 2:
            descontar_inventario(&Insecticida, infoLectura[1]);
            break;
        case 3:
            descontar_inventario(&Semillas, infoLectura[1]);
            break;
        case 4:
            descontar_inventario(&Red, infoLectura[1]);
            break;
        default:
            lcd_clear();
            lcd_string("Producto invalido");
            sleep_ms(2000);
            break;
    }
}

/**
 * @brief Actualiza el inventario después de una compra.
 * 
 * @param producto Puntero al producto a actualizar.
 * @param cantidad Cantidad comprada.
 */
void actualizar_inventario(Producto *producto, int cantidad) {
    producto->Cantidad += cantidad;
    InventarioTotal[6] -= producto->Compra * cantidad;
    lcd_clear();
    lcd_string("Compra exitosa");
    sleep_ms(2000);
}

/**
 * @brief Descuenta el inventario después de una venta.
 * 
 * @param producto Puntero al producto a actualizar.
 * @param cantidad Cantidad vendida.
 */
void descontar_inventario(Producto *producto, int cantidad) {
    producto->Cantidad -= cantidad;
    InventarioTotal[5] += producto->Venta * cantidad;
    lcd_clear();
    lcd_string("Venta exitosa");
    sleep_ms(2000);
}
