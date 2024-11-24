#pragma once
#include <vector>
#include "Canvas.h"
#include "Map.h"
#include "RayCaster.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "SoundManager.h"

/**
 * @class Game
 * @brief Gestiona el bucle principal del juego y las transiciones de estado.
 *
 * La clase Game se encarga de la inicializaci�n, renderizaci�n y actualizaciones de l�gica
 * para el bucle principal del juego. Tambi�n maneja los estados del juego,
 * transiciones de nivel e interacciones entre los componentes como el jugador,
 * el mapa, los objetos y los enemigos.
 */
class Game {
public:
    /**
     * @brief Inicia el juego entrando en el bucle principal.
     *
     * Inicializa la ventana del juego y comienza a manejar la renderizaci�n
     * y las actualizaciones de l�gica.
     */
    void startGame();

    /**
     * @brief Obtiene el estado actual del juego.
     * @return El valor actual del enum GameState.
     */
    GameState getState();

    /**
     * @brief Construye el objeto Game e inicializa los sistemas principales.
     *
     * Inicializa la ventana del juego, el dispositivo de audio, el gestor de sonidos
     * y los componentes del juego como el mapa y el jugador.
     */
    Game();

private:
    /**
     * @brief Inicializa el juego para el nivel actual.
     *
     * Restablece al jugador, restaura los mapas, inicializa los objetos y enemigos,
     * y configura el nivel actual.
     */
    void initGame();

    /**
     * @brief El bucle principal del juego que maneja la renderizaci�n y las actualizaciones de l�gica.
     *
     * Actualiza continuamente el juego hasta que se cierre la ventana.
     */
    void mainLoop();

    /**
     * @brief Maneja todas las operaciones de renderizaci�n.
     *
     * Dibuja el mapa actual, el jugador, los objetos y los enemigos en el lienzo seg�n el estado del juego.
     */
    void render();

    /**
     * @brief Actualiza la l�gica del juego y las transiciones entre estados.
     *
     * Maneja las acciones del jugador, el comportamiento de los enemigos, la recolecci�n de objetos
     * y las transiciones de estado, como pausar o finalizar el juego.
     */
    void logic();

    /**
     * @brief Reproduce la m�sica de fondo para el nivel actual.
     *
     * Asegura que se reproduzca la banda sonora apropiada seg�n el �ndice del mapa actual.
     */
    void playCurrentSong();

    /**
     * @brief Avanza el juego al siguiente nivel.
     *
     * Actualiza el �ndice del nivel actual, restablece al jugador, inicializa los objetos y enemigos
     * para el nuevo nivel y carga el mapa correspondiente.
     */
    void nextLevel();

    int currentLevel;                 ///< El �ndice del nivel actual.
    Sound currentSong;                ///< La m�sica de fondo actual que se est� reproduciendo.
    Canvas canvas;                    ///< El lienzo de renderizaci�n para el juego.
    Map* map;                         ///< Puntero a la instancia de Map que gestiona los niveles del juego.
    Player* player;                   ///< Puntero a la instancia de Player.
    SoundManager* soundMgr;           ///< Puntero al singleton SoundManager.
    ItemManager* itemManager;         ///< Puntero al singleton ItemManager.
    EnemyManager enemyManager;        ///< Gestiona todas las entidades enemigas en el juego.
    GameState currentState;           ///< El estado actual del juego.
    GameState newState;               ///< El pr�ximo estado al que se transicionar� seg�n la l�gica del juego.
};
