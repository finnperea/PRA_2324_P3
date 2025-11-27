#ifndef DICT_H
#define DICT_H

#include <string>

template <typename V> 
class Dict {
    public:
        // Destructor virtual: Esencial para una clase base abstracta.
        // Garantiza que se llame al destructor de la clase hija al eliminar un puntero Dict*.
        virtual ~Dict() {}

        // 1. Inserta el par key->value.
        // Lanza excepción si la clave ya existe.
        virtual void insert(std::string key, V value) = 0;

        // 2. Busca y devuelve el valor asociado a key.
        // Lanza excepción si no se encuentra.
        virtual V search(std::string key) = 0;

        // 3. Elimina el par key->value y devuelve el valor que tenía.
        // Lanza excepción si no se encuentra.
        virtual V remove(std::string key) = 0;

        // 4. Devuelve el número de elementos en el diccionario.
        virtual int entries() = 0;
};

#endif