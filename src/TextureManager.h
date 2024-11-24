#pragma once
#include <raylib.h>
#include <map>
#include <string>

/**
 * @class TextureManager
 * @brief Clase para gestionar la carga, almacenamiento y acceso a texturas.
 *
 * TextureManager es una clase singleton dise�ada para manejar la gesti�n de texturas
 * en memoria de video (VRAM) en un entorno de juego. Proporciona m�todos para cargar
 * texturas desde directorios espec�ficos y acceder a ellas mediante rutas de archivo.
 */
class TextureManager {
public:
    /**
     * @brief Obtiene una textura almacenada en el gestor.
     *
     * Si la textura especificada no est� disponible, devuelve una textura de error.
     * @param fileName Nombre del archivo de la textura relativa al directorio base.
     * @return La textura correspondiente al archivo solicitado.
     */
    Texture getTexture(std::string fileName);

    /**
     * @brief Carga todas las texturas en VRAM desde los directorios predefinidos.
     *
     * Busca texturas en carpetas como "walls", "sprites/static", "sprites/animated",
     * y "backgrounds" dentro del directorio base. Las texturas se almacenan en un mapa
     * para acceso r�pido por su ruta.
     */
    void loadTexturesToVRAM();

    /**
     * @brief Obtiene la instancia �nica de la clase TextureManager.
     *
     * Implementa el patr�n Singleton para garantizar que solo exista
     * una instancia de TextureManager durante la ejecuci�n del programa.
     * @return Puntero a la instancia �nica de TextureManager.
     */
    static TextureManager* getInstance();

private:
    /**
     * @brief Constructor privado.
     *
     * Crea una instancia de TextureManager. Este constructor es privado
     * para cumplir con los requisitos del patr�n Singleton.
     */
    TextureManager();

    /**
     * @brief Obtiene el directorio base de texturas.
     *
     * Devuelve la ruta base donde se almacenan las texturas en el sistema.
     * Esta ruta se utiliza como punto de partida para buscar subdirectorios.
     * @return La ruta base de texturas.
     */
    std::string getTextureDir();

    static TextureManager* instance; ///< Instancia �nica de la clase (Singleton).
    std::map<std::string, Texture>* textures; ///< Mapa para almacenar texturas cargadas por ruta.
};
