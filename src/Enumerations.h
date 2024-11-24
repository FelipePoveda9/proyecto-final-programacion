#pragma once

/**
 * @file Enumerations.h
 * @brief Contiene las enumeraciones usadas en el juego.
 *
 * Este archivo define varios tipos enumerados que representan elementos importantes
 * dentro del juego, como tipos de paredes, �tems, enemigos y estados del juego.
 */

 /**
  * @enum WallType
  * @brief Representa los diferentes tipos de paredes disponibles en el juego.
  *
  * Cada valor corresponde a un tipo espec�fico de pared, usado para definir el dise�o del mapa.
  */
enum WallType {
	none = 0,        /**< No hay pared (espacio vac�o). */
	brick = 1,       /**< Pared de ladrillo. */
	stone = 2,       /**< Pared de piedra. */
	mossyStone = 3,  /**< Pared de piedra con musgo. */
	closedDoor = 4,  /**< Puerta cerrada. */
	openDoor = 6,    /**< Puerta abierta. */
};

/**
 * @enum ItemType
 * @brief Representa los diferentes tipos de �tems que el jugador puede recoger.
 *
 * Define qu� tipo de beneficio o efecto tienen los �tems en el juego.
 */
enum ItemType {
	invalid = 0, /**< �tem no v�lido o inexistente. */
	health = 1,  /**< �tem que restaura la salud del jugador. */
	ammo = 2,    /**< �tem que proporciona munici�n. */
	lamp = 3,    /**< �tem que mejora la iluminaci�n del entorno. */
};

/**
 * @enum EnemyType
 * @brief Representa los tipos de enemigos en el juego.
 *
 * Define el comportamiento base de los enemigos seg�n su tipo de ataque.
 */
enum EnemyType {
	melee = 1, /**< Enemigo que ataca cuerpo a cuerpo. */
	range = 2, /**< Enemigo que ataca a distancia. */
};

/**
 * @enum GameState
 * @brief Representa los posibles estados del juego.
 *
 * Se utiliza para controlar la l�gica y flujo del juego en diferentes momentos.
 */
enum GameState {
	mainMenu = 0,   /**< Estado del men� principal. */
	playing = 1,    /**< Estado cuando el juego est� en curso. */
	gameOver = 2,   /**< Estado cuando el juego ha terminado. */
	pause = 3,      /**< Estado de pausa. */
	options = 4,    /**< Estado para acceder a las opciones del juego. */
	na = 5,         /**< Estado no definido. */
	end = 6,        /**< Estado del final del juego. */
	transition = 7, /**< Estado de transici�n entre niveles o escenas. */
};
