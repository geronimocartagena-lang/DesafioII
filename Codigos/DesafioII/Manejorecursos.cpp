#include "Manejorecursos.h"

Manejorecursos::Manejorecursos() {
    memoriaConsumidaBytes = 0;
    contadorIteraciones = 0;
}

Manejorecursos::~Manejorecursos() {
}

void Manejorecursos::registrarAsignacion(std::size_t bytes) {
    memoriaConsumidaBytes += bytes;
}

void Manejorecursos::registrarLiberacion(std::size_t bytes) {
    if (memoriaConsumidaBytes >= bytes) {
        memoriaConsumidaBytes -= bytes;
    } else {
        memoriaConsumidaBytes = 0;
    }
}

void Manejorecursos::incrementarIteracion(int num) {
    contadorIteraciones += num;
}

std::size_t Manejorecursos::obtenerMemoriaConsumida() const {
    return memoriaConsumidaBytes;
}

unsigned long long Manejorecursos::obtenerIteraciones() const {
    return contadorIteraciones;
}

void Manejorecursos::reiniciarContadores() {
    memoriaConsumidaBytes = 0;
    contadorIteraciones = 0;
}