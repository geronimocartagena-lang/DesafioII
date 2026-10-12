#include "Mensaje.h"
#include <ctime>

Mensaje::Mensaje()
{
    emisor = "";
    receptor = "";
    textoContenido = "";
    fechaEnvio = "";
    leido = false;
}

Mensaje::Mensaje(string emisor, string receptor, string texto)
{
    this->emisor = emisor;
    this->receptor = receptor;
    textoContenido = texto;
    leido = false;

    time_t ahora = time(nullptr);
    tm* fecha = localtime(&ahora);

    if (fecha != nullptr)
    {
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", fecha);
        fechaEnvio = buffer;
    }
}

Mensaje::Mensaje(const Mensaje& otro)
{
    emisor = otro.emisor;
    receptor = otro.receptor;
    textoContenido = otro.textoContenido;
    fechaEnvio = otro.fechaEnvio;
    leido = otro.leido;
}

Mensaje::~Mensaje()
{
}

void Mensaje::marcarComoLeido()
{
    leido = true;
}

string Mensaje::getEmisor() const
{
    return emisor;
}

string Mensaje::getReceptor() const
{
    return receptor;
}

string Mensaje::getTextoContenido() const
{
    return textoContenido;
}

string Mensaje::getFechaEnvio() const
{
    return fechaEnvio;
}

bool Mensaje::getLeido() const
{
    return leido;
}

void Mensaje::setFechaEnvio(string fecha)
{
    fechaEnvio = fecha;
}

bool Mensaje::operator==(const Mensaje& otro) const
{
    return emisor == otro.emisor &&
           receptor == otro.receptor &&
           fechaEnvio == otro.fechaEnvio &&
           textoContenido == otro.textoContenido;
}

bool Mensaje::operator<(const Mensaje& otro) const
{
    return fechaEnvio < otro.fechaEnvio;
}

ostream& operator<<(ostream& os, const Mensaje& mensaje)
{
    os << "De: " << mensaje.emisor << '\n';
    os << "Para: " << mensaje.receptor << '\n';
    os << "Fecha: " << mensaje.fechaEnvio << '\n';
    os << "Mensaje: " << mensaje.textoContenido << '\n';
    os << "Estado: " << (mensaje.leido ? "Leido" : "No leido");

    return os;
}