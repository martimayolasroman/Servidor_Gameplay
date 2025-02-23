#pragma once

#include <SFML/System/Vector2.hpp>
#include <map>
#include <string>

struct PersonajeData {

    sf::Vector2f posicion;
    int estado; // 0 = idle, 1 = caminando, 2 = saltando, 3 = disparando
    int vidas;
    int salud;
    
};

class GameLogic
{
public:

    void actualizarPersonaje(const std::string& nombreUsuario, const PersonajeData& datos);
    void actualizar(float deltaTime);

    std::map<std::string, PersonajeData> personajes; // Almacenar datos de los personajes



};

