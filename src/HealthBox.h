#pragma once
#include "Item.h"
#include "Pickup.h"

/**
 * @class HealthBox
 * @brief Representa un objeto que otorga puntos de curaci�n al jugador.
 *
 * La clase `HealthBox` es un tipo especial de �tem que, al ser recogido,
 * incrementa la salud del jugador. Hereda de las clases `Item` y `Pickup`.
 */
class HealthBox : public Item, public Pickup {
public:
    int healingPoints; ///< Puntos de curaci�n que otorga el HealthBox.

    /**
     * @brief Constructor de la clase HealthBox.
     *
     * @param pos Posici�n del HealthBox en el espacio (tipo Point2D).
     *
     * Crea un nuevo objeto `HealthBox` con una posici�n inicial y establece
     * por defecto los puntos de curaci�n a 30.
     */
    HealthBox(Point2D pos);

    /**
     * @brief M�todo que recoge el HealthBox y cura al jugador.
     *
     * @return true si el objeto se us� correctamente, false en caso contrario.
     *
     * Este m�todo interact�a con la clase `Player` para incrementar la salud
     * del jugador en funci�n de los puntos de curaci�n (`healingPoints`).
     */
    bool pickup() override;
};
