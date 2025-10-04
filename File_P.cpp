#include <cstring>
#include <iostream>
#include <vector>
#include <variant>
#include <fstream>

#include "File_P.h"


File_P::File_P(){
    this->ruta = "./Sin_Nombre.txt";
    this->FileType = 'n'; // No hay ningun tipo de archivo especificado

}

void File_P::set_fs(const std::string &ruta, const std::string &Modo){// Modo es rw, r o w
    this->ruta = ruta;

    if(Modo == "r"){
        this->fs.open(ruta, std::ios::in);

    } else if(Modo == "rw"){
        this->fs.open(ruta, std::ios::out | std::ios::ate | std::ios::in);

    }else if(Modo == "w"){
        this->fs.open(ruta, std::ios::out | std::ios::app);

    }
}

void File_P::set_FileType(char tipo_de_archivo){
    this->FileType = tipo_de_archivo;
}

//=====================================================================================================

void File_P::Leer_Archivo(){
    this->set_fs(ruta, "r");

    std::vector<std::string> lineas;
    std::string line;

    lineas.clear();
    while(getline(fs, line)){
        lineas.insert(lineas.begin() + lineas.size()-1, line); //lineas.push_back(line);
    }
    fs.close();

}
void File_P::EscribirArchivo(){
    if(fs.is_open()){
        fs.close();
    }
    this->set_fs(ruta, "w");

    std::cout << "ya puede escribir, para parar ingrese 'stop'" << std::endl;

    std::string line;
    while(true){
        getline(std::cin, line);

        if(line == "stop"){
            break;
        }
        fs << line << std::endl;
    }

    fs.close();
}

void File_P::Escribir_Al_Final(std::string &frase){
    this->set_fs(ruta, "w");

    fs << frase << std::endl;
}

void File_P::Reescribir_Linea(std::string &frase, int N_linea){
    // Apertura del archivo
    if(fs.is_open()){
        fs.close();
    }
    this->set_fs(ruta, "rw");

    // Leemos el archivo y obtenemos las lineas
    std::string linea_aux;
    int linea_actual = 0; // ultima linea escrita
    size_t pos = 0;

    fs.seekp(0);
    fs.seekg(0);

    while(getline(fs, linea_aux)){
        linea_actual++;

        pos += linea_aux.size() + 1;

        if(linea_actual == N_linea){
            break;
        }
    }

    // Agregamos espacios para completar la linea
    std::string espacios = "";
    
    getline(fs, linea_aux);
    for(int i = 0; i < (linea_aux.size() - frase.size()); i++){
        espacios += " ";
    }
    // Escribimos la linea
    fs << frase + espacios;
}


// Método para leer y mostrar en formato elegido (csv, json, xml)
void File_P::Leer_Tipo_De_Archivo(char tipo_de_archivo) {
    if (fs.is_open()) {
        fs.close();
    }
    this->set_fs(ruta,"r");

    std::string linea;
    std::vector<std::vector<std::string>> contenido;

    // Leer el archivo línea por línea y separarlo en tokens (muy simple, por comas o espacios)
    while (getline(fs, linea)) {
        std::vector<std::string> fila;
        std::string token;
        for (char c : linea) {
            if (c == ',' || c == ' ' || c == '\t') {
                if (!token.empty()) {
                    fila.push_back(token);
                    token.clear();
                }
            } else {
                token.push_back(c);
            }
        }
        if (!token.empty()) fila.push_back(token);
        contenido.push_back(fila);
    }

    // Mostrar según FileType
    switch (FileType) {
        case 'c':  // CSV
            for (auto &fila : contenido) {
                for (size_t i = 0; i < fila.size(); i++) {
                    std::cout << fila[i];
                    if (i < fila.size() - 1) std::cout << ",";
                }
                std::cout << "\n";
            }
            break;

        case 'j':  // JSON
            std::cout << "[\n";
            for (size_t i = 0; i < contenido.size(); i++) {
                std::cout << "  { ";
                for (size_t j = 0; j < contenido[i].size(); j++) {
                    std::cout << "\"col" << j + 1 << "\": \"" << contenido[i][j] << "\"";
                    if (j < contenido[i].size() - 1) std::cout << ", ";
                }
                std::cout << " }";
                if (i < contenido.size() - 1) std::cout << ",";
                std::cout << "\n";
            }
            std::cout << "]\n";
            break;

        case 'x':  // XML
            std::cout << "<root>\n";
            for (size_t i = 0; i < contenido.size(); i++) {
                std::cout << "  <row>\n";
                for (size_t j = 0; j < contenido[i].size(); j++) {
                    std::cout << "    <col" << j + 1 << ">" << contenido[i][j] << "</col" << j + 1 << ">\n";
                }
                std::cout << "  </row>\n";
            }
            std::cout << "</root>\n";
            break;

        default:
            std::cerr << "Error: tipo de archivo no soportado. Usa 'c'=CSV, 'j'=JSON, 'x'=XML.\n";
            break;
    }
}