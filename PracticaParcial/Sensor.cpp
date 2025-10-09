#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <ctime>

#include "Medicion.h"
#include "Sensor.h"


Sensor::Sensor(const std::string &ruta, const bool Persistencia){
    this->ruta = ruta;
    this->Persistencia = Persistencia;
    this->mediciones.clear();
}

Sensor::~Sensor(){
    if(Persistencia){
        if(fs.is_open()){
            fs.close();
        }
    }
}

void Sensor::SetRuta(const std::string &ruta){
    this->ruta = ruta;
    this->Persistencia = true;

}

//=======================================================================================================
//=======================================================================================================
void Sensor::mostrar_Medidas(){

    for(int i=0; i<mediciones.size() ;i++){
        std::cout << mediciones[i].getFechaHora();
        std::cout << "   " << mediciones[i].getValor();
        std::cout << " [" << mediciones[i].getUnidad() << "]";

        std::cout << std::endl;
    }
}

std::vector<Medicion>& Sensor::getMedicion(){
    
    return this->mediciones;
}

void Sensor::agregar(Medicion &m){
    this->mediciones.push_back(m);
}

void Sensor::listar(){
    if(mediciones.empty()){
        std::cout << "No hay mediciones registradas." << std::endl;
        return;
    }

    for(const auto &m : mediciones){
        std::cout << "FechaHora: " << m.getFechaHora()
                  << " | Valor: " << m.getValor()
                  << " | Unidad: " << m.getUnidad() << std::endl;
    }
}
// Helper: parse YYYY-MM-DD HH:MM into std::tm. Returns true on success.
static bool parseFechaHora(const std::string &s, std::tm &out_tm){
    if(s.size() < 16) return false;
    std::istringstream iss(s);
    iss >> std::get_time(&out_tm, "%Y-%m-%d %H:%M");
    if (iss.fail()) return false;
    // Ensure seconds and daylight flag are set for mktime
    out_tm.tm_sec = 0;
    out_tm.tm_isdst = -1; // let mktime determine DST
    return true;
}

void Sensor::listar(const std::string &fechaHoraDesde){
    std::tm tmDesde{};
    if(!parseFechaHora(fechaHoraDesde, tmDesde)){
        std::cerr << "Formato de fecha inválido. Use YYYY-MM-DD HH:MM\n";
        return;
    }

    bool found = false;
    for(const auto &m : mediciones){
        const std::string &fh = m.getFechaHora();
        std::tm tmMed{};
        if(!parseFechaHora(fh, tmMed)) continue; // saltar si no se puede parsear

        std::time_t tDesde = std::mktime(&tmDesde);
        std::time_t tMed = std::mktime(&tmMed);

        if(tMed > tDesde){
            found = true;
            std::cout << "FechaHora: " << m.getFechaHora()
                      << " | Valor: " << m.getValor()
                      << " | Unidad: " << m.getUnidad() << std::endl;
        }
    }

    if(!found){
        std::cout << "No se encontraron mediciones posteriores a " << fechaHoraDesde << std::endl;
    }
}
