#pragma once
#include <vector>
#include "Map.h"
#include "Item.h"
#include "Enemy.h"

/**
 * @class FileReader.h
 * @brief Declaraci�n de la clase FileReader para manejar la lectura de datos de archivos en el juego.
 *
 * La clase FileReader proporciona funciones est�ticas para cargar datos de archivos externos,
 * incluyendo el mapa, los �tems y los enemigos que se utilizar�n en el juego.
 */

 /**
  * @class FileReader
  * @brief Clase para leer y cargar datos desde archivos.
  *
  * Esta clase contiene m�todos est�ticos que permiten leer el mapa, �tems y enemigos desde
  * archivos externos y cargarlos en estructuras adecuadas para su uso en el juego.
  */
class FileReader {
public:
    /**
     * @brief Lee los datos del mapa desde un archivo y los carga en una matriz 2D.
     *
     * @param fileName Nombre del archivo que contiene los datos del mapa.
     * @param map Matriz bidimensional donde se almacenar� el mapa.
     * @return `true` si el archivo se ley� correctamente, `false` si ocurri� un error.
     *
     * El archivo debe contener valores separados por comas, donde cada valor representa
     * un tipo de pared definido por la enumeraci�n `WallType`.
     */
    static bool readMapFromFile(const char* fileName, WallType** map);

    /**
     * @brief Lee los datos de los �tems desde un archivo y los carga en una lista.
     *
     * @param fileName Nombre del archivo que contiene los datos de los �tems.
     * @param itemList Vector donde se almacenar�n los �tems instanciados.
     * @return `true` si el archivo se ley� correctamente, `false` si ocurri� un error.
     *
     * El archivo debe contener l�neas con los datos de cada �tem en el formato:
     * `ItemType,posici�nX,posici�nY`. Se instanciar� un �tem basado en su tipo
     * y se a�adir� a la lista proporcionada.
     */
    static bool readItemsFromFile(const char* fileName, std::vector<Item*>& itemList);

    /**
     * @brief Lee los datos de los enemigos desde un archivo y los carga en una lista.
     *
     * @param fileName Nombre del archivo que contiene los datos de los enemigos.
     * @param enemyList Vector donde se almacenar�n los enemigos instanciados.
     * @return `true` si el archivo se ley� correctamente, `false` si ocurri� un error.
     *
     * El archivo debe contener l�neas con los datos de cada enemigo en el formato:
     * `EnemyType,posici�nX,posici�nY`. Se instanciar� un enemigo basado en su tipo
     * y se a�adir� a la lista proporcionada.
     */
    static bool readEnemiesFromFile(const char* fileName, std::vector<Enemy*>& enemyList);
};
