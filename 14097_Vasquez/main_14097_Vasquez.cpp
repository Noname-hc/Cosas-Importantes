#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "Chapa.h"
#include "Pieza.h"

int main(int argc, char* argv[]){
    if(argc > 1){
        std::string a = argv[1];
        if(a == "help"){
            std::cout << "Uso: parcial_Vasquez" << std::endl;
            std::cout << "  El programa permite ingresar piezas (circulo, rectangulo, triangulo) con dimensiones en mm." << std::endl;
            std::cout << "  Tras cada ingreso muestra la superficie de la pieza y el porcentaje de ocupacion y el porcentaje restante." << std::endl;
            std::cout << "  Ingrese 'stop' para terminar antes de alcanzar el 75% de ocupacion." << std::endl;
            return 0;
        }
    }
    Chapa chapa; // unica instancia
    double superficieChapa = chapa.getSuperficie(); // mm^2

    std::vector<Pieza> piezas;
    double superficieOcupada = 0.0;

    std::cout << "Superficie de la chapa: " << superficieChapa << " (mm^2)" << std::endl;

    int nextId = 1;
    while(true){
        std::cout << "Ingrese tipo de pieza (circulo, rectangulo, triangulo) o 'stop' para terminar: ";
        std::string tipo;
        if(!std::getline(std::cin, tipo)) break;
        if(tipo.empty()) continue;
        for(auto &c: tipo) c = std::tolower((unsigned char)c);
        if(tipo == "stop") break;

        TipoPieza t;
        if(tipo == "circulo") t = TipoPieza::CIRCULO;
        else if(tipo == "rectangulo") t = TipoPieza::RECTANGULO;
        else if(tipo == "triangulo") t = TipoPieza::TRIANGULO;
        else {
            std::cout << "Tipo desconocido. Intente nuevamente." << std::endl;
            continue;
        }

        Pieza p(nextId++, t);
        if(t == TipoPieza::CIRCULO){
            std::cout << "Ingrese radio (mm): "; double r; std::cin >> r; p.setDimensiones(r); 
        } else if(t == TipoPieza::RECTANGULO){
            std::cout << "Ingrese largo (mm): "; double a; std::cin >> a;
            std::cout << "Ingrese ancho (mm): "; double b; std::cin >> b;
            p.setDimensiones(a,b);
        } else if(t == TipoPieza::TRIANGULO){
            std::cout << "Ingrese lado (mm): "; double L; std::cin >> L; p.setDimensiones(L);
        }

        // consumir el newline restante
        std::string dummy; std::getline(std::cin, dummy);

        double supP = p.getSuperficie();
        superficieOcupada += supP;
        piezas.push_back(p);

    double porcentaje = (superficieOcupada / superficieChapa) * 100.0;
    double restante = 100.0 - porcentaje;
    std::cout << "Pieza agregada. Superficie pieza: " << supP << " mm^2. Porcentaje de ocupacion: " << std::fixed << std::setprecision(2) << porcentaje << "%";
    std::cout << " | Porcentaje restante: " << restante << "%" << std::endl;

        if(porcentaje > 75.0){
            std::cout << "La ocupacion de la chapa supero el 75%. Terminando." << std::endl;
            break;
        }
    }

    // Reporte final encolumnado
    std::cout << "\nReporte de piezas ingresadas:\n";
    std::cout << std::left << std::setw(6) << "ID" << std::setw(15) << "Tipo" << std::setw(18) << "Superficie(mm^2)" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    for(const auto &pp : piezas){
        std::string tipoStr = (pp.getTipo() == TipoPieza::CIRCULO)?"Circulo":(pp.getTipo()==TipoPieza::RECTANGULO?"Rectangulo":"Triangulo");
        std::cout << std::left << std::setw(6) << pp.getId() << std::setw(15) << tipoStr << std::setw(18) << std::fixed << std::setprecision(2) << pp.getSuperficie() << std::endl;
    }

    double porcentajeFinal = (superficieOcupada / superficieChapa) * 100.0;
    std::cout << std::string(40, '-') << std::endl;
    std::cout << "Cantidad de piezas: " << piezas.size() << std::endl;
    std::cout << "Superficie total ocupada: " << superficieOcupada << " mm^2" << std::endl;
    std::cout << "Porcentaje disponible en la chapa: " << std::fixed << std::setprecision(2) << (100.0 - porcentajeFinal) << "%" << std::endl;

    return 0;
}
