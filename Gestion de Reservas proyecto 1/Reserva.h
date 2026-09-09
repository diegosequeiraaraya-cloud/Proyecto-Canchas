#pragma once
#include "Cliente.h"
#include "Cancha.h"

class Reserva
{
private:
    int numeroReserva;
    Cliente* clienteAsociado;
    Cancha* canchaAsociada;
    int franjaInicial; 
    int cantidadFranjas;
    double monto;
    bool activa; 

public:
    // Constructor
    Reserva(int numReserva, Cliente* cliente, Cancha* cancha, int fInicial, int cantFranjas, double precioHora);

    // Destructor
    ~Reserva();

    int getNumeroReserva() const;
    Cliente* getCliente() const;
    Cancha* getCancha() const;
    int getFranjaInicial() const;
    int getCantidadFranjas() const;
    double getMonto() const;
    bool isActiva() const;

    
    void cancelarReserva();
};

