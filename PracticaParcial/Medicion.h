#ifndef MEDICION
#define MEDICION

#include <iostream>
#include <random>
#include <string>

enum Unidades {Ampere = 0, Metros, litros};

class Medicion{
    public:
        Medicion(std::mt19937 &gen);
        void obtenerFechaHoraActual();
        void Medir(std::mt19937 &gen);
        
        // Getters
        const std::string &getFechaHora() const;
        const std::string &getUnidad() const;
        double getValor() const;


    private:
        std::string fechaHora;
        std::string unidad;
        double valor;

};

#endif
