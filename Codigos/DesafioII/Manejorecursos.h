#ifndef MANEJORECURSOS_H
#define MANEJORECURSOS_H

#include <cstddef>

class Manejorecursos
{
private:
    size_t memoriaConsumidaBytes;
    unsigned long long contadorIteraciones;

public:
    Manejorecursos();

    void registrarAsignacion(size_t bytes);
    void registrarLiberacion(size_t bytes);
    void incrementarIteracion(unsigned long long num = 1);

    size_t obtenerMemoriaConsumida() const;
    unsigned long long obtenerIteraciones() const;

    void reiniciarContadores();
};

#endif