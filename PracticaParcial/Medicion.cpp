#include <iostream>
#include <filesystem>
#include <fstream>
#include <cctype>
#include <random>

#include "Medicion.h"

Medicion::Medicion(std::mt19937 &gen){
    this->Medir(gen);
    this->obtenerFechaHoraActual();
}
// Getters
const std::string &Medicion::getFechaHora() const{
    return this->fechaHora;
}

const std::string &Medicion::getUnidad() const{
    return this->unidad;
}

double Medicion::getValor() const{
    return this->valor;
}

void Medicion::obtenerFechaHoraActual() {
    using namespace std::chrono;

    auto ahora = system_clock::now();                // obtiene el tiempo actual
    std::time_t tiempo_actual = system_clock::to_time_t(ahora);

    std::tm tiempo_local = *std::localtime(&tiempo_actual); // convierte a hora local

    std::ostringstream oss;
    oss << std::put_time(&tiempo_local, "%Y-%m-%d %H:%M");  // formato: YYYY-MM-DD HH:MM
    
    this->fechaHora = oss.str();
}

void Medicion::Medir(std::mt19937 &gen){
    double min = 0.0, max = 20.0;
    //static std::random_device rd;           Hay que inicializarlo en el main
    //static std::mt19937 gen(rd());          Hay que inicializarlo en el main
    std::uniform_real_distribution<> dist(min, max);
    this->valor = dist(gen);

    std::uniform_real_distribution<> dist_2(0, 3);
    Unidades u = static_cast<Unidades>(dist_2(gen));

    switch (u)
    {
        case Ampere:
            this->unidad = "Ampere";
        break;
    
        case litros:
            this->unidad = "litros";
        break;

        case Metros:
            this->unidad = "Metros";
        break;
    }
    
}