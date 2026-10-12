#include "Album.h"
#include <stdexcept>

Album::Album()
{
    nombre = "";
    rutaAlmacenamiento = "";
    privacidad = "privado";
    indiceFotoActual = 0;
}

Album::Album(const Album& otro)
{
    nombre = otro.nombre;
    rutaAlmacenamiento = otro.rutaAlmacenamiento;
    privacidad = otro.privacidad;
    fotos = otro.fotos;
    indiceFotoActual = otro.indiceFotoActual;
}

Album::Album(string nombre, string ruta, string privacidad)
{
    this->nombre = nombre;
    rutaAlmacenamiento = ruta;
    this->privacidad = privacidad;
    indiceFotoActual = 0;
}

Album::~Album()
{
}

void Album::agregarComoLeido(const Foto& foto)
{
    agregarFoto(foto);
}

void Album::agregarFoto(const Foto& foto)
{
    fotos.agregarFinal(foto);
}

Foto Album::obtenerFotoSiguiente()
{
    if (fotos.estaVacia())
    {
        throw out_of_range("El album no tiene fotos");
    }

    indiceFotoActual++;

    if (indiceFotoActual >= fotos.obtenerTamano())
    {
        indiceFotoActual = 0;
    }

    return fotos.obtenerElemento(indiceFotoActual);
}

Foto Album::obtenerFotoAnterior()
{
    if (fotos.estaVacia())
    {
        throw out_of_range("El album no tiene fotos");
    }

    indiceFotoActual--;

    if (indiceFotoActual < 0)
    {
        indiceFotoActual = fotos.obtenerTamano() - 1;
    }

    return fotos.obtenerElemento(indiceFotoActual);
}

int Album::obtenerCantidadFotos() const
{
    return fotos.obtenerTamano();
}

Foto Album::obtenerFoto(int indice) const
{
    return fotos.obtenerElemento(indice);
}

string Album::getNombre() const
{
    return nombre;
}

string Album::getRutaAlmacenamiento() const
{
    return rutaAlmacenamiento;
}

string Album::getPrivacidad() const
{
    return privacidad;
}

void Album::setNombre(string nombre)
{
    this->nombre = nombre;
}

void Album::setRutaAlmacenamiento(string ruta)
{
    rutaAlmacenamiento = ruta;
}

void Album::setPrivacidad(string privacidad)
{
    this->privacidad = privacidad;
}