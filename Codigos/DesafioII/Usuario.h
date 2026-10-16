#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "Lista.h"
#include "Album.h"
#include "Mensaje.h"

class Usuario {
private:
    std::string username;
    std::string contrasena;
    std::string fotoPerfilRuta;
    std::string fechaNacimiento;
    std::string email;
    std::string ciudad;
    std::string pais;
    std::string fechaInscripcion;

    Lista<std::string> solicitudesPendientes;
    Lista<std::string> amigos;
    Lista<Mensaje> mensajesEnviados;
    Lista<Mensaje> mensajesRecibidos;
    Lista<Album> albumes;

public:
    Usuario();
    Usuario(const std::string& user, const std::string& pass);
    Usuario(const std::string& user, const std::string& pass, const std::string& foto);
    Usuario(const std::string& user, const std::string& fnac, const std::string& mail,
            const std::string& foto, const std::string& pass, const std::string& ciu,
            const std::string& pa, const std::string& finsc);

    std::string getUsername() const;
    std::string getContrasena() const;
    std::string getFotoPerfilRuta() const;

    void setContrasena(const std::string& pass);
    void setFotoPerfilRuta(const std::string& foto);

    // Métodos requeridos por main.cpp
    void agregarSolicitud(const std::string& remitente);
    int obtenerCantidadSolicitudes() const;
    std::string obtenerSolicitud(int index);
    void eliminarSolicitud(int index);

    void agregarAmigo(const std::string& amigo);
    int obtenerCantidadAmigos() const;
    std::string obtenerAmigo(int index) const;
    bool esAmigo(const std::string& nombre) const;

    void recibirMensaje(const Mensaje& msg);
    int obtenerCantidadMensajesRecibidos() const;
    Mensaje& obtenerMensajeRecibido(int index);
    void marcarMensajeLeido(int index);

    void agregarAlbum(const Album& alb);
    int obtenerCantidadAlbumes() const;
    Album& obtenerAlbum(int index);
};

#endif // USUARIO_H