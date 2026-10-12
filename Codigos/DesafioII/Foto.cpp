#include "Foto.h"

Foto::Foto()
{
    fechaCaptura = "";
    tamanoBytes = 0;
    rutaArchivo = "";
    conteoLikes = 0;
}

Foto::Foto(const Foto& otra)
{
    fechaCaptura = otra.fechaCaptura;
    tamanoBytes = otra.tamanoBytes;
    rutaArchivo = otra.rutaArchivo;
    conteoLikes = otra.conteoLikes;
}

Foto::Foto(string fecha, unsigned int tamano, string ruta)
{
    fechaCaptura = fecha;
    tamanoBytes = tamano;
    rutaArchivo = ruta;
    conteoLikes = 0;
}

Foto::~Foto()
{
}

void Foto::darLike()
{
    conteoLikes++;
}

void Foto::quitarLike()
{
    if (conteoLikes > 0)
    {
        conteoLikes--;
    }
}

string Foto::getRutaArchivo() const
{
    return rutaArchivo;
}

string Foto::getFechaCaptura() const
{
    return fechaCaptura;
}

unsigned int Foto::getTamanoBytes() const
{
    return tamanoBytes;
}

int Foto::getConteoLikes() const
{
    return conteoLikes;
}

void Foto::setFechaCaptura(string fecha)
{
    fechaCaptura = fecha;
}

void Foto::setTamanoBytes(unsigned int tamano)
{
    tamanoBytes = tamano;
}

void Foto::setRutaArchivo(string ruta)
{
    rutaArchivo = ruta;
}