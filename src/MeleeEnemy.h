#pragma once
#include "Enemy.h"

/**
 * @class MeleeEnemy
 * @brief Representa a un enemigo que ataca cuerpo a cuerpo en el juego.
 *
 * `MeleeEnemy` es una clase derivada de `Enemy` que implementa un comportamiento
 * espec�fico de ataque cuerpo a cuerpo y la respuesta al recibir da�o.
 */
class MeleeEnemy : public Enemy {
public:
    /**
     * @brief Realiza un ataque cuerpo a cuerpo al jugador.
     *
     * Si el jugador est� lo suficientemente cerca (distancia <= 0.5), est� vivo y no est�
     * en estado de "herido", el enemigo realiza un ataque que reproduce un sonido y
     * aplica da�o al jugador.
     */
    void attack() override;

    /**
     * @brief Maneja el da�o recibido por el enemigo.
     *
     * Reduce la vida del enemigo en funci�n del da�o recibido. Si el enemigo sigue con vida,
     * se reproduce un sonido de "herido". Si muere, se reproduce un sonido de "muerte".
     *
     * @param damage Cantidad de da�o recibido.
     */
    void takeDamage(int damage) override;

    /**
     * @brief Constructor de la clase `MeleeEnemy`.
     *
     * @param position Posici�n inicial del enemigo (tipo `Point2D`).
     *
     * Inicializa la posici�n y configura la velocidad del enemigo cuerpo a cuerpo.
     */
    MeleeEnemy(Point2D position);
};
