#include "Foto.h"

using namespace std;

Foto::Foto() {
    fechaCaptura = "";
    tamanoBytes = 0;
    rutaArchivo = "";
    conteoLikes = 0;
}

Foto::Foto(const Foto& otra) {
    this->fechaCaptura = otra.fechaCaptura;
    this->tamanoBytes = otra.tamanoBytes;
    this->rutaArchivo = otra.rutaArchivo;
    this->conteoLikes = otra.conteoLikes;
}

Foto::Foto(const string& fecha, unsigned int tam, const string& ruta) {
    this->fechaCaptura = fecha;
    this->tamanoBytes = tam;
    this->rutaArchivo = ruta;
    this->conteoLikes = 0;
}

Foto::~Foto() {
}

string Foto::getFechaCaptura() const {
    return fechaCaptura;
}

void Foto::setFechaCaptura(const string& fecha) {
    this->fechaCaptura = fecha;
}

unsigned int Foto::getTamanoBytes() const {
    return tamanoBytes;
}

void Foto::setTamanoBytes(unsigned int tam) {
    this->tamanoBytes = tam;
}

string Foto::getRutaArchivo() const {
    return rutaArchivo;
}

void Foto::setRutaArchivo(const string& ruta) {
    this->rutaArchivo = ruta;
}

int Foto::getConteoLikes() const {
    return conteoLikes;
}

void Foto::darLike() {
    conteoLikes++;
}

void Foto::quitarLike() {
    if (conteoLikes > 0) conteoLikes--;
}