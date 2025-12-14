#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>
#include <iostream> // Necesario para std::cout en el operador << (aunque ostream es suficiente para la firma)

template <typename V> 
class TableEntry {
    public:
        // --- ATRIBUTOS PÚBLICOS ---
        std::string key;
        V value;

        // --- MÉTODOS CONSTRUCTORES ---

        // 1. Constructor con clave y valor
        TableEntry(std::string key, V value) : key(key), value(value) {}

        // 2. Constructor solo con clave
        // Útil para buscar: creamos un TableEntry temporal solo con la clave para comparar.
        TableEntry(std::string key) : key(key), value(V{}) {} // Inicializamos V con su valor por defecto {}

        // 3. Constructor por defecto
        TableEntry() : key("") {} // Clave vacía, el valor se inicializa por defecto

        // --- OPERADORES FRIEND (Sobrecarga Global) ---
        // La implementación debe ir dentro del .h para templates, 
        // y como son 'friend', tienen acceso a los atributos privados (si los hubiera).

        // Operador de Igualdad (==)
        // Dos entradas son iguales si sus claves son IGUALES.
        friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2) {
            return te1.key == te2.key;
        }

        // Operador de Desigualdad (!=)
        // Dos entradas son diferentes si sus claves son DISTINTAS.
        friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2) {
            return te1.key != te2.key;
        }

        // Operador de Inserción (<<) para imprimir
        // Esto permite imprimir la entrada directamente usando std::cout << entry.
        friend std::ostream& operator<<(std::ostream &out, const TableEntry<V> &te) {
            out << "{" << te.key << " : " << te.value << "}";
            return out;
        }

        // Operador Menor Que (<)
        // Necesario para que el ABB pueda ordenar.
        friend bool operator<(const TableEntry<V> &te1, const TableEntry<V> &te2) {
            return te1.key < te2.key;
        }

        // Operador Mayor Que (>)
        // Necesario para que el ABB pueda ordenar.
        friend bool operator>(const TableEntry<V> &te1, const TableEntry<V> &te2) {
            return te1.key > te2.key;
        }
};

#endif
