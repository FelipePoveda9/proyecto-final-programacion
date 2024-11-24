#pragma once
#include <raylib.h>
#include <string>
#include <map>

/**
 * @class SoundManager
 * @brief Clase singleton para gestionar los sonidos del juego.
 *
 * La clase se encarga de cargar, almacenar y proporcionar acceso a los recursos de sonido.
 */
class SoundManager {
public:
    /**
     * @brief Obtiene un sonido espec�fico del listado cargado.
     *
     * Busca un archivo de sonido en el mapa cargado y lo retorna.
     * Si el archivo no existe en el mapa, no se garantiza un comportamiento v�lido.
     *
     * @param fileName Nombre del archivo de sonido a buscar.
     * @return El objeto `Sound` asociado al archivo especificado.
     */
    Sound getSound(std::string fileName);

    /**
     * @brief Carga todos los sonidos desde el directorio de sonidos.
     *
     * Itera sobre los archivos en el directorio de sonidos configurado y
     * carga cada archivo v�lido en el mapa de sonidos.
     */
    void loadSounds();

    /**
     * @brief Obtiene la instancia �nica de la clase `SoundManager`.
     *
     * Implementa el patr�n singleton, garantizando que solo exista una instancia de la clase.
     *
     * @return Puntero a la instancia �nica de `SoundManager`.
     */
    static SoundManager* getInstance();

private:
    std::map<std::string, Sound>* soundList; /**< Mapa que almacena los sonidos cargados, con sus rutas como clave. */
    static SoundManager* instance; /**< Instancia �nica de la clase `SoundManager`. */

    /**
     * @brief Obtiene la ruta del directorio donde est�n almacenados los sonidos.
     *
     * Define y retorna el directorio predeterminado de sonidos.
     *
     * @return Una cadena de texto con la ruta del directorio de sonidos.
     */
    std::string getSoundsDir();

    /**
     * @brief Constructor privado del `SoundManager`.
     *
     * Inicializa la estructura interna para almacenar los sonidos.
     * Este constructor es privado para implementar el patr�n singleton.
     */
    SoundManager();
};
