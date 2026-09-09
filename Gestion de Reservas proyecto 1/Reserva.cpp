#include "Reserva.h"
#include <iostream>

// Constructor
Reserva::Reserva(int numeroReserva, Cliente* clienteAsociado, Cancha* canchaAsociada, int franjaInicial, int cantidadFranjas, double precioHora) {
    this->numeroReserva = numeroReserva;
    this->clienteAsociado = clienteAsociado;
    this->canchaAsociada = canchaAsociada;
    this->franjaInicial = franjaInicial;
    this->cantidadFranjas = cantidadFranjas;

  
    this->monto = cantidadFranjas * precioHora;

    this->activa = true;
}

// Destructor
Reserva::~Reserva() {

}


void Reserva::cancelarReserva() {
    this->activa = false;
}


int Reserva::getNumeroReserva() const {
    return this->numeroReserva;
}