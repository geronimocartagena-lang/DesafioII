#include "Usuario.h"

using namespace std;

Usuario::Usuario() {
    username = "";
    contrasena = "";
    fotoPerfilRuta = "";
    email = "";
    ciudad = "";
}

Usuario::Usuario(const Usuario& otro) {
    this->username = otro.username;
    this->contrasena = otro.contrasena;
    this->fotoPerfilRuta = otro.fotoPerfilRuta;
    this->email = otro.email;
    this->ciudad = otro.ciudad;
    this->listaAmigos = otro.listaAmigos;
    this->solicitudesPendientes = otro.solicitudesPendientes;
    this->albumes = otro.albumes;
    this->mensajesEnviados = otro.mensajesEnviados;
    this->mensajesRecibidos = otro.mensajesRecibidos;
}

Usuario::Usuario(const string& user, const string& pass, const string& foto) {
    this->username = user;
    this->contrasena = pass;
    this->fotoPerfilRuta = foto;
    this->email = user + "@udea.edu.co";
    this->ciudad = "Medellin";
}

Usuario::~Usuario() {
}

string Usuario::getUsername() const {
    return username;
}

void Usuario::setUsername(const string& user) {
    this->username = user;
}

string Usuario::getContrasena() const {
    return contrasena;
}

void Usuario::setContrasena(const string& pass) {
    this->contrasena = pass;
}

string Usuario::getFotoPerfilRuta() const {
    return fotoPerfilRuta;
}

void Usuario::setFotoPerfilRuta(const string& foto) {
    this->fotoPerfilRuta = foto;
}

string Usuario::getEmail() const {
    return email;
}

void Usuario::setEmail(const string& mail) {
    this->email = mail;
}

string Usuario::getCiudad() const {
    return ciudad;
}

void Usuario::setCiudad(const string& city) {
    this->ciudad = city;
}

void Usuario::agregarAmigo(const string& amigo) {
    if (!esAmigo(amigo)) {
        listaAmigos.agregarFinal(amigo);
    }
}

bool Usuario::esAmigo(const string& amigo) const {
    for (int i = 0; i < listaAmigos.obtenerTamano(); ++i) {
        if (listaAmigos[i] == amigo) return true;
    }
    return false;
}

int Usuario::obtenerCantidadAmigos() const {
    return listaAmigos.obtenerTamano();
}

string Usuario::obtenerAmigo(int index) const {
    return listaAmigos[index];
}

void Usuario::agregarSolicitud(const string& remitente) {
    solicitudesPendientes.agregarFinal(remitente);
}

int Usuario::obtenerCantidadSolicitudes() const {
    return solicitudesPendientes.obtenerTamano();
}

string Usuario::obtenerSolicitud(int index) const {
    return solicitudesPendientes[index];
}

void Usuario::agregarAlbum(const Album& alb) {
    albumes.agregarFinal(alb);
}

int Usuario::obtenerCantidadAlbumes() const {
    return albumes.obtenerTamano();
}

Album& Usuario::obtenerAlbum(int index) {
    return albumes[index];
}

void Usuario::recibirMensaje(const Mensaje& msg) {
    mensajesRecibidos.agregarFinal(msg);
}

void Usuario::enviarMensaje(const Mensaje& msg) {
    mensajesEnviados.agregarFinal(msg);
}

int Usuario::obtenerCantidadMensajesRecibidos() const {
    return mensajesRecibidos.obtenerTamano();
}

Mensaje& Usuario::obtenerMensajeRecibido(int index) {
    return mensajesRecibidos[index];
}

void Usuario::marcarMensajeLeido(int index) {
    if (index >= 0 && index < mensajesRecibidos.obtenerTamano()) {
        mensajesRecibidos[index].marcarComoLeido();
    }
}

ostream& operator<<(ostream& os, const Usuario& u) {
    os << "Usuario: " << u.username << " | Profile: " << u.fotoPerfilRuta;
    return os;
}