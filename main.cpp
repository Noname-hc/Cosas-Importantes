#include <iostream>
#include "File_P.h"

int main() {
    File_P archivo;

    // Ruta
    archivo.set_fs("./datos.txt", "w"); 
    archivo.set_FileType('c');

    // Preguntar si se quiere reescribir
    std::string comando;
    std::cout << "\n¿Quieres reescribir alguna linea? (s/n): " << std::endl;
    getline(std::cin, comando);
    std::cout << comando << std::endl;

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
        std::cout << "¿quieres escribir al final de la linea?" << std::endl;
        std::getline(std::cin, comando);

        if(comando == "s" || comando == "S"){
            archivo.EscribirArchivo();
        }
    }
    return 0;
}