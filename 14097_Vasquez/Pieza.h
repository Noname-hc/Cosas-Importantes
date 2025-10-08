#ifndef PIEZA_H
#define PIEZA_H

#include <string>

enum class TipoPieza { CIRCULO, RECTANGULO, TRIANGULO };

class Pieza{
public:
    Pieza(int id, TipoPieza tipo);
    virtual ~Pieza();

    void setDimensiones(double a, double b=0.0); // para circulo usa a=radio, b ignorado; rectangulo a=largo b=ancho; triangulo a=lado
    double getSuperficie() const;
    int getId() const;
    TipoPieza getTipo() const;

private:
    int id;
    TipoPieza tipo;
    double dimA;
    double dimB;
};

#endif
