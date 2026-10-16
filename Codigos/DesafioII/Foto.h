#ifndef FOTO_H
#define FOTO_H

#include <string>

class Foto {
private:
    std::string fechaCaptura;
    unsigned int tamanoBytes;
    std::string rutaArchivo;
    int conteoLikes;

public:
    Foto();
    Foto(const Foto& otra);
    Foto(const std::string& fecha, unsigned int tam, const std::string& ruta);
    ~Foto();

    std::string getFechaCaptura() const;
    void setFechaCaptura(const std::string& fecha);

    unsigned int getTamanoBytes() const;
    void setTamanoBytes(unsigned int tam);

    std::string getRutaArchivo() const;
    void setRutaArchivo(const std::string& ruta);

    int getConteoLikes() const;

    void darLike();
    void quitarLike();
};

#endif // FOTO_H