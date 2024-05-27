/**
 * @file sensor_rfid.c
 * @brief Implementación de funciones para la lectura y escritura de tarjetas RFID.
 *
 * Este archivo contiene las implementaciones de las funciones declaradas en sensor_rfid.h
 */

// Librerías estándar
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "MFRC522.h"
#include "RFID.h"
#include "sensor_rfid.h"

#define TIMEOUT_US 1000000

MIFARE_Key keyBlock = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
const uint8_t expectedUID[] = {0xCB, 0xE7, 0x27, 0x79};
const size_t expectedUIDLength = sizeof(expectedUID) / sizeof(expectedUID[0]});

/**
 * @brief Lee un bloque de datos de una tarjeta RFID.
 * 
 * @param mfrc Puntero que apunta al MFRC522.
 * @param bloque Número del bloque que se va a leer.
 * @param info Buffer donde se almacenarán los datos leídos del bloque.
 */
void LeerBloque(MFRC522Ptr_t mfrc, uint8_t bloque, uint8_t info[18]) {
    uint8_t len = 18;
    printf("Por favor, coloque la tarjeta RFID.\n");
    while (!PICC_IsNewCardPresent(mfrc));
    printf("Leyendo tarjeta...\n");
    PICC_ReadCardSerial(mfrc);
    printf("Tarjeta reconocida.\n");
    if (PCD_Authenticate(mfrc, PICC_CMD_MF_AUTH_KEY_A, bloque, &keyBlock, &(mfrc->uid)) == 0) {
        printf("Autenticación exitosa.\n");
        if (MIFARE_Read(mfrc, bloque, info, &len) == 0) {
            printf("Lectura de bloque exitosa. Datos: ");
            for (int i = 0; i < 16; i++) {
                printf("%u ", info[i]);
            }
            printf("\n");
            PCD_StopCrypto1(mfrc);
        } else {
            printf("Error al leer el bloque.\n");
        }
    } else {
        printf("Error en la autenticación.\n");
    }
}

/**
 * @brief Escribe un bloque de datos en una tarjeta RFID.
 * 
 * @param mfrc Puntero que apunta al MFRC522.
 * @param bloque Número del bloque que se va a escribir.
 * @param info Datos que se van a escribir en el bloque.
 */
void EscribeBloque(MFRC522Ptr_t mfrc, uint8_t bloque, uint8_t info[16]) {
    uint8_t len = 16;
    printf("Por favor, coloque la tarjeta RFID.\n");
    while (!PICC_IsNewCardPresent(mfrc));
    printf("Escribiendo en la tarjeta...\n");
    PICC_ReadCardSerial(mfrc);
    printf("Tarjeta reconocida.\n");
    if (PCD_Authenticate(mfrc, PICC_CMD_MF_AUTH_KEY_A, bloque, &keyBlock, &(mfrc->uid)) == 0) {
        printf("Autenticación exitosa.\n");
        if (MIFARE_Write(mfrc, bloque, info, len) == 0) {
            printf("Bloque escrito exitosamente.\n");
            PCD_StopCrypto1(mfrc);
        } else {
            printf("Error al escribir el bloque.\n");
        }
    } else {
        printf("Error en la autenticación.\n");
    }
}

/**
 * @brief Verifica si dos UID son iguales.
 * 
 * @param entrada UID recibido.
 * @param longitudEntrada Longitud del UID recibido.
 * @param esperado UID esperado.
 * @param longitudEsperado Longitud del UID esperado.
 * 
 * @return true si los UID coinciden, false en caso contrario.
 */
bool VerificaciónUID(const uint8_t *entrada, size_t longitudEntrada, const uint8_t *esperado, size_t longitudEsperado) {
    if (longitudEntrada != longitudEsperado) {
        return false;
    }
    for (size_t i = 0; i < longitudEntrada; i++) {
        if (entrada[i] != esperado[i]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Lee la UID de una tarjeta RFID y la compara con la UID esperada.
 * 
 * @param mfrc Puntero que apunta al MFRC522.
 * 
 * @return true si la UID leída coincide con la UID esperada, false en caso contrario.
 */
bool LeerTarjeta(MFRC522Ptr_t mfrc) {
    while (!PICC_IsNewCardPresent(mfrc));
    PICC_ReadCardSerial(mfrc);
    bool uidCorrecto = VerificaciónUID(mfrc->uid.uidByte, mfrc->uid.size, expectedUID, expectedUIDLength);
    if (uidCorrecto) {
        printf("UID correcto.\n");
    } else {
        printf("UID incorrecto.\n");
    }
    PCD_StopCrypto1(mfrc); // Detener la encriptación en PCD
    return uidCorrecto;
}
