#include <iostream>
#include <string>
#include "Redsocial.h"
#include "Usuario.h"
#include "Album.h"
#include "Foto.h"
#include "Mensaje.h"

using namespace std;

// Prototipos de submenús LISTA ENLASADA
void menuAdministrarAmistades(Redsocial& red, Usuario* usuario);
void menuVisitarPerfilAmigo(Redsocial& red, Usuario* usuario);
void menuVerSugerencias(Redsocial& red, Usuario* usuario);
void menuAdministrarMensajes(Redsocial& red, Usuario* usuario);

void mostrarPantallaPrincipal(Redsocial& red, Usuario* usuario) {
    cout << "\n========================================================" << endl;
    // Muestra 3 mejores amigos (fotos de perfil) con prioridad por coincidencias
    red.mostrarMejoresAmigos();

    cout << "\nBienvenido a UdeaBook // " << usuario->getUsername() << endl;
    cout << "========================================================" << endl;
    cout << "Menú de opciones:" << endl;
    cout << "  1.- Administrar amistades" << endl;
    cout << "  2.- Visitar perfil de un amigo" << endl;
    cout << "  3.- Ver sugerencias de amistad" << endl;
    cout << "  4.- Administrar mensajes" << endl;
    cout << "  5.- Medición global del consumo de recursos" << endl;
    cout << "\n.- Ingrese 'N' o 'n' para alternar el grupo de fotos de perfil de amigos." << endl;
    cout << ".- Ingrese 'S' o 's' para cerrar su sesión." << endl;
    cout << "Su opción: ";
}

int main() {
    Redsocial red;

    // Carga de los 1000 usuarios y relaciones desde usuarios.txt al iniciar
    cout << "=== INICIALIZANDO UDE@BOOK ===" << endl;
    if (!red.cargarDatosAlmacenamiento()) {
        cout << "Error grave: No se pudo cargar el archivo 'usuarios.txt'." << endl;
        cout << "Asegúrese de generar el dataset de 1000 usuarios primero." << endl;
        return 1;
    }

    bool ejecucionActiva = true;

    while (ejecucionActiva) {
        cout << "\n=========================================" << endl;
        cout << "         INICIO DE SESIÓN UDE@BOOK        " << endl;
        cout << "=========================================" << endl;

        string username, password;
        cout << "Nombre de usuario (o '0' para salir del programa): ";
        cin >> username;

        if (username == "0") {
            ejecucionActiva = false;
            break;
        }

        cout << "Contraseña: ";
        cin >> password;

        Usuario* usuarioLogueado = red.autenticarUsuario(username, password);

        if (usuarioLogueado == nullptr) {
            cout << "\n Credenciales incorrectas. Intente nuevamente." << endl;
            continue;
        }

        cout << "\n Autenticación correcta." << endl;

        // Bucle de sesión del usuario autenticado
        bool sesionActiva = true;
        while (sesionActiva) {
            mostrarPantallaPrincipal(red, usuarioLogueado);

            string entradaOp;
            cin >> entradaOp;

            if (entradaOp == "S" || entradaOp == "s") {
                red.cerrarSesion();
                cout << "\nSesión cerrada exitosamente." << endl;
                sesionActiva = false;
            }
            else if (entradaOp == "N" || entradaOp == "n") {
                // Refresca/alterna el grupo de 3 mejores amigos mostrados
                cout << "\n[Actualizando grupo de fotos de perfil de amigos...]" << endl;
                red.mostrarMejoresAmigos();
            }
            else if (entradaOp == "1") {
                menuAdministrarAmistades(red, usuarioLogueado);
            }
            else if (entradaOp == "2") {
                menuVisitarPerfilAmigo(red, usuarioLogueado);
            }
            else if (entradaOp == "3") {
                menuVerSugerencias(red, usuarioLogueado);
            }
            else if (entradaOp == "4") {
                menuAdministrarMensajes(red, usuarioLogueado);
            }
            else if (entradaOp == "5") {
                red.mostrarRecursos();
            }
            else {
                cout << "\nOpción no válida. Intente de nuevo." << endl;
            }
        }
    }

    cout << "\nGracias por utilizar Ude@Book." << endl;
    return 0;
}

// -----------------------------------------------------------------------------
// IMPLEMENTACIÓN DE SUBMENÚS FUNCIONALES (III, IV, V, VI)
// -----------------------------------------------------------------------------

void menuAdministrarAmistades(Redsocial& red, Usuario* usuario) {
    cout << "\n--- III. ADMINISTRAR AMISTADES ---" << endl;
    cout << "1. Enviar solicitud de amistad" << endl;
    cout << "2. Aceptar solicitudes de amistad recibidas (" << usuario->obtenerCantidadSolicitudes() << " pendientes)" << endl;
    cout << "0. Volver al menú principal" << endl;
    cout << "Selección: ";

    int op;
    cin >> op;

    if (op == 1) {
        string destino;
        cout << "Ingrese el nombre de usuario a solicitar amistad: ";
        cin >> destino;

        if (red.enviarSolicitudAmistad(usuario->getUsername(), destino)) {
            cout << "Solicitud enviada exitosamente a " << destino << "." << endl;
        } else {
            cout << "No se pudo enviar la solicitud (el usuario no existe o ya son amigos)." << endl;
        }
    } else if (op == 2) {
        if (usuario->obtenerCantidadSolicitudes() == 0) {
            cout << "No tienes solicitudes de amistad pendientes." << endl;
        } else {
            cout << "\nSolicitudes pendientes:" << endl;
            for (int i = 0; i < usuario->obtenerCantidadSolicitudes(); ++i) {
                cout << "  " << (i + 1) << ". " << usuario->obtenerSolicitud(i) << endl;
            }
            cout << "Ingrese el número de la solicitud a aceptar (o 0 para cancelar): ";
            int sel;
            cin >> sel;
            if (sel > 0 && sel <= usuario->obtenerCantidadSolicitudes()) {
                string remitente = usuario->obtenerSolicitud(sel - 1);
                red.aceptarSolicitudAmistad(usuario->getUsername(), remitente);
                cout << "¡Ahora eres amigo de " << remitente << "!" << endl;
            }
        }
    }
    red.mostrarRecursos();
}

void menuVisitarPerfilAmigo(Redsocial& red, Usuario* usuario) {
    cout << "\n--- IV. VISITAR PERFIL DE UN AMIGO ---" << endl;
    string amigo;
    cout << "Ingrese el nombre de usuario del amigo: ";
    cin >> amigo;

    Usuario* uAmigo = red.buscarUsuarioPorNombre(amigo);
    if (uAmigo == nullptr || !usuario->esAmigo(amigo)) {
        cout << "El usuario especificado no existe o no se encuentra en tu lista de amigos." << endl;
        red.mostrarRecursos();
        return;
    }

    cout << "\nPerfil de: " << uAmigo->getUsername() << " | Foto: " << uAmigo->getFotoPerfilRuta() << endl;
    cout << "Álbumes disponibles: " << uAmigo->obtenerCantidadAlbumes() << endl;

    if (uAmigo->obtenerCantidadAlbumes() == 0) {
        cout << "Este amigo no tiene álbumes creados." << endl;
        red.mostrarRecursos();
        return;
    }

    for (int i = 0; i < uAmigo->obtenerCantidadAlbumes(); ++i) {
        cout << "  " << (i + 1) << ". " << uAmigo->obtenerAlbum(i).getNombre() << endl;
    }

    cout << "Seleccione el número del álbum a explorar: ";
    int idxAlb;
    cin >> idxAlb;

    if (idxAlb > 0 && idxAlb <= uAmigo->obtenerCantidadAlbumes()) {
        Album& alb = uAmigo->obtenerAlbum(idxAlb - 1);
        cout << "\n=== CARRUSEL DE FOTOS: " << alb.getNombre() << " ===" << endl;

        bool enCarrusel = true;
        while (enCarrusel) {
            Foto& fActual = alb.obtenerFotoSiguiente();
            cout << "\n[Foto actual]: " << fActual.getRutaArchivo() << " | Likes: " << fActual.getConteoLikes() << endl;
            cout << "Opciones: [1] Siguiente | [2] Anterior | [3] Dar/Quitar Like | [0] Salir del álbum" << endl;
            cout << "Opción: ";
            int opC;
            cin >> opC;

            if (opC == 1) {
                // Siguiente se llama automáticamente en el loop
            } else if (opC == 2) {
                alb.obtenerFotoAnterior();
            } else if (opC == 3) {
                fActual.darLike();
                cout << "¡Like actualizado!" << endl;
            } else if (opC == 0) {
                enCarrusel = false;
            }
        }
    }
    red.mostrarRecursos();
}

void menuVerSugerencias(Redsocial& red, Usuario* usuario) {
    cout << "\n--- V. VER SUGERENCIAS DE AMISTAD ---" << endl;
    int K;
    cout << "Ingrese la cantidad K de sugerencias deseada (1 a 20): ";
    cin >> K;

    if (K < 1) K = 1;
    if (K > 20) K = 20;

    red.verSugerenciasAmigos(K);

    cout << "\n¿Desea enviar solicitud de amistad a alguna sugerencia? (S/N): ";
    char resp;
    cin >> resp;

    if (resp == 'S' || resp == 's') {
        string nomSug;
        cout << "Ingrese el nombre de usuario: ";
        cin >> nomSug;
        red.enviarSolicitudAmistad(usuario->getUsername(), nomSug);
        cout << "Solicitud enviada a " << nomSug << "." << endl;
    }
    red.mostrarRecursos();
}

void menuAdministrarMensajes(Redsocial& red, Usuario* usuario) {
    cout << "\n--- VI. ADMINISTRAR MENSAJES ---" << endl;
    cout << "1. Enviar mensaje a un amigo" << endl;
    cout << "2. Leer nuevos mensajes (Bandeja de entrada)" << endl;
    cout << "3. Buscar mensajes por rango de fechas" << endl;
    cout << "0. Volver" << endl;
    cout << "Opción: ";

    int op;
    cin >> op;

    if (op == 1) {
        string destino, texto;
        cout << "Nombre del amigo: ";
        cin >> destino;
        cout << "Mensaje (hasta 512 caracteres): ";
        cin.ignore();
        getline(cin, texto);

        if (red.enviarMensaje(usuario->getUsername(), destino, texto)) {
            cout << "Mensaje enviado exitosamente." << endl;
        } else {
            cout << "No se pudo enviar el mensaje. Verifique si el usuario existe." << endl;
        }
    } else if (op == 2) {
        cout << "\n--- MENSAJES RECIBIDOS ---" << endl;
        if (usuario->obtenerCantidadMensajesRecibidos() == 0) {
            cout << "No tienes mensajes nuevos." << endl;
        } else {
            for (int i = 0; i < usuario->obtenerCantidadMensajesRecibidos(); ++i) {
                Mensaje& m = usuario->obtenerMensajeRecibido(i);
                cout << m << " [Estado: " << (m.isLeido() ? "Leído" : "NUEVO") << "]" << endl;
                usuario->marcarMensajeLeido(i);
            }
        }
    } else if (op == 3) {
        string fInicio, fFin;
        cout << "Ingrese fecha inicio (YYYY-MM-DD): ";
        cin >> fInicio;
        cout << "Ingrese fecha fin (YYYY-MM-DD): ";
        cin >> fFin;

        cout << "\nBuscando mensajes entre " << fInicio << " y " << fFin << "..." << endl;
        for (int i = 0; i < usuario->obtenerCantidadMensajesRecibidos(); ++i) {
            Mensaje& m = usuario->obtenerMensajeRecibido(i);
            if (m.getFechaEnvio() >= fInicio && m.getFechaEnvio() <= fFin) {
                cout << m << endl;
            }
        }
    }
    red.mostrarRecursos();
}