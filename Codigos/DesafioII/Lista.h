#ifndef LISTA_H
#define LISTA_H

#include <stdexcept>

template <typename T>
class Lista
{
private:
    class Nodo
    {
    public:
        T dato;
        Nodo* siguiente;

        Nodo(const T& elemento)
        {
            dato = elemento;
            siguiente = nullptr;
        }
    };

    Nodo* cabeza;
    int tamano;

    void copiar(const Lista<T>& otra)
    {
        Nodo* actual = otra.cabeza;

        while (actual != nullptr)
        {
            agregarFinal(actual->dato);
            actual = actual->siguiente;
        }
    }

public:
    Lista()
    {
        cabeza = nullptr;
        tamano = 0;
    }

    Lista(const Lista<T>& otra)
    {
        cabeza = nullptr;
        tamano = 0;
        copiar(otra);
    }

    ~Lista()
    {
        Nodo* actual = cabeza;

        while (actual != nullptr)
        {
            Nodo* temporal = actual;
            actual = actual->siguiente;
            delete temporal;
        }

        cabeza = nullptr;
        tamano = 0;
    }

    Lista<T>& operator=(const Lista<T>& otra)
    {
        if (this != &otra)
        {
            Nodo* actual = cabeza;

            while (actual != nullptr)
            {
                Nodo* temporal = actual;
                actual = actual->siguiente;
                delete temporal;
            }

            cabeza = nullptr;
            tamano = 0;
            copiar(otra);
        }

        return *this;
    }

    void agregarFinal(const T& elemento)
    {
        Nodo* nuevo = new Nodo(elemento);

        if (cabeza == nullptr)
        {
            cabeza = nuevo;
        }
        else
        {
            Nodo* actual = cabeza;

            while (actual->siguiente != nullptr)
            {
                actual = actual->siguiente;
            }

            actual->siguiente = nuevo;
        }

        tamano++;
    }

    T& obtenerElemento(int indice)
    {
        if (indice < 0 || indice >= tamano)
        {
            throw std::out_of_range("Indice fuera de rango");
        }

        Nodo* actual = cabeza;

        for (int i = 0; i < indice; i++)
        {
            actual = actual->siguiente;
        }

        return actual->dato;
    }

    const T& obtenerElemento(int indice) const
    {
        if (indice < 0 || indice >= tamano)
        {
            throw std::out_of_range("Indice fuera de rango");
        }

        Nodo* actual = cabeza;

        for (int i = 0; i < indice; i++)
        {
            actual = actual->siguiente;
        }

        return actual->dato;
    }

    int obtenerTamano() const
    {
        return tamano;
    }

    T& operator[](int indice)
    {
        return obtenerElemento(indice);
    }

    const T& operator[](int indice) const
    {
        return obtenerElemento(indice);
    }

    bool estaVacia() const
    {
        return cabeza == nullptr;
    }

    void eliminarElemento(int indice)
    {
        if (indice < 0 || indice >= tamano)
        {
            throw std::out_of_range("Indice fuera de rango");
        }

        Nodo* eliminar = nullptr;

        if (indice == 0)
        {
            eliminar = cabeza;
            cabeza = cabeza->siguiente;
        }
        else
        {
            Nodo* anterior = cabeza;

            for (int i = 0; i < indice - 1; i++)
            {
                anterior = anterior->siguiente;
            }

            eliminar = anterior->siguiente;
            anterior->siguiente = eliminar->siguiente;
        }

        delete eliminar;
        tamano--;
    }
};

#endif