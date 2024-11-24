#pragma once
#include "Point2D.h"
#include "Animated.h"

/**
 * @class Projectile
 * @brief Representa un proyectil en el juego, con capacidades de movimiento, colisi�n y da�o.
 *
 * La clase `Projectile` gestiona las propiedades y el comportamiento de los proyectiles
 * en el juego, incluyendo su posici�n, velocidad, trayectoria, y colisiones con objetos
 * como el jugador y las paredes.
 */
class Projectile {
public:
    /**
     * @brief Constructor de la clase Projectile.
     *
     * @param pos La posici�n inicial del proyectil.
     * @param ang El �ngulo de movimiento del proyectil en radianes.
     * @param damage La cantidad de da�o que inflige el proyectil al impactar.
     */
    Projectile(Point2D pos, double ang, int damage);

    /**
     * @brief Maneja el movimiento del proyectil y verifica colisiones.
     *
     * Este m�todo actualiza la posici�n del proyectil y detecta si ha colisionado
     * con el jugador, una pared o si ha excedido su tiempo l�mite.
     *
     * @return `true` si el proyectil colisiona o expira; `false` en caso contrario.
     */
    bool shoot();

    /**
     * @brief Obtiene la posici�n actual del proyectil.
     *
     * @return La posici�n actual como un objeto `Point2D`.
     */
    Point2D getPosition();

    /**
     * @brief Sprite animado que representa al proyectil.
     *
     * Este sprite contiene las animaciones visuales del proyectil.
     */
    Animated* sprite;

private:
    int damage;             /**< Da�o que inflige el proyectil al impactar. */
    double timeLimit;       /**< Tiempo m�ximo de vida del proyectil en segundos. */
    double timer;           /**< Temporizador que mide el tiempo de existencia del proyectil. */
    double speed;           /**< Velocidad de movimiento del proyectil. */
    double angle;           /**< �ngulo de movimiento del proyectil en radianes. */
    Point2D position;       /**< Posici�n actual del proyectil. */
};
