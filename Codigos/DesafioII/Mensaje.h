#ifndef MENSAJE_H
#define MENSAJE_H

#include <string>
#include <iostream>

class Mensaje {
private:
    std::string emisor;
    std::string receptor;
    std::string textoContenido;
    std::string fechaEnvio;
    bool leido;

public:
    Mensaje();
    Mensaje(const Mensaje& otro);
    Mensaje(const std::string& em, const std::string& rec, const std::string& txt);
    Mensaje(const std::string& em, const std::string& rec, const std::string& txt, const std::string& fecha);
    ~Mensaje();

    std::string getEmisor() const;
    void setEmisor(const std::string& em);

    std::string getReceptor() const;
    void setReceptor(const std::string& rec);

    std::string getTextoContenido() const;
    void setTextoContenido(const std::string& txt);

    std::string getFechaEnvio() const;
    void setFechaEnvio(const std::string& fecha);

    bool getLeido() const;
    bool isLeido() const;
    void marcarComoLeido();

    // Sobrecarga de operadores
    bool operator==(const Mensaje& otro) const;
    bool operator<(const Mensaje& otro) const;

    friend std::ostream& operator<<(std::ostream& os, const Mensaje& m);
};

#endif // MENSAJE_H