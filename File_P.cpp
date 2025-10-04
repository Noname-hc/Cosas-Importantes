#include <cstring>
#include <iostream>
#include <vector>
#include <variant>
#include <fstream>
#include <algorithm>

#include "File_P.h"


File_P::File_P(){
    this->ruta = "./Sin_Nombre.txt";
    this->FileType = 'n'; // No hay ningun tipo de archivo especificado

}

File_P::~File_P(){
    fs.close();

}

void File_P::set_fs(const std::string &ruta, const std::string &Modo){// Modo es rw, r o w
    if(fs.is_open()){
        fs.close();
    }
    fs.clear();

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
    this->set_fs(ruta, "rw");

    std::vector<std::string> lineas;
    std::string line;

    lineas.clear();
    fs.clear();
    fs.seekg(0);

    while(getline(fs, line)){
        lineas.push_back(line);
    }

    for (int i=0; i<lineas.size(); i++){
        std::cout << lineas[i] << std::endl;

    }
        fs.close();
    
}

void File_P::EscribirArchivo(){

    this->set_fs(ruta, "w");

    fs << std::endl;
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

/*void File_P::Reescribir_Linea(std::string &frase, int N_linea){
    // Apertura del archivo

    this->set_fs(ruta, "rw");

    // Leemos el archivo y obtenemos las lineas
    std::string linea_aux;
    int linea_actual = 0; // ultima linea escrita
    size_t pos = 0;

    fs.clear();
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
    fs.clear();
    fs.seekp(pos);
    fs << frase + espacios;
}*/

void File_P::Reescribir_Linea(std::string &frase, int N_linea) {

    // Abrir para lectura
    set_fs(ruta, "r");
    if (!fs.is_open()) {
        std::cerr << "No se pudo abrir el archivo para lectura.\n";
        return;
    }

    std::vector<std::string> lineas;
    std::string linea;

    while (std::getline(fs, linea)) {
        lineas.push_back(linea);
    }
    fs.close();

    // Verificar que la línea exista
    if (N_linea < 1 || N_linea > (int)lineas.size()) {
        std::cerr << "Número de línea inválido.\n";
        return;
    }

    // Reemplazar la línea
    lineas[N_linea - 1] = frase;

    // Reescribir todo el archivo
    set_fs(ruta, "rw");
    if (!fs.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escribir.\n";
        return;
    }

    fs.clear();
    fs.seekp(0, std::ios::beg);
    for (const auto &l : lineas) {
        fs << l << '\n';
    }

    fs.close();

    std::cout << "✅ Línea " << N_linea << " reescrita correctamente.\n";
}


// Método para leer y mostrar en formato elegido (csv, json, xml)
/*void File_P::Leer_Tipo_De_Archivo(char tipo_de_archivo) {

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
}*/

void File_P::Leer_Tipo_De_Archivo(char tipo_de_archivo) {
    // Apertura del archivo en modo lectura
    this->set_fs(ruta, "r");

    // Guardamos todo el archivo en un vector de strings
    std::vector<std::string> contenido; 
    contenido.clear();

    std::string linea_aux = "";
    while(getline(fs, linea_aux)){
        contenido.push_back(linea_aux);
    }

    // Manejo de los tipos de archivo a la hora de leer
    size_t pos = 0;

    std::string str_aux = "";
    std::string key_w;
    std::string valor;

    std::vector<datos> info_k;  
    std::vector<datos> info_v;  
    info_k.clear();
    info_v.clear();


    switch (FileType)
    {
        case 'x':
            for (int i=0; i < contenido.size();i++){
                str_aux = contenido[i];

                pos = str_aux.find("<"); 
                size_t pos_f = str_aux.find(">");

                if(pos != std::string::npos || pos_f != std::string::npos){

                    str_aux.erase(std::remove(str_aux.begin(), str_aux.end(), ' '), str_aux.end());// eliminamos los espacios

                    key_w = str_aux.substr(pos+1, pos_f-(pos+1));
                    info_k.push_back(key_w);

                    pos = str_aux.find("</");
                    valor = str_aux.substr(pos_f+1, pos-(pos_f+1));
    
                    if(std::stoi(valor)){
                        info_v.push_back(std::stoi(valor));

                    }else if(std::stod(valor)){
                        info_v.push_back(std::stod(valor));
                    
                    }else{
                        info_v.push_back(valor);
                    }

                } else{
                    continue;
                }   
            }
        break;

        case 'c':
            for (int i=0; i < contenido.size();i++){
                str_aux = contenido[i];

                pos = str_aux.find(","); // Buscamos ","
                if(pos != std::string::npos){

                    str_aux.erase(std::remove(str_aux.begin(), str_aux.end(), ' '), str_aux.end());// eliminamos los espacios
                    key_w = str_aux.substr(0, pos); 
                    valor = str_aux.substr(pos+1);

                    info_k.push_back(key_w);

                    if(std::stoi(valor)){
                        info_v.push_back(std::stoi(valor));

                    }else if(std::stod(valor)){
                        info_v.push_back(std::stod(valor));
                    
                    }else{
                        info_v.push_back(valor);
                    }

                } else{
                    continue;
                }   
            }
        break;

        case 'j':
            for (int i=0; i < contenido.size();i++){
                str_aux = contenido[i];

                pos = str_aux.find(":"); // Buscamos ":"
                if(pos != std::string::npos){

                    str_aux.erase(std::remove(str_aux.begin(), str_aux.end(), ' '), str_aux.end());// eliminamos los espacios
                    key_w = str_aux.substr(0, pos); 
                    valor = str_aux.substr(pos+1);

                    info_k.push_back(key_w);

                    if(std::stoi(valor)){
                        info_v.push_back(std::stoi(valor));

                    }else if(std::stod(valor)){
                        info_v.push_back(std::stod(valor));
                    
                    }else{
                        info_v.push_back(valor);
                    }

                } else{
                    continue;
                }   
            }
        break;
    
        default:
        
        break;
    }
}

void File_P::Leer_Linea(int N_linea){
    // Apertura del archivo
    this->set_fs(ruta, "rw");

    // Leemos el archivo y obtenemos las lineas
    std::string linea_aux;
    int linea_actual = 0; // ultima linea escrita

    fs.clear();
    fs.seekp(0);
    fs.seekg(0);

    bool leida = false;
    while(getline(fs, linea_aux)){
        linea_actual++;

        if(linea_actual == N_linea){
            leida= true;
            break;
        }
    }

    if(leida){
        std::cout << linea_aux << std::endl;

    }else{
        std::cout << "La linea no se pudo leer" << std::endl;
    }
}
    



void File_P::Borrar_Archivo(){

}

void File_P::MostrarDatos(){

}

void File_P::MostrarArchivo(){
    this->set_fs(ruta, "r");
    std::string linea_aux = "";
    std::string contenido;

    while(getline(fs, linea_aux)){
        contenido += linea_aux + "\n";
    }
    std::cout << contenido << std::endl;
}