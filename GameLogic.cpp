#include "GameLogic.h"
#include <iostream>

void GameLogic::actualizarPersonaje(const std::string& nombreUsuario, const PersonajeData& datos)
{
	

    personajes[nombreUsuario] = datos;
    personajes[nombreUsuario].estado = datos.estado;
    
}

void GameLogic::actualizar(float deltaTime)
{
    // Lógica del juego (colisiones, respawn, etc.)
    for (auto& [nombre, datos] : personajes) {
       
       

        // Ejemplo: Verificar si el personaje está fuera del mapa
        if (datos.posicion.x < 0 || datos.posicion.x > 800 || datos.posicion.y < 0 || datos.posicion.y > 600) {
            datos.posicion = sf::Vector2f(1, 1); // Respawn en el centro
        }
    }
}


