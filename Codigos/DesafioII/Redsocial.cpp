#include "Redsocial.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

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

int Redsocial::buscarIndiceUsuario(const string& username) {
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

Usuario* Redsocial::buscarUsuarioPorNombre(const string& nombre) {
    int idx = buscarIndiceUsuario(nombre);
    if (idx != -1) return &usuarios[idx];
    return nullptr;
}

bool Redsocial::cargarDatosAlmacenamiento() {
    monitor.reiniciarContadores();

    ifstream fileUsers("usuarios.txt");
    if (!fileUsers.is_open()) return false;

    string linea;
    while (getline(fileUsers, linea)) {
        monitor.incrementarIteracion(1);
        if (linea.empty()) continue;

        stringstream ss(linea);
        string user, pass, foto, email, ciudad;

        getline(ss, user, '|');
        getline(ss, pass, '|');
        getline(ss, foto, '|');
        getline(ss, email, '|');
        getline(ss, ciudad, '|');

        Usuario u(user, pass, foto);
        u.setEmail(email);
        u.setCiudad(ciudad);
        agregarUsuario(u);
    }
    fileUsers.close();

    ifstream fileMatriz("matriz_adyacencia.txt");
    if (fileMatriz.is_open()) {
        int i = 0;
        while (getline(fileMatriz, linea) && i < capacidadUsuarios) {
            monitor.incrementarIteracion(1);
            if (linea.empty()) continue;

            stringstream ss(linea);
            string val;
            int j = 0;

            while (getline(ss, val, ',') && j < capacidadUsuarios) {
                if (!val.empty()) {
                    int estadoAmistad = stoi(val);
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

    ifstream fileAlbums("albums_fotos.txt");
    if (fileAlbums.is_open()) {
        while (getline(fileAlbums, linea)) {
            monitor.incrementarIteracion(1);
            if (linea.empty()) continue;

            stringstream ss(linea);
            string user, nomAlbum, priv, rutaFoto, fecha, strLikes;

            getline(ss, user, '|');
            getline(ss, nomAlbum, '|');
            getline(ss, priv, '|');
            getline(ss, rutaFoto, '|');
            getline(ss, fecha, '|');
            getline(ss, strLikes, '|');

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

                int likes = strLikes.empty() ? 0 : stoi(strLikes);
                Foto nuevaFoto(fecha, 2048, rutaFoto);
                for (int l = 0; l < likes; ++l) nuevaFoto.darLike();

                uRef.obtenerAlbum(idxAlb).agregarFoto(nuevaFoto);
            }
        }
        fileAlbums.close();
    }

    // REGISTRO DEL MENSAJE DE HACE 6 SEMANAS DE usuario2 PARA usuario1
    Usuario* u1 = buscarUsuarioPorNombre("usuario1");
    if (u1 != nullptr) {
        Mensaje msgAntiguo("usuario2", "usuario1", "Hola Me dejastes envisto >:( ", "2026-09-04");
        u1->recibirMensaje(msgAntiguo);
    }

    cout << "Se completo la carga correctamente." << endl;
    return true;
}

bool Redsocial::guardarDatosAlmacenamiento() {
    ofstream fileAlbums("albums_fotos.txt");
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

Usuario* Redsocial::autenticarUsuario(const string& username, const string& pass) {
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

bool Redsocial::enviarSolicitudAmistad(const string& origen, const string& destino) {
    Usuario* uDestino = buscarUsuarioPorNombre(destino);
    if (uDestino != nullptr) {
        uDestino->agregarSolicitud(origen);
        return true;
    }
    return false;
}

bool Redsocial::aceptarSolicitudAmistad(const string& destinatario, const string& remitente) {
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

bool Redsocial::enviarMensaje(const string& emisor, const string& receptor, const string& texto) {
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

    cout << "\n--- MEJORES AMIGOS ---" << endl;
    int mostrados = 0;
    for (int j = 0; j < usuarios.obtenerTamano() && mostrados < 3; ++j) {
        monitor.incrementarIteracion(1);
        if (matrizAdyacencia[idxActual][j] == 1) {
            cout << "Amigo: " << usuarios[j].getUsername()
            << " | Foto: " << usuarios[j].getFotoPerfilRuta() << endl;
            mostrados++;
        }
    }
}

void Redsocial::verSugerenciasAmigos(int K) {
    if (!usuarioAutenticado) return;

    int idxUsuario = buscarIndiceUsuario(usuarioAutenticado->getUsername());
    if (idxUsuario == -1) return;

    int numUsuarios = usuarios.obtenerTamano();
    int* amigosEnComun = new int[numUsuarios]();
    monitor.registrarAsignacion(sizeof(int) * numUsuarios);

    for (int j = 0; j < numUsuarios; ++j) {
        monitor.incrementarIteracion(1);
        if (matrizAdyacencia[idxUsuario][j] == 1) {
            for (int k = 0; k < numUsuarios; ++k) {
                monitor.incrementarIteracion(1);
                if (matrizAdyacencia[j][k] == 1 && k != idxUsuario && matrizAdyacencia[idxUsuario][k] == 0) {
                    amigosEnComun[k]++;
                }
            }
        }
    }

    cout << "\n========================================================" << endl;
    cout << "        SUGERENCIAS DE AMISTAD (TOP " << K << ")        " << endl;
    cout << "========================================================" << endl;

    int sugerenciasMostradas = 0;

    for (int s = 0; s < K; ++s) {
        int maxCoincidencias = 0;
        int idxMejorSugerencia = -1;

        for (int i = 0; i < numUsuarios; ++i) {
            monitor.incrementarIteracion(1);
            if (amigosEnComun[i] > maxCoincidencias) {
                maxCoincidencias = amigosEnComun[i];
                idxMejorSugerencia = i;
            }
        }

        if (idxMejorSugerencia != -1 && maxCoincidencias > 0) {
            sugerenciasMostradas++;
            cout << " " << sugerenciasMostradas << ". " << usuarios[idxMejorSugerencia].getUsername()
                 << " | " << maxCoincidencias << " amigos en común"
                 << " | Foto: " << usuarios[idxMejorSugerencia].getFotoPerfilRuta() << endl;

            amigosEnComun[idxMejorSugerencia] = 0;
        } else {
            break;
        }
    }

    if (sugerenciasMostradas == 0) {
        cout << "No se encontraron sugerencias de amistad con amigos en común en este momento." << endl;
    }

    delete[] amigosEnComun;
    monitor.registrarLiberacion(sizeof(int) * numUsuarios);
}

void Redsocial::mostrarRecursos() {
    cout << "\n=== CONSUMO DE RECURSOS ===" << endl;
    cout << "Memoria consumida: " << monitor.obtenerMemoriaConsumida() << " bytes." << endl;
    cout << "Iteraciones ejecutadas: " << monitor.obtenerIteraciones() << endl;
}

Manejorecursos& Redsocial::getMonitor() {
    return monitor;
}