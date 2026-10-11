#include "Usuario.h"

Usuario::Usuario()
{
    username = "";
    fechaNacimiento = "";
    email = "";
    fotoPerfilRuta = "";
    contrasena = "";
    ciudad = "";
    pais = "";
    fechaInscripcion = "";
}

Usuario::Usuario(string username, string contrasena)
{
    this->username = username;
    this->contrasena = contrasena;
    fechaNacimiento = "";
    email = "";
    fotoPerfilRuta = "";
    ciudad = "";
    pais = "";
    fechaInscripcion = "";
}

Usuario::Usuario(const Usuario& otro)
{
    username = otro.username;
    fechaNacimiento = otro.fechaNacimiento;
    email = otro.email;
    fotoPerfilRuta = otro.fotoPerfilRuta;
    contrasena = otro.contrasena;
    ciudad = otro.ciudad;
    pais = otro.pais;
    fechaInscripcion = otro.fechaInscripcion;

    solicitudesPendientes = otro.solicitudesPendientes;
    amigos = otro.amigos;
    mensajesEnviados = otro.mensajesEnviados;
    mensajesRecibidos = otro.mensajesRecibidos;
    albumes = otro.albumes;
}

Usuario::~Usuario()
{
}

string Usuario::getUsername() const
{
    return username;
}

string Usuario::getFechaNacimiento() const
{
    return fechaNacimiento;
}

string Usuario::getEmail() const
{
    return email;
}

string Usuario::getFotoPerfilRuta() const
{
    return fotoPerfilRuta;
}

string Usuario::getCiudad() const
{
    return ciudad;
}

string Usuario::getPais() const
{
    return pais;
}

string Usuario::getFechaInscripcion() const
{
    return fechaInscripcion;
}

void Usuario::setFechaNacimiento(string fecha)
{
    fechaNacimiento = fecha;
}

void Usuario::setEmail(string email)
{
    this->email = email;
}

void Usuario::setFotoPerfilRuta(string ruta)
{
    fotoPerfilRuta = ruta;
}

void Usuario::setCiudad(string ciudad)
{
    this->ciudad = ciudad;
}

void Usuario::setPais(string pais)
{
    this->pais = pais;
}

void Usuario::setFechaInscripcion(string fecha)
{
    fechaInscripcion = fecha;
}

bool Usuario::verificarContrasena(string contrasena) const
{
    return this->contrasena == contrasena;
}

bool Usuario::enviarSolicitud(string destinatario)
{
    if (destinatario == username || esAmigo(destinatario))
    {
        return false;
    }

    for (int i = 0; i < solicitudesPendientes.obtenerTamano(); i++)
    {
        if (solicitudesPendientes[i] == destinatario)
        {
            return false;
        }
    }

    solicitudesPendientes.agregarFinal(destinatario);
    return true;
}

bool Usuario::aceptarSolicitud(string remitente)
{
    for (int i = 0; i < solicitudesPendientes.obtenerTamano(); i++)
    {
        if (solicitudesPendientes[i] == remitente)
        {
            solicitudesPendientes.eliminarElemento(i);
            agregarAmigo(remitente);
            return true;
        }
    }

    return false;
}

bool Usuario::agregarAmigo(string username)
{
    if (username == this->username || esAmigo(username))
    {
        return false;
    }

    amigos.agregarFinal(username);
    return true;
}

bool Usuario::esAmigo(string username) const
{
    for (int i = 0; i < amigos.obtenerTamano(); i++)
    {
        if (amigos[i] == username)
        {
            return true;
        }
    }

    return false;
}

bool Usuario::tieneSolicitud(string username) const
{
    for (int i = 0; i < solicitudesPendientes.obtenerTamano(); i++)
    {
        if (solicitudesPendientes[i] == username)
        {
            return true;
        }
    }

    return false;
}

void Usuario::agregarMensajeEnviado(const Mensaje& mensaje)
{
    mensajesEnviados.agregarFinal(mensaje);
}

void Usuario::agregarMensajeRecibido(const Mensaje& mensaje)
{
    mensajesRecibidos.agregarFinal(mensaje);
}

void Usuario::agregarAlbum(const Album& album)
{
    albumes.agregarFinal(album);
}

int Usuario::obtenerCantidadAmigos() const
{
    return amigos.obtenerTamano();
}

string Usuario::obtenerAmigo(int indice) const
{
    return amigos.obtenerElemento(indice);
}

int Usuario::obtenerCantidadSolicitudes() const
{
    return solicitudesPendientes.obtenerTamano();
}

string Usuario::obtenerSolicitud(int indice) const
{
    return solicitudesPendientes.obtenerElemento(indice);
}

int Usuario::obtenerCantidadMensajesRecibidos() const
{
    return mensajesRecibidos.obtenerTamano();
}

Mensaje Usuario::obtenerMensajeRecibido(int indice) const
{
    return mensajesRecibidos.obtenerElemento(indice);
}

void Usuario::marcarMensajeLeido(int indice)
{
    mensajesRecibidos.obtenerElemento(indice).marcarComoLeido();
}

int Usuario::obtenerCantidadAlbumes() const
{
    return albumes.obtenerTamano();
}

Album Usuario::obtenerAlbum(int indice) const
{
    return albumes.obtenerElemento(indice);
}

Lista<string>& Usuario::obtenerListaAmigos()
{
    return amigos;
}

Lista<Mensaje>& Usuario::obtenerMensajesRecibidos()
{
    return mensajesRecibidos;
}

Lista<Album>& Usuario::obtenerAlbumes()
{
    return albumes;
}

void Usuario::setContrasena(string contrasena)
{
    this->contrasena = contrasena;
}