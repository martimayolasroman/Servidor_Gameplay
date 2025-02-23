#pragma once
#include <SFML/Network.hpp>
#include <thread>
#include <iostream>
#include "GameLogic.h"

class Server_Gameplay {
public:

  
    
    Server_Gameplay(unsigned short port);// Inicializa el servidor
    void iniciar(); // Inicia el servidor y maneja conexiones entrantes
    void manejarPaquete(const std::string& mensaje, const std::string& nombre, float posX, float posY, int estado, sf::IpAddress ip, unsigned short port);// Procesa los paquetes de los clientes
    std::map<std::string, std::pair<std::optional<sf::IpAddress>, unsigned short>> clientes; // Almacenar clientes conectados

    GameLogic gameLogic;

    
    sf::UdpSocket socket;
  
   
   

};