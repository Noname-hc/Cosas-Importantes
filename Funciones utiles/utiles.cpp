#include <iostream>
#include <filesystem>
#include <fstream>
#include <random>
#include <cstring>
#include <algorithm>

#include "utiles.h"


double randomDouble(double min, double max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(min, max);
    return dist(gen);
}

void eliminar_espacios(std::string &str){
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());// eliminamos los espacios
}