#pragma once
#include <vector>
#include "Item.h"
#include "FileReader.h"

/**
 * @class ItemManager
 * @brief Clase responsable de gestionar los �tems del juego.
 *
 * `ItemManager` se encarga de manejar los �tems disponibles en el juego, organizarlos
 * por niveles, verificar si el jugador recoge un �tem, y gestionar la transici�n entre
 * diferentes listas de �tems. Esta clase sigue el patr�n de dise�o Singleton.
 */
class ItemManager {
public:
    /**
     * @brief Obtiene la lista actual de �tems en el nivel.
     *
     * @return Un puntero a la lista actual de �tems (`std::vector<Item*>`).
     */
    std::vector<Item*>* getCurrentItemList();

    /**
     * @brief Inicializa las listas de �tems desde los archivos de datos.
     *
     * Lee archivos `.csv` en la carpeta de datos y organiza los �tems por niveles.
     * Los datos se cargan en `itemLists`, y la lista del nivel actual se asigna a `currentItems`.
     */
    void initItems();

    /**
     * @brief Limpia la lista actual de �tems.
     *
     * Borra todos los �tems de `currentItems`, dejando la lista vac�a.
     */
    void clearItems();

    /**
     * @brief Verifica si alg�n �tem est� siendo recogido por el jugador.
     *
     * Recorre la lista actual de �tems y comprueba si est�n lo suficientemente cerca
     * del jugador para ser recogidos. Si el jugador recoge un �tem, este se elimina de
     * la lista y su memoria se libera.
     */
    void checkForPickup();

    /**
     * @brief Obtiene el �ndice del nivel actual.
     *
     * @return Un entero representando el �ndice del nivel actual.
     */
    int getCurrentLevel();

    /**
     * @brief Cambia el nivel actual y actualiza la lista de �tems correspondiente.
     *
     * @param level �ndice del nivel al que se desea cambiar.
     *
     * Si el �ndice proporcionado es v�lido, actualiza `currentLevel` y asigna la
     * lista de �tems correspondiente a `currentItems`.
     */
    void setLevel(int level);

    /**
     * @brief Obtiene la instancia �nica de `ItemManager`.
     *
     * @return Un puntero a la instancia �nica de `ItemManager`.
     *
     * Este m�todo implementa el patr�n Singleton para garantizar que solo exista
     * una instancia de `ItemManager` en el juego.
     */
    static ItemManager* getInstance();

private:
    int currentLevel; ///< �ndice del nivel actual.
    std::vector<std::vector<Item*>> itemLists; ///< Listas de �tems organizadas por niveles.
    std::vector<Item*> currentItems; ///< Lista de �tems activos en el nivel actual.
    static ItemManager* instance; ///< Instancia �nica de la clase (Singleton).

    /**
     * @brief Constructor privado de `ItemManager`.
     *
     * Inicializa el nivel actual a 0, carga las listas de �tems desde los datos y
     * asigna la lista del nivel inicial a `currentItems`.
     */
    ItemManager();
};
