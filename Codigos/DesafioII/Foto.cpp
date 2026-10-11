#ifndef FOTO_H
#define FOTO_H

#include <string>
using namespace std;

class Foto
{
private:
    string fechaCaptura;
    unsigned int tamanoBytes;
    string rutaArchivo;
    int conteoLikes;

public:
    Foto();
    Foto(const Foto& otra);
    Foto(string fecha, unsigned int tamano, string ruta);

    ~Foto();

    void darLike();
    void quitarLike();

    string getRutaArchivo() const;
    string getFechaCaptura() const;
    unsigned int getTamanoBytes() const;
    int getConteoLikes() const;

    void setFechaCaptura(string fecha);
    void setTamanoBytes(unsigned int tamano);
    void setRutaArchivo(string ruta);
};

#endif