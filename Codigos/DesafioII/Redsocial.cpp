#include "Redsocial.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Redsocial::Redsocial() {
    capacidadUsuarios = 1000;
    usuarioAutenticado = nullptr;

    matrizAdyacencia = new int*[capacidadUsuarios];
    monitor.registrarAsignacion(sizeof(int*) * capacidadUsuarios);

    for (int i = 0; i < capacidadUsuarios; ++i) {
        matrizAdyacencia[i] = new int[capacidadUsuarios];
        monitor.registrarAsignacion(sizeof(int) * capacidadUsuarios);
        for (int j = 0; j < capacidadUsuarios; ++j) {
            matrizAdyacencia[i][j] = 0;
        }
    }
}

Redsocial::~Redsocial() {
    if (matrizAdyacencia != nullptr) {
        for (int i = 0; i < capacidadUsuarios; ++i) {
            delete[] matrizAdyacencia[i];
            monitor.registrarLiberacion(sizeof(int) * capacidadUsuarios);
        }
        delete[] matrizAdyacencia;
        monitor.registrarLiberacion(sizeof(int*) * capacidadUsuarios);
    }
}

int Redsocial::buscarIndiceUsuario(const std::string& username) {
    for (int i = 0; i < usuarios.obtenerTamano(); ++i) {
        monitor.incrementarIteracion(1);
        if (usuarios[i].getUsername() == username) {
            return i;
        }
    }
    return -1;
}

void Redsocial::agregarUsuario(const Usuario& u) {
    usuarios.agregarFinal(u);
    monitor.registrarAsignacion(sizeof(Usuario));
}

Usuario* Redsocial::buscarUsuarioPorNombre(const std::string& nombre) {
    int idx = buscarIndiceUsuario(nombre);
    if (idx != -1) return &usuarios[idx];
    return nullptr;
}

bool Redsocial::cargarDatosAlmacenamiento() {
    monitor.reiniciarContadores();

    // 1. CARGA DE USUARIOS (usuarios.txt)
    std::ifstream fileUsers("usuarios.txt");
    if (!fileUsers.is_open()) return false;

    std::string linea;
    while (std::getline(fileUsers, linea)) {
        monitor.incrementarIteracion(1);
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string user, pass, foto, email, ciudad;

        std::getline(ss, user, '|');
        std::getline(ss, pass, '|');
        std::getline(ss, foto, '|');
        std::getline(ss, email, '|');
        std::getline(ss, ciudad, '|');

        Usuario u(user, pass, foto);
        agregarUsuario(u);
    }
    fileUsers.close();

    // 2. CARGA DE LA MATRIZ DE ADYACENCIA (matriz_adyacencia.txt)
    std::ifstream fileMatriz("matriz_adyacencia.txt");
    if (fileMatriz.is_open()) {
        int i = 0;
        while (std::getline(fileMatriz, linea) && i < capacidadUsuarios) {
            monitor.incrementarIteracion(1);
            if (linea.empty()) continue;

            std::stringstream ss(linea);
            std::string val;
            int j = 0;

            while (std::getline(ss, val, ',') && j < capacidadUsuarios) {
                if (!val.empty()) {
                    int estadoAmistad = std::stoi(val);
                    matrizAdyacencia[i][j] = estadoAmistad;

                    if (estadoAmistad == 1 && i != j) {
                        usuarios[i].agregarAmigo(usuarios[j].getUsername());
                    }
                }
                j++;
            }
            i++;
        }
        fileMatriz.close();
    }

    // 3. CARGA DE ÁLBUMES Y FOTOS (albums_fotos.txt)
    std::ifstream fileAlbums("albums_fotos.txt");
    if (fileAlbums.is_open()) {
        while (std::getline(fileAlbums, linea)) {
            monitor.incrementarIteracion(1);
            if (linea.empty()) continue;

            std::stringstream ss(linea);
            std::string user, nomAlbum, priv, rutaFoto, fecha, strLikes;

            std::getline(ss, user, '|');
            std::getline(ss, nomAlbum, '|');
            std::getline(ss, priv, '|');
            std::getline(ss, rutaFoto, '|');
            std::getline(ss, fecha, '|');
            std::getline(ss, strLikes, '|');

            int idxU = buscarIndiceUsuario(user);
            if (idxU != -1) {
                Usuario& uRef = usuarios[idxU];

                int idxAlb = -1;
                for (int a = 0; a < uRef.obtenerCantidadAlbumes(); ++a) {
                    if (uRef.obtenerAlbum(a).getNombre() == nomAlbum) {
                        idxAlb = a;
                        break;
                    }
                }

                if (idxAlb == -1) {
                    Album nuevoAlb(nomAlbum, "/users/udeabook/static/" + user + "/albums/" + nomAlbum, priv);
                    uRef.agregarAlbum(nuevoAlb);
                    idxAlb = uRef.obtenerCantidadAlbumes() - 1;
                }

                int likes = strLikes.empty() ? 0 : std::stoi(strLikes);
                Foto nuevaFoto(fecha, 2048, rutaFoto);
                for (int l = 0; l < likes; ++l) nuevaFoto.darLike();

                uRef.obtenerAlbum(idxAlb).agregarFoto(nuevaFoto);
            }
        }
        fileAlbums.close();
    }

    std::cout << "[CARGA COMPLETA] Datos y estructuras cargados correctamente." << std::endl;
    return true;
}

bool Redsocial::guardarDatosAlmacenamiento() {
    std::ofstream fileAlbums("albums_fotos.txt");
    if (!fileAlbums.is_open()) return false;

    for (int i = 0; i < usuarios.obtenerTamano(); ++i) {
        Usuario& u = usuarios[i];
        for (int a = 0; a < u.obtenerCantidadAlbumes(); ++a) {
            Album& alb = u.obtenerAlbum(a);
            for (int f = 0; f < alb.obtenerCantidadFotos(); ++f) {
                Foto& foto = alb.obtenerFoto(f);
                fileAlbums << u.getUsername() << "|"
                           << alb.getNombre() << "|"
                           << alb.getPrivacidad() << "|"
                           << foto.getRutaArchivo() << "|"
                           << foto.getFechaCaptura() << "|"
                           << foto.getConteoLikes() << "\n";
            }
        }
    }
    fileAlbums.close();
    return true;
}

Usuario* Redsocial::autenticarUsuario(const std::string& username, const std::string& pass) {
    int idx = buscarIndiceUsuario(username);
    if (idx != -1 && usuarios[idx].getContrasena() == pass) {
        usuarioAutenticado = &usuarios[idx];
        return usuarioAutenticado;
    }
    return nullptr;
}

void Redsocial::cerrarSesion() {
    usuarioAutenticado = nullptr;
}

Usuario* Redsocial::getUsuarioAutenticado() {
    return usuarioAutenticado;
}

bool Redsocial::enviarSolicitudAmistad(const std::string& origen, const std::string& destino) {
    Usuario* uDestino = buscarUsuarioPorNombre(destino);
    if (uDestino != nullptr) {
        uDestino->agregarSolicitud(origen);
        return true;
    }
    return false;
}

bool Redsocial::aceptarSolicitudAmistad(const std::string& destinatario, const std::string& remitente) {
    int idx1 = buscarIndiceUsuario(destinatario);
    int idx2 = buscarIndiceUsuario(remitente);

    if (idx1 != -1 && idx2 != -1) {
        matrizAdyacencia[idx1][idx2] = 1;
        matrizAdyacencia[idx2][idx1] = 1;
        usuarios[idx1].agregarAmigo(remitente);
        usuarios[idx2].agregarAmigo(destinatario);
        return true;
    }
    return false;
}

bool Redsocial::enviarMensaje(const std::string& emisor, const std::string& receptor, const std::string& texto) {
    Usuario* uReceptor = buscarUsuarioPorNombre(receptor);
    if (uReceptor != nullptr) {
        Mensaje msg(emisor, receptor, texto);
        uReceptor->recibirMensaje(msg);
        return true;
    }
    return false;
}

void Redsocial::mostrarMejoresAmigos() {
    if (!usuarioAutenticado) return;
    int idxActual = buscarIndiceUsuario(usuarioAutenticado->getUsername());
    if (idxActual == -1) return;

    std::cout << "\n--- MEJORES AMIGOS ---" << std::endl;
    int mostrados = 0;
    for (int j = 0; j < usuarios.obtenerTamano() && mostrados < 3; ++j) {
        monitor.incrementarIteracion(1);
        if (matrizAdyacencia[idxActual][j] == 1) {
            std::cout << "Amigo: " << usuarios[j].getUsername()
            << " | Foto: " << usuarios[j].getFotoPerfilRuta() << std::endl;
            mostrados++;
        }
    }
}

void Redsocial::verSugerenciasAmigos(int K) {
    std::cout << "\n--- SUGERENCIAS DE AMISTAD (" << K << ") ---" << std::endl;
}

void Redsocial::mostrarRecursos() {
    std::cout << "\n=== CONSUMO DE RECURSOS ===" << std::endl;
    std::cout << "Memoria consumida: " << monitor.obtenerMemoriaConsumida() << " bytes." << std::endl;
    std::cout << "Iteraciones ejecutadas: " << monitor.obtenerIteraciones() << std::endl;
}

Manejorecursos& Redsocial::getMonitor() {
    return monitor;
}