#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <iostream>
#include "Lista.h"
#include "Album.h"
#include "Mensaje.h"

class Usuario {
private:
    std::string username;
    std::string contrasena;
    std::string fotoPerfilRuta;
    std::string email;
    std::string ciudad;

    Lista<std::string> listaAmigos;
    Lista<std::string> solicitudesPendientes;
    Lista<Album> albumes;
    Lista<Mensaje> mensajesEnviados;
    Lista<Mensaje> mensajesRecibidos;

public:
    Usuario();
    Usuario(const Usuario& otro);
    Usuario(const std::string& user, const std::string& pass, const std::string& foto);
    ~Usuario();

    std::string getUsername() const;
    void setUsername(const std::string& user);

    std::string getContrasena() const;
    void setContrasena(const std::string& pass);

    std::string getFotoPerfilRuta() const;
    void setFotoPerfilRuta(const std::string& foto);

    std::string getEmail() const;
    void setEmail(const std::string& mail);

    std::string getCiudad() const;
    void setCiudad(const std::string& city);

    void agregarAmigo(const std::string& amigo);
    bool esAmigo(const std::string& amigo) const;
    int obtenerCantidadAmigos() const;
    std::string obtenerAmigo(int index) const;

    void agregarSolicitud(const std::string& remitente);
    int obtenerCantidadSolicitudes() const;
    std::string obtenerSolicitud(int index) const;

    void agregarAlbum(const Album& alb);
    int obtenerCantidadAlbumes() const;
    Album& obtenerAlbum(int index);

    void recibirMensaje(const Mensaje& msg);
    void enviarMensaje(const Mensaje& msg);
    int obtenerCantidadMensajesRecibidos() const;
    Mensaje& obtenerMensajeRecibido(int index);
    void marcarMensajeLeido(int index);

    // Sobrecarga del operador << para imprimir informacion del usuario
    friend std::ostream& operator<<(std::ostream& os, const Usuario& u);
};

#endif