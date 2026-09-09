#pragma once
#include "Reserva.h"
class Coleccion_Reservas
{
private:
    Reserva** arregloReservas;
    int cantidadActual;
    int capacidadMaxima;

public:
   
    ColeccionReservas();
    ~ColeccionReservas();

    bool registrarReserva(Cliente* cliente, Cancha* cancha, int franjaInicial, int cantidadFranjas);

    void mostrarTodasLasReservas() const;
    void mostrarReservasPorCancha(const Cancha* cancha) const;
    Reserva* buscarReservaPorNumero(int numeroReserva) const;

    bool cancelarReserva(int numeroReserva);
};


