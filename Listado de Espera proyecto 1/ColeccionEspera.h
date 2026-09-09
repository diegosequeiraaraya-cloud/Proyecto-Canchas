#pragma once
#include "RegistroEspera.h"
#include <iostream>
using namespace std;
class ColeccionEspera
{
private:
    RegistroEspera** arregloEspera; 
    int cantidadActual;
    int capacidadMaxima;

public:
    ColeccionEspera();
    ~ColeccionEspera();

    bool agregarAEspera(Cliente* cliente, Cancha* cancha, int franja);
    void mostrarListadoEspera() const;
    bool cambiarEstado(int consecutivo, const string& nuevoEstado);

    // Método para conectar con el Módulo 3
    void verificarEsperasPorFranja(const Cancha* cancha, int franja) const;
};

