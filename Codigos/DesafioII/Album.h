#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "Lista.h"
#include "Foto.h"

using namespace std;

class Album
{
private:
    string nombre;
    string rutaAlmacenamiento;
    string privacidad;
    Lista<Foto> fotos;
    int indiceFotoActual;

public:
    Album();
    Album(const Album& otro);
    Album(string nombre, string ruta, string privacidad);

    ~Album();

    void agregarComoLeido(const Foto& foto);
    void agregarFoto(const Foto& foto);

    Foto obtenerFotoSiguiente();
    Foto obtenerFotoAnterior();

    int obtenerCantidadFotos() const;
    Foto obtenerFoto(int indice) const;

    string getNombre() const;
    string getRutaAlmacenamiento() const;
    string getPrivacidad() const;

    void setNombre(string nombre);
    void setRutaAlmacenamiento(string ruta);
    void setPrivacidad(string privacidad);
};

#endif