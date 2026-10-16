#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include "Lista.h"
#include "Foto.h"

class Album {
private:
    std::string nombre;
    std::string rutaAlmacenamiento;
    std::string privacidad;
    Lista<Foto> fotos;
    int indiceFotoActual;

public:
    Album();
    Album(const Album& otro);
    Album(const std::string& nom, const std::string& ruta, const std::string& priv);
    ~Album();

    std::string getNombre() const;
    void setNombre(const std::string& nom);

    std::string getRutaAlmacenamiento() const;
    void setRutaAlmacenamiento(const std::string& ruta);

    std::string getPrivacidad() const;
    void setPrivacidad(const std::string& priv);

    void agregarFoto(const Foto& foto);
    int obtenerCantidadFotos() const;
    Foto& obtenerFoto(int index);

    Foto& obtenerFotoSiguiente();
    Foto& obtenerFotoAnterior();
};

#endif // ALBUM_H