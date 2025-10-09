#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <random>
#include <sstream>

#include "Sensor.h"
#include "Medicion.h"

int main(int argc, char* argv[]){
    Sensor m_sensor;

    static std::random_device rd; 
    static std::mt19937 gen(rd()); 
    if (argc <= 1) {
        // Modo interactivo (REPL). Permite ejecutar múltiples comandos manteniendo el vector en RAM.
        std::cout << "Modo interactivo. Escriba 'help' para ver comandos. 'salir' para terminar." << std::endl;
        std::string line;
        while (true) {
            std::cout << ">> ";
            if (!std::getline(std::cin, line)) break; // EOF
            // Trim leading/trailing spaces
            auto l = line.find_first_not_of(" \t\r\n");
            if (l == std::string::npos) continue;
            auto r = line.find_last_not_of(" \t\r\n");
            std::string cmdline = line.substr(l, r - l + 1);

            std::istringstream iss(cmdline);
            std::string cmd;
            iss >> cmd;
            if (cmd == "salir" || cmd == "exit") break;
            if (cmd == "help"){
                std::cout << "Comandos disponibles:\n  help\n  tiempo <YYYY-MM-DD HH:MM>\n  todo\n  agregar <n>\n  salir\n";
                continue;
            }
            if (cmd == "tiempo"){
                std::string fecha;
                std::getline(iss, fecha);
                // eliminar espacios iniciales
                auto p = fecha.find_first_not_of(' ');
                if (p != std::string::npos) fecha = fecha.substr(p);
                if (fecha.empty()){
                    std::cerr << "Falta la fecha. Uso: tiempo YYYY-MM-DD HH:MM\n";
                    continue;
                }
                m_sensor.listar(fecha);
                continue;
            }
            if (cmd == "todo"){
                m_sensor.listar();
                continue;
            }
            if (cmd == "agregar"){
                int n = 1;
                if (!(iss >> n)) n = 1;
                for (int i = 0; i < n; ++i){
                    Medicion m(gen);
                    m_sensor.agregar(m);
                }
                std::cout << "Agregadas " << n << " mediciones.\n";
                continue;
            }
            // Si el comando es un número, agregar esa cantidad de mediciones
            try {
                int n = std::stoi(cmd);
                for (int i = 0; i < n; ++i){
                    Medicion m(gen);
                    m_sensor.agregar(m);
                }
                std::cout << "Agregadas " << n << " mediciones.\n";
                continue;
            } catch (...) {
                std::cerr << "Comando no reconocido. Escriba 'help'.\n";
                continue;
            }
        }
        return 0;
    }

    std::string cmd = argv[1];

    if (cmd == "help"){
        std::cout << "si ingresa : 'tiempo YYYY-MM-DD HH:MM', va a obtener las mediciones posteriores a la fecha" << std::endl;
        std::cout << std::endl;

        std::cout << "si ingresa : 'todo' obtendra todas las mediciones hasta el momento" << std::endl;
        std::cout << std::endl;

        std::cout << "si ingresa un numero entero va a obtener esa cantidad de mediciones (ultimas n)" << std::endl;
        std::cout << std::endl;
        return 0;
    }

    if (cmd == "tiempo"){
        if (argc < 3){
            std::cerr << "Falta la fecha. Uso: parcialPractica tiempo \"YYYY-MM-DD HH:MM\"\n";
            return 1;
        }
        // Unir argv[2..] para permitir fecha con espacio
        std::string tiempo_M;
        for (int i = 2; i < argc; ++i){
            if (i > 2) tiempo_M += ' ';
            tiempo_M += argv[i];
        }
        m_sensor.listar(tiempo_M);
        return 0;
    }

    if (cmd == "todo"){
        m_sensor.mostrar_Medidas();
        return 0;
    }

    // Try to convert argv[1] to int and check if it's a valid integer
    try {
        int n = std::stoi(cmd);
        Medicion m(gen);
        for (int i=0; i<n; i++){
            m.Medir(gen);
            m_sensor.agregar(m);
        }
        m_sensor.mostrar_Medidas();
    } catch (const std::exception&) {
        std::cerr << "Comando no reconocido. Use 'help' para ver usos disponibles." << std::endl;
    }

    return 0;
}