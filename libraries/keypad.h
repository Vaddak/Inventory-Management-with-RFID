#ifndef KEYPAD_H
#define KEYPAD_H

extern volatile int KEY_PRESS_DELAY_MS;

// Función para inicializar el teclado
void setup();

// Función para leer el valor del teclado
char get_key_pressed();

#endif // KEYPAD_H


/*
EJEMPLO

int main() {
   stdio_init_all();
   setup();

   while (true) {
       char key = get_key_pressed();
       if (key != '\0') {
           printf("Tecla presionada: %c\n", key); 
           sleep_ms(KEY_PRESS_DELAY_MS); // Retardo para evitar detección múltiple
       }
   }
   return 0;
}

*/