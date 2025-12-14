#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <string>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {

    private:
        // El árbol binario que guardará los datos.
        // Fíjate que el tipo T del árbol es TableEntry<V>.
        BSTree<TableEntry<V>>* tree;

    public:
        // --- CONSTRUCTOR ---
        BSTreeDict() {
            // Creamos el árbol dinámicamente
            tree = new BSTree<TableEntry<V>>();
        }

        // --- DESTRUCTOR ---
        ~BSTreeDict() {
            // Borramos el árbol. 
            // El destructor de BSTree se encargará de borrar todos los nodos internos.
            delete tree;
        }

        // --- MÉTODOS DE LA INTERFAZ DICT ---

        // 1. Insertar
        void insert(std::string key, V value) override {
            // Empaquetamos clave y valor en una TableEntry
            TableEntry<V> entry(key, value);
            
            // Delegamos en el árbol
            // Si ya existe, el árbol lanzará la excepción std::runtime_error automáticamente
            tree->insert(entry);
        }

        // 2. Buscar
        V search(std::string key) override {
            // Creamos una entrada "dummy" solo con la clave para buscar
            // (Usamos el constructor de TableEntry que solo acepta clave)
            TableEntry<V> searchEntry(key);
            
            // El árbol nos devuelve el TableEntry completo encontrado
            TableEntry<V> result = tree->search(searchEntry);
            
            // Devolvemos solo el valor (.value)
            return result.value;
        }

        // 3. Eliminar
        V remove(std::string key) override {
            // Primero creamos la entrada para buscar
            TableEntry<V> searchEntry(key);
            
            // EL TRUCO: Como BSTree::remove no devuelve el valor, 
            // primero tenemos que buscarlo para poder devolverlo después.
            // Si no existe, 'search' lanzará la excepción y nos ahorramos el resto.
            V val = tree->search(searchEntry).value;
            
            // Si llegamos aquí, es que existe. Lo borramos.
            tree->remove(searchEntry);
            
            return val;
        }

        // 4. Contar elementos
        int entries() override {
            return tree->size();
        }

        // --- MÉTODOS PROPIOS ---

        // Operador [] (Acceso directo)
        V operator[](std::string key) {
            return search(key);
        }

        // Operador << (Impresión)
        // Imprime el contenido del árbol
        friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs) {
            // Desreferenciamos el puntero (*bs.tree) para pasar el objeto árbol al operador << de BSTree
            out << *(bs.tree);
            return out;
        }
};

#endif