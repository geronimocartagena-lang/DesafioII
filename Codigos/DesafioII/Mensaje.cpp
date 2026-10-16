#include "Mensaje.h"
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

// obtener la fecha actual en formato "YYYY-MM-DD"
string obtenerFechaActual() {
    time_t ahora = time(nullptr);
    tm* tiempoLocal = localtime(&ahora);
    stringstream ss;
    ss << (tiempoLocal->tm_year + 1900) << "-"
       << setfill('0') << setw(2) << (tiempoLocal->tm_mon + 1) << "-"
       << setfill('0') << setw(2) << tiempoLocal->tm_mday;
    return ss.str();
}

Mensaje::Mensaje() {
    emisor = "";
    receptor = "";
    textoContenido = "";
    fechaEnvio = obtenerFechaActual();
    leido = false;
}

Mensaje::Mensaje(const Mensaje& otro) {
    this->emisor = otro.emisor;
    this->receptor = otro.receptor;
    this->textoContenido = otro.textoContenido;
    this->fechaEnvio = otro.fechaEnvio;
    this->leido = otro.leido;
}

Mensaje::Mensaje(const string& em, const string& rec, const string& txt) {
    this->emisor = em;
    this->receptor = rec;
    this->textoContenido = txt;
    this->fechaEnvio = obtenerFechaActual(); // Se asigna automáticamente la fecha del día
    this->leido = false;
}

Mensaje::Mensaje(const string& em, const string& rec, const string& txt, const string& fecha) {
    this->emisor = em;
    this->receptor = rec;
    this->textoContenido = txt;
    this->fechaEnvio = fecha; // Permite cargar fechas personalizadas desde archivos .txt
    this->leido = false;
}

Mensaje::~Mensaje() {
}

string Mensaje::getEmisor() const {
    return emisor;
}

void Mensaje::setEmisor(const string& em) {
    this->emisor = em;
}

string Mensaje::getReceptor() const {
    return receptor;
}

void Mensaje::setReceptor(const string& rec) {
    this->receptor = rec;
}

string Mensaje::getTextoContenido() const {
    return textoContenido;
}

void Mensaje::setTextoContenido(const string& txt) {
    this->textoContenido = txt;
}

string Mensaje::getFechaEnvio() const {
    return fechaEnvio;
}

void Mensaje::setFechaEnvio(const string& fecha) {
    this->fechaEnvio = fecha;
}

bool Mensaje::getLeido() const {
    return leido;
}

bool Mensaje::isLeido() const {
    return leido;
}

void Mensaje::marcarComoLeido() {
    this->leido = true;
}

bool Mensaje::operator==(const Mensaje& otro) const {
    return (emisor == otro.emisor && receptor == otro.receptor &&
            textoContenido == otro.textoContenido && fechaEnvio == otro.fechaEnvio);
}

bool Mensaje::operator<(const Mensaje& otro) const {
    return fechaEnvio < otro.fechaEnvio;
}

ostream& operator<<(ostream& os, const Mensaje& m) {
    os << "[" << m.fechaEnvio << "] De: " << m.emisor << " Para: " << m.receptor << " - " << m.textoContenido;
    return os;
}