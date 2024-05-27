#ifndef __Sensor_rfid_
#define __Sensor_rfid_

/**brief: Lectura de un bloque de información de la tarjeta
 * 
 * @param mfrc: Puntero que apunta al MFRC522
 * @param bloque: Bloque de la información que se va a leer
 * @param info: Grupo de información almacenada luego de leer
 * 
 * @return void: no hay salidas.
 */
void LeerBloque(MFRC522Ptr_t mfrc,uint8_t bloque,uint8_t info[18]);

/**brief: Escritura de un bloque de la tarjeta
 * 
 * @param mfrc: Puntero que apunta al MFRC522
 * @param bloque: Bloque de la información que se va a leer
 * @param info: Grupo de información almacenada luego de leer
 * 
 * @return void
 */
void EscribeBloque(MFRC522Ptr_t mfrc, uint8_t bloque, uint8_t info[16]);


/**brief: Funcion que comprueba que se tiene una identificación correcta
 * 
 * @param entrada: UID recibido
 * @param longitudEntrada: Longitud del UID recibido
 * @param esperado: UID esperado
 * @param longitudEsperado: Longitud del UID esperado
 * 
 * @return bool: 1 si coinciden y cero si no
 */
bool VerificaciónUID(const uint8_t *entrada, size_t longitudEntrada, const uint8_t *esperado, size_t longitudEsperado);


bool LeerTarjeta(MFRC522Ptr_t mfrc);

#endif