#include "Pieza.h"
#include <cmath>

Pieza::Pieza(int id, TipoPieza tipo) : id(id), tipo(tipo), dimA(0.0), dimB(0.0) {}
Pieza::~Pieza() = default;

void Pieza::setDimensiones(double a, double b){
    dimA = a;
    dimB = b;
}

double Pieza::getSuperficie() const{
    switch(tipo){
        case TipoPieza::CIRCULO:{
            double r = dimA;
            return M_PI * r * r;
        }
        case TipoPieza::RECTANGULO:{
            return dimA * dimB;
        }
        case TipoPieza::TRIANGULO:{
            // triangulo equilatero area = (sqrt(3)/4) * lado^2
            double lado = dimA;
            return (std::sqrt(3.0) / 4.0) * lado * lado;
        }
    }
    return 0.0;
}

int Pieza::getId() const{ return id; }
TipoPieza Pieza::getTipo() const{ return tipo; }
