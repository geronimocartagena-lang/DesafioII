#ifndef MANEJORECURSOS_H
#define MANEJORECURSOS_H

#include <cstddef>

class Manejorecursos {
private:
    std::size_t memoriaConsumidaBytes;
    unsigned long long contadorIteraciones;

public:
    Manejorecursos();
    ~Manejorecursos();

    void registrarAsignacion(std::size_t bytes);
    void registrarLiberacion(std::size_t bytes);
    void incrementarIteracion(int num = 1);

    std::size_t obtenerMemoriaConsumida() const;
    unsigned long long obtenerIteraciones() const;
    void reiniciarContadores();
};

#endif // MANEJORECURSOS_H