#include <cstring>
#include <iostream>
#include <vector>
#include <variant>
#include <fstream>

#include "File_P.h"


File_P::File_P(){
    this->ruta = "./Sin_Nombre.txt";
    this->Filetype = 'n'; // No hay ningun tipo de archivo especificado

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
    this->Filetype = tipo_de_archivo;
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

void File_P::Reescribir_Linea(std::string &frase,int N_linea){
    if(fs.is_open()){
        fs.close();
    }
    this->

    while(getline(fs,)){

    }

}