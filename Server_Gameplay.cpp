#include "Server_Gameplay.h"




Server_Gameplay::Server_Gameplay(unsigned short port){

    //sf::IpAddress ipServidorGameplay = sf::IpAddress::Any; // Escucha en cualquier IP
    //if (socket.bind(55000, ipServidorGameplay) != sf::Socket::Status::Done) {
    //    std::cerr << "Error al iniciar Servidor_Gameplay en el puerto 55000" << std::endl;
    //}

    if (socket.bind(port) != sf::Socket::Status::Done) { //-LOCALHOST
        std::cerr << "Error al iniciar Servidor_Gameplay en el puerto " << port << std::endl;
    }

    std::cerr << " Servidor_Gameplay iniciado en el puerto " << port << std::endl;

}


void Server_Gameplay::iniciar()
{
    sf::Clock reloj;

    while (true) {

        sf::Packet packet;
        
        std::optional<sf::IpAddress> ip;
        unsigned short port;
        float deltaTime = reloj.restart().asSeconds();

        // Recibir paquetes de los clientes
        if (socket.receive(packet, ip, port) != sf::Socket::Status::Done) {
            continue;
        }

        std::string mensaje;
        std::string modo;
        std::string nombre;
        float posX, posY;
        int estado;

        if (!(packet >> mensaje)) {
            continue;
        }

       

            if (mensaje.find("CONNECTED:") == 0) {
                // Nuevo cliente conectado
                std::string nombreUsuario = mensaje.substr(10);
                clientes[nombreUsuario] = std::make_pair(ip.value(), port);

                std::cout << "Cliente conectado: " << nombreUsuario << " (" << ip.value() << ":" << port << ")" << std::endl;


                // Inicializar datos del personaje
                PersonajeData datos;
                datos.posicion = sf::Vector2f(1.0f,1.0f); // Posición inicial
                datos.estado = 0; // Estado inicial: idle
                datos.vidas = 3;
                datos.salud = 5;

                gameLogic.actualizarPersonaje(nombreUsuario, datos);

            }
            else if(mensaje.find("UPDATE:") == 0) {
                if (!(packet >> nombre >> posX >> posY >> estado)) {
                    continue;
                }
                
                // Manejar otros mensajes del cliente
                manejarPaquete(mensaje,nombre,posX,posY,estado, ip.value(), port);

            }



        

    }
}

void Server_Gameplay::manejarPaquete(const std::string& mensaje, const std::string& nombre, float _posX, float _posY, int _estado, sf::IpAddress ip, unsigned short port)
{

            // Actualizar el personaje en el servidor
            if (clientes.find(nombre) != clientes.end()) {
                
                clientes[nombre].first = ip;
                PersonajeData datos;
                
                datos.posicion = sf::Vector2f({ _posX, _posY });
                datos.estado = _estado;
                datos.vidas = 5; // Valor predeterminado
                datos.salud = 3; // Valor predeterminado
                gameLogic.actualizarPersonaje(nombre, datos);
                
            }
            else {
                std::cerr << "Error: El personaje " << nombre << " no está registrado en el servidor." << std::endl;
            }
        
        

    // Enviar datos actualizados a todos los clientes


            for (const auto& [clienteNombre, clienteDatos] : clientes) {
                if (clienteNombre != nombre) { // Enviar solo al rival
                   
                    sf::Packet respuesta;

                    respuesta << "UPDATE" << nombre << _posX << _posY << _estado;
                   

                    if (clienteDatos.first.has_value()) {
                        socket.send(respuesta, clienteDatos.first.value(), clienteDatos.second) != sf::Socket::Status::Done;
                        
                        
                    }
                    
                }
            }

}




