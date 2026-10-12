#include "Manejorecursos.h"

Manejorecursos::Manejorecursos()
{
    memoriaConsumidaBytes = 0;
    contadorIteraciones = 0;
}

void Manejorecursos::registrarAsignacion(size_t bytes)
{
    memoriaConsumidaBytes += bytes;
}

void Manejorecursos::registrarLiberacion(size_t bytes)
{
    if (bytes <= memoriaConsumidaBytes)
    {
        memoriaConsumidaBytes -= bytes;
    }
    else
    {
        memoriaConsumidaBytes = 0;
    }
}

void Manejorecursos::incrementarIteracion(unsigned long long num)
{
    contadorIteraciones += num;
}

size_t Manejorecursos::obtenerMemoriaConsumida() const
{
    return memoriaConsumidaBytes;
}

unsigned long long Manejorecursos::obtenerIteraciones() const
{
    return contadorIteraciones;
}

void Manejorecursos::reiniciarContadores()
{
    contadorIteraciones = 0;
}