#ifndef CHAPA_H
#define CHAPA_H

#include <cstddef>

class Chapa{
public:
    Chapa();
    Chapa(int largo, int ancho, int espesor);

    double getSuperficie() const; // devuelve superficie en unidades cuadradas (double)

    int getLargo() const;
    int getAncho() const;
    int getEspesor() const;

private:
    int largo; // mm
    int ancho; // mm
    int espesor; // mm
};

#endif
