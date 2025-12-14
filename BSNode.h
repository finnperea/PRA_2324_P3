#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T>
class BSNode {
    public:
        // --- ATRIBUTOS PÚBLICOS ---
        T elem;               // El dato almacenado
        BSNode<T>* left;      // Puntero al subárbol izquierdo (menores)
        BSNode<T>* right;     // Puntero al subárbol derecho (mayores)

        // --- CONSTRUCTOR ---
        // Los parámetros left y right tienen valores por defecto a nullptr.
        // Esto permite crear un nodo hoja simplemente llamando a: BSNode(dato)
        BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr)
            : elem(elem), left(left), right(right) {}

        // --- IMPRESIÓN ---
        // Imprime solo el elemento. Asumimos que el tipo T tiene sobrecargado su propio operator<<
        friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn) {
            out << bsn.elem;
            return out;
        }
};

#endif