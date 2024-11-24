#pragma once
#include <vector>
#pragma once
#include <vector>
#include "Map.h"
#include "Enumerations.h"
#include "Player.h"
#include "Drawable.h"

/**
 * @struct RayCastResult
 * @brief Representa el resultado de un c�lculo de raycasting.
 *
 * Contiene informaci�n sobre el punto de impacto del rayo, la textura impactada,
 * y datos necesarios para el c�lculo de proyecci�n y renderizado.
 */
struct RayCastResult : public Drawable {
    Point2D hitCoordinates; /**< Coordenadas del punto de impacto del rayo. */
    float horizontalTextureOffset; /**< Desplazamiento horizontal para aplicar la textura en la pared. */
    int index; /**< �ndice del rayo en la lista de rayos lanzados. */
    WallType wall; /**< Tipo de pared impactada. */
    double cos; /**< Valor del coseno del �ngulo del rayo. */
    double sin; /**< Valor del seno del �ngulo del rayo. */
};

/**
 * @class RayCaster
 * @brief Clase responsable de gestionar el raycasting en el motor del juego.
 *
 * El `RayCaster` calcula trayectorias de rayos desde un origen, detecta colisiones con paredes
 * y proporciona informaci�n necesaria para el renderizado de vistas en primera persona.
 */
class RayCaster {
public:
    /**
     * @brief Realiza un raycasting desde una posici�n espec�fica.
     *
     * Calcula la intersecci�n m�s cercana del rayo con las paredes del mapa en la direcci�n dada.
     *
     * @param angle �ngulo del rayo en radianes.
     * @param position Posici�n inicial desde donde se lanza el rayo.
     * @param map Referencia al mapa donde se realiza el raycasting.
     * @return Una estructura `RayCastResult` con la informaci�n del impacto del rayo.
     */
    RayCastResult rayCast(double angle, Point2D position, Map& map);

    /**
     * @brief Obtiene todos los rayos en un rango de �ngulo.
     *
     * Lanza m�ltiples rayos, calcula sus colisiones y ajusta las profundidades
     * para eliminar distorsi�n por proyecci�n en �ngulo.
     *
     * @param rayAngle �ngulo inicial del rayo en radianes.
     * @param player Referencia al jugador desde donde se lanza el raycasting.
     * @param map Referencia al mapa donde se realiza el raycasting.
     * @return Un vector de `RayCastResult` con informaci�n de cada rayo lanzado.
     */
    std::vector<RayCastResult> getAllRays(double rayAngle, Player player, Map map);

    /**
     * @brief Obtiene el �ngulo entre rayos consecutivos.
     *
     * @return El valor del delta del �ngulo en radianes.
     */
    double getDeltaAngle();

    /**
     * @brief Obtiene el n�mero total de rayos lanzados.
     *
     * @return El n�mero de rayos.
     */
    double getNumRays();

    /**
     * @brief Limpia la lista de rayos almacenados.
     *
     * Vac�a el vector de resultados de raycasting.
     */
    void clearRays();

    /**
     * @brief Constructor parametrizado de `RayCaster`.
     *
     * Inicializa la clase con un n�mero de rayos y un delta de �ngulo espec�fico.
     *
     * @param numRays N�mero total de rayos a lanzar.
     * @param deltaAngle �ngulo entre rayos consecutivos en radianes.
     */
    RayCaster(int numRays, double deltaAngle);

    /**
     * @brief Constructor por defecto de `RayCaster`.
     */
    RayCaster();

private:
    std::vector<RayCastResult> rays; /**< Vector de resultados de raycasting. */
    int numRays; /**< N�mero total de rayos a lanzar. */
    double deltaAngle; /**< �ngulo entre rayos consecutivos en radianes. */

    /**
     * @brief Calcula la intersecci�n m�s cercana en el eje X.
     *
     * Determina la primera celda del mapa en el eje X que intersecta el rayo.
     *
     * @param angle �ngulo del rayo en radianes.
     * @param position Posici�n inicial del rayo.
     * @param xNearestLength Distancia desde la posici�n inicial al punto de impacto en el eje X.
     * @return Coordenadas del punto de impacto en el eje X.
     */
    Point2D calculateXNearest(double angle, Point2D position, double& xNearestLength);

    /**
     * @brief Calcula la intersecci�n m�s cercana en el eje Y.
     *
     * Determina la primera celda del mapa en el eje Y que intersecta el rayo.
     *
     * @param angle �ngulo del rayo en radianes.
     * @param position Posici�n inicial del rayo.
     * @param yNearestLength Distancia desde la posici�n inicial al punto de impacto en el eje Y.
     * @return Coordenadas del punto de impacto en el eje Y.
     */
    Point2D calculateYNearest(double angle, Point2D position, double& yNearestLength);

    /**
     * @brief Calcula el desplazamiento en el eje X entre celdas.
     *
     * Determina el incremento en las coordenadas para avanzar en el eje X.
     *
     * @param angle �ngulo del rayo en radianes.
     * @param xStepLength Longitud del paso en el eje X.
     * @return Desplazamiento en el eje X.
     */
    Point2D calculateXStep(double angle, double& xStepLength);

    /**
     * @brief Calcula el desplazamiento en el eje Y entre celdas.
     *
     * Determina el incremento en las coordenadas para avanzar en el eje Y.
     *
     * @param angle �ngulo del rayo en radianes.
     * @param yStepLength Longitud del paso en el eje Y.
     * @return Desplazamiento en el eje Y.
     */
    Point2D calculateYStep(double angle, double& yStepLength);

    /**
     * @brief Selecciona el punto de impacto m�s cercano entre los ejes X e Y.
     *
     * Compara las intersecciones calculadas en ambos ejes y selecciona el m�s pr�ximo al origen.
     *
     * @param xNearest Resultado del c�lculo de raycasting en el eje X.
     * @param yNearest Resultado del c�lculo de raycasting en el eje Y.
     * @return El `RayCastResult` correspondiente al impacto m�s cercano.
     */
    RayCastResult getShortest(RayCastResult xNearest, RayCastResult yNearest);
};


