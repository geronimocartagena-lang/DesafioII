#include "Album.h"

using namespace std;

Album::Album() {
    nombre = "";
    rutaAlmacenamiento = "";
    privacidad = "Publico";
    indiceFotoActual = 0;
}

Album::Album(const Album& otro) {
    this->nombre = otro.nombre;
    this->rutaAlmacenamiento = otro.rutaAlmacenamiento;
    this->privacidad = otro.privacidad;
    this->fotos = otro.fotos;
    this->indiceFotoActual = otro.indiceFotoActual;
}

Album::Album(const string& nom, const string& ruta, const string& priv) {
    this->nombre = nom;
    this->rutaAlmacenamiento = ruta;
    this->privacidad = priv;
    this->indiceFotoActual = 0;
}

Album::~Album() {
    // Manejado automáticamente por el destructor de Lista<T>
}

string Album::getNombre() const {
    return nombre;
}

void Album::setNombre(const string& nom) {
    this->nombre = nom;
}

string Album::getRutaAlmacenamiento() const {
    return rutaAlmacenamiento;
}

void Album::setRutaAlmacenamiento(const string& ruta) {
    this->rutaAlmacenamiento = ruta;
}

string Album::getPrivacidad() const {
    return privacidad;
}

void Album::setPrivacidad(const string& priv) {
    this->privacidad = priv;
}

void Album::agregarFoto(const Foto& foto) {
    fotos.agregarFinal(foto);
}

int Album::obtenerCantidadFotos() const {
    return fotos.obtenerTamano();
}

Foto& Album::obtenerFoto(int index) {
    return fotos[index];
}

Foto& Album::obtenerFotoSiguiente() {
    if (fotos.obtenerTamano() == 0) {
        static Foto fotoVacia;
        return fotoVacia;
    }
    indiceFotoActual = (indiceFotoActual + 1) % fotos.obtenerTamano();
    return fotos[indiceFotoActual];
}

Foto& Album::obtenerFotoAnterior() {
    if (fotos.obtenerTamano() == 0) {
        static Foto fotoVacia;
        return fotoVacia;
    }
    indiceFotoActual = (indiceFotoActual - 1 + fotos.obtenerTamano()) % fotos.obtenerTamano();
    return fotos[indiceFotoActual];
}