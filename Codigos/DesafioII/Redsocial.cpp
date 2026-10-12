#include "Redsocial.h"
#include <fstream>
#include <iostream>

Redsocial::Redsocial()
{
    rutaAlmacenamiento = "usuarios.txt";
    capacidadUsuarios = 1000;
}

Redsocial::~Redsocial()
{
}

int Redsocial::buscarUsuario(string username) const
{
    for (int i = 0; i < usuarios.obtenerTamano(); i++)
    {
        if (usuarios[i].getUsername() == username)
        {
            return i;
        }
    }

    return -1;
}

bool Redsocial::agregarUsuario(const Usuario& usuario)
{
    if (buscarUsuario(usuario.getUsername()) != -1)
    {
        return false;
    }

    usuarios.agregarFinal(usuario);
    capacidadUsuarios = usuarios.obtenerTamano();
    return true;
}

bool Redsocial::cargarDatosAlmacenamiento()
{
    ifstream archivo(rutaAlmacenamiento);

    if (!archivo.is_open())
    {
        return false;
    }

    string username;
    string password;

    while (archivo >> username >> password)
    {
        Usuario nuevo(username, password);
        agregarUsuario(nuevo);
        recursos.incrementarIteracion();
    }

    archivo.close();
    return true;
}

bool Redsocial::guardarDatosAlmacenamiento()
{
    ofstream archivo(rutaAlmacenamiento);

    if (!archivo.is_open())
    {
        return false;
    }

    for (int i = 0; i < usuarios.obtenerTamano(); i++)
    {
        archivo << usuarios[i].getUsername() << " "
                << "1234" << '\n';
        recursos.incrementarIteracion();
    }

    archivo.close();
    return true;
}

Usuario* Redsocial::autenticarUsuario(string usuario, string password)
{
    int indice = buscarUsuario(usuario);

    if (indice == -1)
    {
        return nullptr;
    }

    if (!usuarios[indice].verificarContrasena(password))
    {
        return nullptr;
    }

    return &usuarios[indice];
}

bool Redsocial::enviarSolicitudAmistad(string origen, string destino)
{
    int indiceOrigen = buscarUsuario(origen);
    int indiceDestino = buscarUsuario(destino);

    if (indiceOrigen == -1 || indiceDestino == -1)
    {
        return false;
    }

    Usuario& usuarioOrigen = usuarios[indiceOrigen];
    Usuario& usuarioDestino = usuarios[indiceDestino];

    if (usuarioOrigen.esAmigo(destino) ||
        usuarioDestino.esAmigo(origen))
    {
        return false;
    }

    if (usuarioOrigen.tieneSolicitud(destino) ||
        usuarioDestino.tieneSolicitud(origen))
    {
        return false;
    }

    usuarioDestino.enviarSolicitud(origen);
    return true;
}

bool Redsocial::aceptarSolicitudAmistad(
    string destinatario, string remitente)
{
    int indiceDestino = buscarUsuario(destinatario);
    int indiceRemitente = buscarUsuario(remitente);

    if (indiceDestino == -1 || indiceRemitente == -1)
    {
        return false;
    }

    Usuario& destino = usuarios[indiceDestino];
    Usuario& origen = usuarios[indiceRemitente];

    if (!destino.aceptarSolicitud(remitente))
    {
        return false;
    }

    origen.agregarAmigo(destinatario);
    return true;
}

bool Redsocial::enviarMensaje(
    string emisor, string receptor, string texto)
{
    int indiceEmisor = buscarUsuario(emisor);
    int indiceReceptor = buscarUsuario(receptor);

    if (indiceEmisor == -1 || indiceReceptor == -1)
    {
        return false;
    }

    if (!usuarios[indiceEmisor].esAmigo(receptor))
    {
        return false;
    }

    if (texto.empty() || texto.length() > 512)
    {
        return false;
    }

    Mensaje mensaje(emisor, receptor, texto);

    usuarios[indiceEmisor].agregarMensajeEnviado(mensaje);
    usuarios[indiceReceptor].agregarMensajeRecibido(mensaje);

    return true;
}

Usuario* Redsocial::buscarUsuarioPorNombre(string username)
{
    int indice = buscarUsuario(username);

    if (indice == -1)
    {
        return nullptr;
    }

    return &usuarios[indice];
}

Lista<Usuario> Redsocial::obtenerSugerenciasAmigos(Usuario& usuario)
{
    Lista<Usuario> sugerencias;

    for (int i = 0; i < usuarios.obtenerTamano(); i++)
    {
        Usuario& candidato = usuarios[i];

        if (candidato.getUsername() == usuario.getUsername())
        {
            continue;
        }

        if (!usuario.esAmigo(candidato.getUsername()) &&
            !usuario.tieneSolicitud(candidato.getUsername()))
        {
            sugerencias.agregarFinal(candidato);
        }
    }

    return sugerencias;
}

Lista<Usuario> Redsocial::obtenerMejoresAmigos(Usuario& usuario)
{
    Lista<Usuario> mejores;

    for (int i = 0; i < usuario.obtenerCantidadAmigos(); i++)
    {
        string nombreAmigo = usuario.obtenerAmigo(i);
        int indice = buscarUsuario(nombreAmigo);

        if (indice != -1)
        {
            mejores.agregarFinal(usuarios[indice]);
        }
    }

    return mejores;
}

void Redsocial::mostrarRecursos() const
{
    cout << "\n Consumo de recursos \n";
    cout << "Iteraciones registradas: "
         << recursos.obtenerIteraciones() << '\n';
    cout << "Memoria registrada: "
         << recursos.obtenerMemoriaConsumida()
         << " bytes\n";
}

Manejorecursos& Redsocial::obtenerManejadorRecursos()
{
    return recursos;
}