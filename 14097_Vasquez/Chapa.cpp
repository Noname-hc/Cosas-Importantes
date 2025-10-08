#include "Chapa.h"

Chapa::Chapa() : largo(2000), ancho(1000), espesor(3) {}

Chapa::Chapa(int largo, int ancho, int espesor) : largo(largo), ancho(ancho), espesor(espesor) {}

double Chapa::getSuperficie() const{
    // superficie en mm^2
    return static_cast<double>(largo) * static_cast<double>(ancho);
}

int Chapa::getLargo() const{ return largo; }
int Chapa::getAncho() const{ return ancho; }
int Chapa::getEspesor() const{ return espesor; }
