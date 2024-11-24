#pragma once

/**
 * @class Pickup
 * @brief Clase base abstracta para objetos recogibles en el juego.
 *
 * Esta clase define una interfaz para todos los objetos que pueden ser recogidos
 * por el jugador u otros elementos en el juego.
 */
class Pickup {
public:
    /**
     * @brief M�todo virtual puro para definir la acci�n de recoger el objeto.
     *
     * Este m�todo debe ser implementado por las clases derivadas, especificando
     * el comportamiento cuando el objeto es recogido.
     *
     * @return Un valor booleano que indica si el objeto fue recogido con �xito.
     */
    virtual bool pickup() = 0;
};