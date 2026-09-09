#include "RegistroEspera.h"

RegistroEspera::RegistroEspera(int consecutivo, Cliente* cliente, Cancha* cancha, int franja) {
    this->consecutivo = consecutivo;
    this->cliente = cliente;
    this->cancha = cancha;
    this->franja = franja;
    this->estado = "esperando"; // Todo registro inicia en "esperando"
}

RegistroEspera::~RegistroEspera() {}

int RegistroEspera::getConsecutivo() const { return this->consecutivo; }
Cliente* RegistroEspera::getCliente() const { return this->cliente; }
Cancha* RegistroEspera::getCancha() const { return this->cancha; }
int RegistroEspera::getFranja() const { return this->franja; }
string RegistroEspera::getEstado() const { return this->estado; }

void RegistroEspera::setEstado(const string& nuevoEstado) {
    this->estado = nuevoEstado;
}