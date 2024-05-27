#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdio.h>
#include "keypad.h"


#define KEYPAD_ROWS 4
#define KEYPAD_COLUMNS 4
#define DEBOUNCE_DELAY_MS 50
volatile int KEY_PRESS_DELAY_MS = 200 ;// Retardo después de detectar una tecla

char matrix_keys[KEYPAD_ROWS][KEYPAD_COLUMNS] = {
   {'1', '2', '3', 'A'},
   {'4', '5', '6', 'B'},
   {'7', '8', '9', 'C'},
   {'*', '0', '#', 'D'}
};

int keypad_rows[KEYPAD_ROWS] = {2, 3, 4, 5};
int keypad_columns[KEYPAD_COLUMNS] = {6, 7, 8, 9};

void setup() {
   // Inicializar pines del teclado
   for (int i = 0; i < KEYPAD_ROWS; i++) {
       gpio_init(keypad_rows[i]);
       gpio_set_dir(keypad_rows[i], GPIO_IN); // Filas como entrada
       gpio_pull_down(keypad_rows[i]); // Pull-down en filas
   }

   for (int i = 0; i < KEYPAD_COLUMNS; i++) {
       gpio_init(keypad_columns[i]);
       gpio_set_dir(keypad_columns[i], GPIO_OUT); // Columnas como salida
       gpio_put(keypad_columns[i], 0); // Inicializar columnas en bajo
   }
}


char get_key_pressed() {
   for (int col = 0; col < KEYPAD_COLUMNS; col++) {
       gpio_put(keypad_columns[col], 1); // Activar columna
       sleep_ms(1); // Pequeño delay para estabilizar el voltaje

       for (int row = 0; row < KEYPAD_ROWS; row++) {
           if (gpio_get(keypad_rows[row])) {
               // Anti-rebote
               sleep_ms(DEBOUNCE_DELAY_MS);
               if (gpio_get(keypad_rows[row])) {
                   char key = matrix_keys[row][col]; // Guardar tecla antes de desactivar la columna
                   gpio_put(keypad_columns[col], 0); // Desactivar columna 
                   return key; // Retornar la tecla presionada
               }
           }
       }
       gpio_put(keypad_columns[col], 0); // Desactivar columna si ninguna tecla fue presionada
   }
   return '\0'; // Ninguna tecla presionada
}


