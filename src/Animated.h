#pragma once
#include "Drawable.h"
/**
 * @class Animated
 * @brief Clase que representa un objeto dibujable con animaciones.
 *
 * La clase `Animated` hereda de `Drawable` y agrega capacidades
 * para manejar m�ltiples animaciones. Cada instancia puede contener
 * una lista de animaciones y un �ndice que indica la animaci�n actual.
 */
class Animated : public Drawable {
public:
    /**
     * @brief �ndice de la animaci�n actualmente activa.
     */
    int animationIndex;

    /**
     * @brief Lista de animaciones asociadas a este objeto.
     */
    std::vector<Animation> animations;
};
