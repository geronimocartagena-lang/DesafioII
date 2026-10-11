#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "Lista.h"
#include "Mensaje.h"
#include "Album.h"

using namespace std;

class Usuario
{
private:
    string username;
    string fechaNacimiento;
    string email;
    string fotoPerfilRuta;
    string contrasena;
    string ciudad;
    string pais;
    string fechaInscripcion;

    Lista<string> solicitudesPendientes;
    Lista<string> amigos;
    Lista<Mensaje> mensajesEnviados;
    Lista<Mensaje> mensajesRecibidos;
    Lista<Album> albumes;

public:
    Usuario();
    Usuario(string username, string contrasena);
    Usuario(const Usuario& otro);

    ~Usuario();

    string getUsername() const;
    string getFechaNacimiento() const;
    string getEmail() const;
    string getFotoPerfilRuta() const;
    string getCiudad() const;
    string getPais() const;
    string getFechaInscripcion() const;

    void setFechaNacimiento(string fecha);
    void setEmail(string email);
    void setFotoPerfilRuta(string ruta);
    void setCiudad(string ciudad);
    void setPais(string pais);
    void setFechaInscripcion(string fecha);

    bool verificarContrasena(string contrasena) const;

    bool enviarSolicitud(string destinatario);
    bool aceptarSolicitud(string remitente);

    bool agregarAmigo(string username);
    bool esAmigo(string username) const;
    bool tieneSolicitud(string username) const;

    void agregarMensajeEnviado(const Mensaje& mensaje);
    void agregarMensajeRecibido(const Mensaje& mensaje);

    void agregarAlbum(const Album& album);

    int obtenerCantidadAmigos() const;
    string obtenerAmigo(int indice) const;

    int obtenerCantidadSolicitudes() const;
    string obtenerSolicitud(int indice) const;

    int obtenerCantidadMensajesRecibidos() const;
    Mensaje obtenerMensajeRecibido(int indice) const;
    void marcarMensajeLeido(int indice);

    int obtenerCantidadAlbumes() const;
    Album obtenerAlbum(int indice) const;

    Lista<string>& obtenerListaAmigos();
    Lista<Mensaje>& obtenerMensajesRecibidos();
    Lista<Album>& obtenerAlbumes();

    void setContrasena(string contrasena);
};

#endif