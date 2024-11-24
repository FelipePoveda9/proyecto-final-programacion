#pragma once
#include "Player.h"
#include "Point2D.h"
#include "Enumerations.h"
#include "Drawable.h"

/**
 * @class Item
 * @brief Clase base para los elementos del juego interactuables.
 *
 * La clase `Item` define los elementos b�sicos de un objeto en el juego,
 * como su posici�n y sprite asociado. Est� pensada para ser una clase base
 * que puede ser heredada por otros objetos m�s espec�ficos, como HealthBox.
 */
class Item {
public:
    Point2D position; ///< Posici�n del objeto en el espacio 2D.
    Drawable* sprite; ///< Sprite asociado para representar el objeto gr�ficamente.

    /**
     * @brief Constructor por defecto de la clase Item.
     *
     * Inicializa un objeto `Item` con posici�n predeterminada y sin sprite asociado.
     */
    Item();

    /**
     * @brief Constructor parametrizado de la clase Item.
     *
     * @param position Posici�n inicial del objeto (tipo Point2D).
     *
     * Inicializa un objeto `Item` con la posici�n especificada y sin sprite asociado.
     */
    Item(Point2D position);

    /**
     * @brief Destructor virtual por defecto.
     *
     * Permite la correcta destrucci�n de los objetos derivados de esta clase.
     */
    virtual ~Item() = default;

private:
};
