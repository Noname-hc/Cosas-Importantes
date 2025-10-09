#include <cstring>
#include <iostream>
#include <vector>
#include <variant>
#include <fstream>
#include <algorithm>

#include "File_P.h"

int main() {

//=========================================================================================================
    File_P archivo;

    // Ruta
    archivo.set_fs("./datos.txt", "w"); 
    archivo.set_FileType('c');
    

    // Preguntar si se quiere reescribir
    std::string comando;
    std::cout << "\n¿Quieres reescribir alguna linea? (s/n) (una sola): " << std::endl;
    getline(std::cin, comando);

    if (comando == "S" || comando == "s") {
        std::string reemplazo;
        int linea;

        std::cout << "Escribe la nueva frase: ";
        std::getline(std::cin, reemplazo);

        std::cout << "¿En qué número de línea quieres reemplazar?: ";
        std::cin >> linea;

        archivo.Reescribir_Linea(reemplazo, linea);

        // Volver a leer archivo para mostrar resultado
        std::cout << "\nContenido del archivo despues de reescribir:" << std::endl;
        archivo.Leer_Archivo();
    } else {
        std::cout << "¿quieres escribir al final del archivo? (S/n) (muchas lineas)" << std::endl;
        std::getline(std::cin, comando);

        if(comando == "s" || comando == "S"){
            archivo.EscribirArchivo();
            
            std::cout << "Archivo:" << std::endl;
            archivo.Leer_Archivo();
        }
        

        std::cout << "¿quieres leer un formato en especifico de archivo? (S/n)" << std::endl;
        std::cin >> comando;

        if(comando == "S" || comando == "s"){
            std::cout << "¿de que tipo? (c, x o j)" << std::endl;
            std::cin >> comando;

            archivo.set_FileType(*comando.c_str());
            archivo.Leer_Tipo_De_Archivo('x');
        }

    }
    return 0;
}