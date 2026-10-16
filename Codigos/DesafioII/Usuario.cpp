#include "Usuario.h"

Usuario::Usuario() {
    username = "";
    contrasena = "";
    fotoPerfilRuta = "";
}

Usuario::Usuario(const std::string& user, const std::string& pass) {
    this->username = user;
    this->contrasena = pass;
    this->fotoPerfilRuta = "/users/udeabook/static/" + user + "/profile.png";
}

Usuario::Usuario(const std::string& user, const std::string& pass, const std::string& foto) {
    this->username = user;
    this->contrasena = pass;
    this->fotoPerfilRuta = foto;
}

Usuario::Usuario(const std::string& user, const std::string& fnac, const std::string& mail,
                 const std::string& foto, const std::string& pass, const std::string& ciu,
                 const std::string& pa, const std::string& finsc) {
    this->username = user;
    this->fechaNacimiento = fnac;
    this->email = mail;
    this->fotoPerfilRuta = foto;
    this->contrasena = pass;
    this->ciudad = ciu;
    this->pais = pa;
    this->fechaInscripcion = finsc;
}

std::string Usuario::getUsername() const { return username; }
std::string Usuario::getContrasena() const { return contrasena; }
std::string Usuario::getFotoPerfilRuta() const { return fotoPerfilRuta; }

void Usuario::setContrasena(const std::string& pass) { this->contrasena = pass; }
void Usuario::setFotoPerfilRuta(const std::string& foto) { this->fotoPerfilRuta = foto; }

void Usuario::agregarSolicitud(const std::string& remitente) {
    solicitudesPendientes.agregarFinal(remitente);
}

int Usuario::obtenerCantidadSolicitudes() const {
    return solicitudesPendientes.obtenerTamano();
}

std::string Usuario::obtenerSolicitud(int index) {
    return solicitudesPendientes[index];
}

void Usuario::eliminarSolicitud(int index) {
    // Si tu Lista<T> no tiene eliminar, se simula o limpia
}

void Usuario::agregarAmigo(const std::string& amigo) {
    amigos.agregarFinal(amigo);
}

int Usuario::obtenerCantidadAmigos() const {
    return amigos.obtenerTamano();
}

std::string Usuario::obtenerAmigo(int index) const {
    return amigos[index];
}

bool Usuario::esAmigo(const std::string& nombre) const {
    for (int i = 0; i < amigos.obtenerTamano(); ++i) {
        if (amigos[i] == nombre) return true;
    }
    return false;
}

void Usuario::recibirMensaje(const Mensaje& msg) {
    mensajesRecibidos.agregarFinal(msg);
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

void Usuario::agregarAlbum(const Album& alb) {
    albumes.agregarFinal(alb);
}

int Usuario::obtenerCantidadAlbumes() const {
    return albumes.obtenerTamano();
}

Album& Usuario::obtenerAlbum(int index) {
    return albumes[index];
}