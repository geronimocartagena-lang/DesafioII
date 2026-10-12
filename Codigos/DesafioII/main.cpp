#include <iostream>
#include <string>
#include <limits>

#include "Redsocial.h"

using namespace std;

int main()
{
    Redsocial red;

    Usuario ana("ana", "1234");
    Usuario bruno("bruno", "1234");
    Usuario camila("camila", "1234");
    Usuario david("david", "1234");

    red.agregarUsuario(ana);
    red.agregarUsuario(bruno);
    red.agregarUsuario(camila);
    red.agregarUsuario(david);

    red.enviarSolicitudAmistad("ana", "bruno");
    red.aceptarSolicitudAmistad("bruno", "ana");

    red.enviarSolicitudAmistad("ana", "camila");
    red.aceptarSolicitudAmistad("camila", "ana");

    int opcion = 0;

    do
    {
        cout << "\n===== Ude@Book =====\n";
        cout << "1. Iniciar sesion\n";
        cout << "2. Cargar datos\n";
        cout << "3. Guardar datos\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";


        if (!(cin >> opcion))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = -1;
            continue;
        }

        if (opcion == 1)
        {
            string nombre;
            string contrasena;

            cout << "Usuario: ";
            cin >> nombre;

            cout << "Contrasena: ";
            cin >> contrasena;

            Usuario* usuario =
                red.autenticarUsuario(nombre, contrasena);

            if (usuario == nullptr)
            {
                cout << "Credenciales incorrectas.\n";
                continue;
            }

            int opcionUsuario = -1;

            do
            {
                cout << "\n===== Menu principal =====\n";
                cout << "Usuario: "
                     << usuario->getUsername() << '\n';
                cout << "1. Enviar solicitud de amistad\n";
                cout << "2. Ver solicitudes recibidas\n";
                cout << "3. Aceptar solicitud de amistad\n";
                cout << "4. Enviar mensaje\n";
                cout << "5. Leer mensajes recibidos\n";
                cout << "6. Ver amigos\n";
                cout << "7. Ver sugerencias\n";
                cout << "8. Visitar albumes de un amigo\n";
                cout << "9. Ver consumo de recursos\n";
                cout << "0. Cerrar sesion\n";
                cout << "Opcion: ";

                if (!(cin >> opcionUsuario))
                {
                    cin.clear();
                    cin.ignore(
                        numeric_limits<streamsize>::max(), '\n');
                    opcionUsuario = -1;
                    continue;
                }

                if (opcionUsuario == 1)
                {
                    string destino;

                    cout << "Nombre del usuario: ";
                    cin >> destino;

                    if (red.enviarSolicitudAmistad(
                            usuario->getUsername(), destino))
                    {
                        cout << "Solicitud enviada.\n";
                    }
                    else
                    {
                        cout << "No se pudo enviar la solicitud.\n";
                    }
                }
                else if (opcionUsuario == 2)
                {
                    for (int i = 0;
                         i < usuario->obtenerCantidadSolicitudes();
                         i++)
                    {
                        cout << i + 1 << ". "
                             << usuario->obtenerSolicitud(i)
                             << '\n';
                    }

                    if (usuario->obtenerCantidadSolicitudes() == 0)
                    {
                        cout << "No hay solicitudes pendientes.\n";
                    }
                }
                else if (opcionUsuario == 3)
                {
                    string remitente;

                    cout << "Usuario que envio la solicitud: ";
                    cin >> remitente;

                    if (red.aceptarSolicitudAmistad(
                            usuario->getUsername(), remitente))
                    {
                        cout << "Solicitud aceptada.\n";
                    }
                    else
                    {
                        cout << "No se encontro esa solicitud.\n";
                    }
                }
                else if (opcionUsuario == 4)
                {
                    string destino;
                    string texto;

                    cout << "Enviar a: ";
                    cin >> destino;

                    cin.ignore(
                        numeric_limits<streamsize>::max(), '\n');

                    cout << "Escriba el mensaje: ";
                    getline(cin, texto);

                    if (red.enviarMensaje(
                            usuario->getUsername(), destino, texto))
                    {
                        cout << "Mensaje enviado.\n";
                    }
                    else
                    {
                        cout << "No se pudo enviar el mensaje.\n";
                    }
                }
                else if (opcionUsuario == 5)
                {
                    for (int i = 0;
                         i < usuario->obtenerCantidadMensajesRecibidos();
                         i++)
                    {
                        Mensaje mensaje =
                            usuario->obtenerMensajeRecibido(i);

                        cout << '\n' << mensaje << '\n';

                        if (!mensaje.getLeido())
                        {
                            usuario->marcarMensajeLeido(i);
                        }
                    }

                    if (usuario->obtenerCantidadMensajesRecibidos() == 0)
                    {
                        cout << "No hay mensajes recibidos.\n";
                    }
                }
                else if (opcionUsuario == 6)
                {
                    for (int i = 0;
                         i < usuario->obtenerCantidadAmigos();
                         i++)
                    {
                        cout << i + 1 << ". "
                             << usuario->obtenerAmigo(i) << '\n';
                    }
                }
                else if (opcionUsuario == 7)
                {
                    Lista<Usuario> sugerencias =
                        red.obtenerSugerenciasAmigos(*usuario);

                    for (int i = 0;
                         i < sugerencias.obtenerTamano() && i < 20;
                         i++)
                    {
                        cout << i + 1 << ". "
                             << sugerencias[i].getUsername() << '\n';
                    }
                }
                else if (opcionUsuario == 8)
                {
                    string nombreAmigo;

                    cout << "Nombre del amigo: ";
                    cin >> nombreAmigo;

                    Usuario* amigo =
                        red.buscarUsuarioPorNombre(nombreAmigo);

                    if (amigo == nullptr || !usuario->esAmigo(nombreAmigo))
                    {
                        cout << "No se encontro ese amigo.\n";
                    }
                    else
                    {
                        for (int i = 0;
                             i < amigo->obtenerCantidadAlbumes();
                             i++)
                        {
                            Album album = amigo->obtenerAlbum(i);

                            cout << i + 1 << ". "
                                 << album.getNombre()
                                 << " - Privacidad: "
                                 << album.getPrivacidad()
                                 << " - Fotos: "
                                 << album.obtenerCantidadFotos()
                                 << '\n';
                        }
                    }
                }
                else if (opcionUsuario == 9)
                {
                    red.mostrarRecursos();
                }

            } while (opcionUsuario != 0);
        }
        else if (opcion == 2)
        {
            if (red.cargarDatosAlmacenamiento())
            {
                cout << "Datos cargados.\n";
            }
            else
            {
                cout << "No se pudo abrir usuarios.txt.\n";
            }
        }
        else if (opcion == 3)
        {
            if (red.guardarDatosAlmacenamiento())
            {
                cout << "Datos guardados.\n";
            }
            else
            {
                cout << "No se pudieron guardar los datos.\n";
            }
        }

    } while (opcion != 0);

    return 0;
}