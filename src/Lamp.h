#pragma once
#include "Item.h"

/**
 * @class Lamp
 * @brief Representa una l�mpara en el juego.
 *
 * La clase `Lamp` es un objeto derivado de `Item` que representa una l�mpara
 * con una posici�n espec�fica y un color asociado. Es �til para agregar elementos
 * visuales o interactivos al juego.
 */
class Lamp : public Item {
public:
    int LampColor; ///< Color de la l�mpara representado como un entero.

    /**
     * @brief Constructor de la clase Lamp.
     *
     * @param pos Posici�n inicial de la l�mpara en el espacio (tipo Point2D).
     *
     * Inicializa una l�mpara con una posici�n especificada. El color de la l�mpara
     * debe ser configurado posteriormente.
     */
    Lamp(Point2D pos);
};
