#pragma once

#include <vector>
#include "Enemy.h"

/**
 * @class EnemyManager
 * @brief Administra la l�gica y el comportamiento de los enemigos en el juego.
 *
 * La clase `EnemyManager` se encarga de manejar una lista de enemigos,
 * inicializarlos, gestionar su comportamiento, aplicar da�o y verificar su estado.
 */
class EnemyManager {
public:
    /**
     * @brief Obtiene la lista de enemigos actuales.
     *
     * @return Un puntero a un vector de enemigos (`Enemy*`).
     */
    std::vector<Enemy*>* getEnemyList();

    /**
     * @brief Inicializa los enemigos en el nivel actual.
     *
     * Este m�todo crea nuevos enemigos bas�ndose en objetos del nivel,
     * asign�ndoles sprites y animaciones espec�ficas seg�n su tipo.
     */
    void initEnemies();

    /**
     * @brief Limpia la lista de enemigos.
     *
     * Libera la memoria asignada para los enemigos actuales y vac�a la lista.
     */
    void clearEnemies();

    /**
     * @brief Ejecuta el comportamiento de todos los enemigos.
     *
     * Este m�todo actualiza el estado de cada enemigo en la lista, aplica da�o
     * cuando sea necesario y actualiza sus animaciones.
     *
     * @param player Referencia al jugador.
     * @param map Mapa del nivel actual.
     */
    void runEnemyBehaviour(Player& player, Map map);

    /**
     * @brief Verifica si todos los enemigos est�n muertos.
     *
     * @return `true` si todos los enemigos est�n muertos, `false` en caso contrario.
     */
    bool areEnemiesDead();

private:
    /**
     * @brief Aplica da�o a un enemigo, si corresponde.
     *
     * Este m�todo determina si un enemigo puede recibir da�o basado en
     * la posici�n, distancia y el estado del jugador (si dispar� recientemente).
     *
     * @param enemy Puntero al enemigo que podr�a recibir da�o.
     * @param player Referencia al jugador.
     * @param map Mapa del nivel actual.
     */
    void damageEnemy(Enemy* enemy, Player player, Map map);

    /**
     * @brief Actualiza el estado visual del enemigo.
     *
     * Cambia la animaci�n del enemigo seg�n su estado actual:
     * - Animaci�n de herido si est� herido.
     * - Animaci�n de muerte si est� muerto.
     * - Animaci�n de caminar si est� vivo y saludable.
     *
     * @param enemy Puntero al enemigo cuyo estado se actualizar�.
     */
    void setEnemyState(Enemy* enemy);

    /**
     * @brief Lista de enemigos actuales en el nivel.
     */
    std::vector<Enemy*> enemyList;
};
