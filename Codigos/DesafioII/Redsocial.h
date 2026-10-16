#ifndef REDSOCIAL_H
#define REDSOCIAL_H

#include <string>
#include "Usuario.h"
#include "Lista.h"
#include "Album.h"
#include "Foto.h"
#include "Manejorecursos.h"

class Redsocial {
private:
    Lista<Usuario> usuarios;
    int** matrizAdyacencia;
    int capacidadUsuarios;
    Usuario* usuarioAutenticado;
    Manejorecursos monitor;

    int buscarIndiceUsuario(const std::string& username);

public:
    Redsocial();
    ~Redsocial();

    void agregarUsuario(const Usuario& u);
    Usuario* buscarUsuarioPorNombre(const std::string& nombre);

    bool cargarDatosAlmacenamiento();
    bool guardarDatosAlmacenamiento();

    Usuario* autenticarUsuario(const std::string& username, const std::string& pass);
    void cerrarSesion();
    Usuario* getUsuarioAutenticado();

    bool enviarSolicitudAmistad(const std::string& origen, const std::string& destino);
    bool aceptarSolicitudAmistad(const std::string& destinatario, const std::string& remitente);
    bool enviarMensaje(const std::string& emisor, const std::string& receptor, const std::string& texto);

    void mostrarMejoresAmigos();
    void verSugerenciasAmigos(int K);
    void mostrarRecursos();

    Manejorecursos& getMonitor();
};

#endif // REDSOCIAL_H