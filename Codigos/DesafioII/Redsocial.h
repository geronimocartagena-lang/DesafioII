#ifndef REDSOCIAL_H
#define REDSOCIAL_H

#include <string>
#include "Lista.h"
#include "Usuario.h"
#include "Manejorecursos.h"

using namespace std;

class Redsocial
{
private:
    Lista<Usuario> usuarios;
    string rutaAlmacenamiento;
    int capacidadUsuarios;
    Manejorecursos recursos;

    int buscarUsuario(string username) const;

public:
    Redsocial();
    ~Redsocial();

    bool cargarDatosAlmacenamiento();
    bool guardarDatosAlmacenamiento();

    Usuario* autenticarUsuario(string usuario, string password);

    Lista<Usuario> obtenerSugerenciasAmigos(Usuario& usuario);
    Lista<Usuario> obtenerMejoresAmigos(Usuario& usuario);

    bool agregarUsuario(const Usuario& usuario);
    bool enviarSolicitudAmistad(string origen, string destino);
    bool aceptarSolicitudAmistad(string destinatario, string remitente);
    bool enviarMensaje(string emisor, string receptor, string texto);

    Usuario* buscarUsuarioPorNombre(string username);

    void mostrarRecursos() const;
    Manejorecursos& obtenerManejadorRecursos();
};

#endif