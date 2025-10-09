#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>

#include "Medicion.h"

class Sensor{
    public:
        Sensor(const std::string &ruta = "./mios/Mediciones",const bool Persistencia = false);
        ~Sensor();    

        void SetRuta(const std::string &ruta);

        void agregar(Medicion &m);
        
        void mostrar_Medidas();
        
        std::vector<Medicion> &getMedicion();

        void listar();
        // Lista mediciones posteriores a la fechaHora dada (formato "YYYY-MM-DD HH:MM")
        void listar(const std::string &fechaHoraDesde);

        protected:
        std::string ruta;
        std::fstream fs;
        bool Persistencia = false;
        
        std::vector<Medicion> mediciones;
    
};