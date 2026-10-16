#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include <stdexcept>

template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* siguiente;

    Nodo(const T& d) : dato(d), siguiente(nullptr) {}
};

template <typename T>
class Lista {
private:
    Nodo<T>* cabeza;
    int tamano;

public:
    Lista() : cabeza(nullptr), tamano(0) {}

    // Constructor de copia
    Lista(const Lista<T>& otra) : cabeza(nullptr), tamano(0) {
        Nodo<T>* actual = otra.cabeza;
        while (actual != nullptr) {
            this->agregarFinal(actual->dato);
            actual = actual->siguiente;
        }
    }

    // Destructor
    ~Lista() {
        limpiar();
    }

    // Operador de asignacion
    Lista<T>& operator=(const Lista<T>& otra) {
        if (this != &otra) {
            limpiar();
            Nodo<T>* actual = otra.cabeza;
            while (actual != nullptr) {
                this->agregarFinal(actual->dato);
                actual = actual->siguiente;
            }
        }
        return *this;
    }

    void agregarFinal(const T& elemento) {
        Nodo<T>* nuevo = new Nodo<T>(elemento);
        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            Nodo<T>* aux = cabeza;
            while (aux->siguiente != nullptr) {
                aux = aux->siguiente;
            }
            aux->siguiente = nuevo;
        }
        tamano++;
    }

    int obtenerTamano() const {
        return tamano;
    }

    T& operator[](int index) {
        if (index < 0 || index >= tamano) {
            static T vacio;
            return vacio;
        }
        Nodo<T>* aux = cabeza;
        for (int i = 0; i < index; ++i) {
            aux = aux->siguiente;
        }
        return aux->dato;
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= tamano) {
            static T vacio;
            return vacio;
        }
        Nodo<T>* aux = cabeza;
        for (int i = 0; i < index; ++i) {
            aux = aux->siguiente;
        }
        return aux->dato;
    }

    void limpiar() {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            Nodo<T>* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
        cabeza = nullptr;
        tamano = 0;
    }
};

#endif // LISTA_H