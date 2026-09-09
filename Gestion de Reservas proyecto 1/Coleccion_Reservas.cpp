#include "Coleccion_Reservas.h"
#include "ColeccionEspera.h"
#include <iostream>
using namespace std;
ColeccionReservas::ColeccionReservas() {
    this->capacidadMaxima = 120;
    this->cantidadActual = 0;

    this->arregloReservas = new Reserva * [capacidadMaxima];

  
    for (int i = 0; i < capacidadMaxima; i++) {
        arregloReservas[i] = nullptr;
    }
}
ColeccionReservas::~ColeccionReservas() {

    for (int i = 0; i < cantidadActual; i++) {
        delete arregloReservas[i];
    }
   
    delete[] arregloReservas;
}

bool ColeccionReservas::registrarReserva(Cliente* cliente, Cancha* cancha, int franjaInicial, int cantidadFranjas) {
  
    if (cantidadActual >= capacidadMaxima) {
        cout << "Error: Se ha alcanzado el límite máximo de reservas (120).\n";
        return false;
    }

    if (cliente == nullptr || cancha == nullptr) {
        cout << "Error: El cliente o la cancha no existen.\n";
        return false;
    }

    if (franjaInicial < 0 || (franjaInicial + cantidadFranjas) > 12) {
        cout << "Error: La franja horaria seleccionada está fuera de rango.\n";
        return false;
    }

   
    for (int i = franjaInicial; i < (franjaInicial + cantidadFranjas); i++) {
        if (cancha->getDisponibilidad(i) != 'L') {
            cout << "Error: La franja no está disponible. No se puede realizar la reserva.\n";
           
            return false;
        }
    }
        
    int nuevoNumeroReserva = cantidadActual + 1;
       
    double precioHora = cancha->getPrecio();
    Reserva* nuevaReserva = new Reserva(nuevoNumeroReserva, cliente, cancha, franjaInicial, cantidadFranjas, precioHora);
       
    arregloReservas[cantidadActual] = nuevaReserva;
    cantidadActual++;
        
    for (int i = franjaInicial; i < (franjaInicial + cantidadFranjas); i++) {
        cancha->setDisponibilidad(i, 'O');
    }

    cout << "Reserva #" << nuevoNumeroReserva << " registrada exitosamente.\n";
    return true;
}

bool ColeccionReservas::cancelarReserva(int numeroReserva, ColeccionEspera& coleccionEspera) {
   
    Reserva* reservaEncontrada = buscarReservaPorNumero(numeroReserva);

    if (reservaEncontrada == nullptr) {
        cout << "Error: No se encontro ninguna reserva con el numero #" << numeroReserva << ".\n";
        return false;
    }

    if (!reservaEncontrada->isActiva()) {
        cout << "Error: La reserva #" << numeroReserva << " ya se encuentra cancelada.\n";
        return false;
    }

    reservaEncontrada->cancelarReserva();

    Cancha* canchaAsociada = reservaEncontrada->getCancha();
    int inicio = reservaEncontrada->getFranjaInicial();
    int totalFranjas = reservaEncontrada->getCantidadFranjas();

    for (int i = inicio; i < (inicio + totalFranjas); i++) {
        canchaAsociada->setDisponibilidad(i, 'L');
    }

    // Fragmento dentro de cancelarReserva() en ColeccionReservas.cpp
    for (int f = inicio; f < (inicio + totalFranjas); f++) {
        canchaAsociada->setDisponibilidad(f, 'L');

        // Llamada a la lista de espera por cada franja liberada:
        coleccionEspera.verificarEsperasPorFranja(canchaAsociada, f);
    }

    cout << "La reserva #" << numeroReserva << " ha sido cancelada exitosamente.\n";
    cout << "Las franjas horarias de la cancha han sido liberadas (L).\n";

    verificarListadoDeEspera(canchaAsociada, inicio, totalFranjas);

    return true;
}

void ColeccionReservas::mostrarTodasLasReservas() const {
    if (cantidadActual == 0) {
        cout << "No hay reservas registradas en el sistema.\n";
        return;
    }

    std::cout << "\n=== LISTADO GENERAL DE RESERVAS ===\n";
    for (int i = 0; i < cantidadActual; i++) {
        Reserva* r = arregloReservas[i];

        cout << "Reserva #" << r->getNumeroReserva() << "\n"
            << "  Cliente: " << r->getCliente()->getNombre() << " (ID: " << r->getCliente()->getId() << ")\n"
            << "  Cancha: " << r->getCancha()->getCodigo() << "\n"
            << "  Franja inicio: " << r->getFranjaInicial() << " | Cantidad franjas: " << r->getCantidadFranjas() << "\n"
            << "  Monto total: $" << r->getMonto() << "\n"
            << "  Estado: " << (r->isActiva() ? "Activa" : "Cancelada") << "\n"
            << "-----------------------------------\n";
    }
}

void ColeccionReservas::mostrarReservasPorCancha(const Cancha* cancha) const {
    if (cancha == nullptr) {
        cout << "Error: La cancha especificada no existe.\n";
        return;
    }

    bool encontro = false;
    cout << "\n=== RESERVAS PARA LA CANCHA: " << cancha->getCodigo() << " ===\n";

    for (int i = 0; i < cantidadActual; i++) {
        
        if (arregloReservas[i]->getCancha() == cancha) {
            Reserva* r = arregloReservas[i];
            cout << "Reserva #" << r->getNumeroReserva()
                << " | Cliente: " << r->getCliente()->getNombre()
                << " | Estado: " << (r->isActiva() ? "Activa" : "Cancelada") << "\n";
            encontro = true;
        }
    }

    if (!encontro) {
        cout << "No se encontraron reservas registradas para esta cancha.\n";
    }
}