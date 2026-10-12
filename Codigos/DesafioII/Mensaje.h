#ifndef MENSAJE_H
#define MENSAJE_H

#include <string>
#include <iostream>

using namespace std;

class Mensaje
{
private:
    string emisor;
    string receptor;
    string textoContenido;
    string fechaEnvio;
    bool leido;

public:
    Mensaje();
    Mensaje(string emisor, string receptor, string texto);
    Mensaje(const Mensaje& otro);

    ~Mensaje();

    void marcarComoLeido();

    string getEmisor() const;
    string getReceptor() const;
    string getTextoContenido() const;
    string getFechaEnvio() const;
    bool getLeido() const;

    void setFechaEnvio(string fecha);

    bool operator==(const Mensaje& otro) const;
    bool operator<(const Mensaje& otro) const;

    friend ostream& operator<<(ostream& os, const Mensaje& mensaje);
};

#endif