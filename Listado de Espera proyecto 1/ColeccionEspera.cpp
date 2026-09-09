#include "ColeccionEspera.h"
using namespace std;
ColeccionEspera::ColeccionEspera() {
    this->capacidadMaxima = 10; // Capacidad máxima indicada en la especificación
    this->cantidadActual = 0;
    this->arregloEspera = new RegistroEspera * [capacidadMaxima];

    for (int i = 0; i < capacidadMaxima; i++) {
        arregloEspera[i] = nullptr;
    }
}

ColeccionEspera::~ColeccionEspera() {
    for (int i = 0; i < cantidadActual; i++) {
        delete arregloEspera[i];
    }
    delete[] arregloEspera;
}

bool ColeccionEspera::agregarAEspera(Cliente* cliente, Cancha* cancha, int franja) {
    // 1. Validar espacio disponible en el listado de espera
    if (cantidadActual >= capacidadMaxima) {
        cout << "Error: El listado de espera esta lleno (máximo 10 registros).\n";
        return false;
    }

    if (cancha->getDisponibilidad(franja) != 'O') {
        cout << "Error: Solo se puede agregar a la lista de espera cuando la franja esta ocupada (O).\n";
        return false;
    }

    for (int i = 0; i < cantidadActual; i++) {
        if (arregloEspera[i]->getEstado() == "esperando" &&
            arregloEspera[i]->getCliente() == cliente &&
            arregloEspera[i]->getCancha() == cancha &&
            arregloEspera[i]->getFranja() == franja) {
            cout << "Error: El cliente ya se encuentra en lista de espera para esta cancha y franja horaria.\n";
            return false;
        }
    }
    int consecutivo = cantidadActual + 1;
    arregloEspera[cantidadActual] = new RegistroEspera(consecutivo, cliente, cancha, franja);
    cantidadActual++;

    cout << "Cliente ingresado exitosamente a la lista de espera con el consecutivo #" << consecutivo << ".\n";
    return true;
}

void ColeccionEspera::mostrarListadoEspera() const {
    if (cantidadActual == 0) {
        cout << "El listado de espera esta vacio.\n";
        return;
    }

    cout << "\n=== LISTADO DE ESPERA ===\n";
    for (int i = 0; i < cantidadActual; i++) {
        RegistroEspera* r = arregloEspera[i];
        cout << "Registro #" << r->getConsecutivo() << "\n"
            << "  Cliente: " << r->getCliente()->getNombre() << " (ID: " << r->getCliente()->getId() << ")\n"
            << "  Cancha: " << r->getCancha()->getCodigo() << "\n"
            << "  Franja horaria: " << r->getFranja() << "\n"
            << "  Estado: " << r->getEstado() << "\n"
            << "-----------------------------------\n";
    }
}

bool ColeccionEspera::cambiarEstado(int consecutivo, const string& nuevoEstado) {
    for (int i = 0; i < cantidadActual; i++) {
        if (arregloEspera[i]->getConsecutivo() == consecutivo) {
            arregloEspera[i]->setEstado(nuevoEstado);
            cout << "Estado actualizado a '" << nuevoEstado << "' para el registro #" << consecutivo << ".\n";
            return true;
        }
    }
    cout << "Error: No se encontro el registro de espera #" << consecutivo << ".\n";
    return false;
}

// Conexión con la Cancelación del Módulo 3
void ColeccionEspera::verificarEsperasPorFranja(const Cancha* cancha, int franja) const {
    bool hayAlguien = false;

    for (int i = 0; i < cantidadActual; i++) {
        if (arregloEspera[i]->getCancha() == cancha &&
            arregloEspera[i]->getFranja() == franja &&
            arregloEspera[i]->getEstado() == "esperando") {

            if (!hayAlguien) {
                cout << "\n=======================================================\n";
                cout << "[AVISO LISTA DE ESPERA] Existen clientes esperando por esta franja:\n";
                hayAlguien = true;
            }

            cout << " - Registro #" << arregloEspera[i]->getConsecutivo()
                << " | Cliente: " << arregloEspera[i]->getCliente()->getNombre()
                << " (Tel: " << arregloEspera[i]->getCliente()->getTelefono() << ")\n";
        }
    }

    if (hayAlguien) {
        cout << "=======================================================\n";
    }
}