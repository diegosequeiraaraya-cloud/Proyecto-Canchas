#pragma once
#include "Cliente.h"
#include "Cancha.h"
#include <string>
using namespace std;
class RegistroEspera
{
private:
    int consecutivo;
    Cliente* cliente;
    Cancha* cancha;
    int franja;
    string estado; 

public:
    RegistroEspera(int consecutivo, Cliente* cliente, Cancha* cancha, int franja);
    ~RegistroEspera();

    
    int getConsecutivo() const;
    Cliente* getCliente() const;
    Cancha* getCancha() const;
    int getFranja() const;
    string getEstado() const;

    
    void setEstado(const string& nuevoEstado);

};

