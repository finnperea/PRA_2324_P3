#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

// IMPORTANTE: Ajusta esta ruta a donde tengas tu práctica 1.
// Si copiaste el archivo a la carpeta actual, usa: #include "ListLinked.h"
#include "/mnt/d/PRA Practicas/pract1/PRA_2324_P1/ListLinked.h" 

template <typename V>
class HashTable : public Dict<V> {

    private:
        // Atributos privados
        int n;   // Número de elementos almacenados
        int max; // Capacidad de la tabla (número de cubetas)
        
        // Array de punteros a ListLinked. 
        // Cada posición del array es una lista enlazada de TableEntries.
        ListLinked<TableEntry<V>>* table;

        // Función Hash (Privada)
        // Calcula el índice de la cubeta para una clave dada.
        int h(std::string key) {
            int sum = 0;
            // Suma los valores ASCII de cada carácter de la clave
            for (char c : key) {
                sum += (int)c;
            }
            // Devuelve el resto de la división para asegurar que el índice está dentro del array
            return sum % max;
        }

    public:
        // --- CONSTRUCTOR ---
        HashTable(int size) : max(size), n(0) {
            // Reservamos memoria para el array de listas
            // Esto llama al constructor por defecto de ListLinked para cada posición
            table = new ListLinked<TableEntry<V>>[size];
        }

        // --- DESTRUCTOR ---
        ~HashTable() {
            // Liberamos la memoria del array.
            // El destructor de ListLinked se encargará de liberar los nodos internos.
            delete[] table;
        }

        // --- MÉTODOS PROPIOS ---
        
        // Devuelve la capacidad total de cubetas
        int capacity() {
            return max;
        }

        // Sobrecarga de operador friend << para imprimir la tabla
        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
            out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]\n";
            out << "==============\n";
            for (int i = 0; i < th.max; i++) {
                out << "== [" << i << "] ==> " << th.table[i] << "\n";
            }
            out << "==============";
            return out;
        }

        // Sobrecarga del operador [] para acceso directo
        // Permite hacer: int x = miTabla["clave"];
        V operator[](std::string key) {
            return search(key); // Reutilizamos el método search
        }

        // --- MÉTODOS HEREDADOS DE DICT<V> ---

        // 1. INSERTAR
        void insert(std::string key, V value) override {
            // Primero comprobamos si ya existe la clave
            // Usamos search y capturamos la excepción para saber si existe o no
            // (Esta es una forma, otra es usar el método search de ListLinked si devuelve -1)
            
            int cubeta = h(key);
            TableEntry<V> entry(key, value); // Creamos la entrada completa
            
            // Nota: ListLinked suele tener un método search que busca por valor.
            // Gracias a que sobrecargamos operator== en TableEntry, buscará solo por clave.
            if (table[cubeta].search(entry) != -1) {
                // Si search devuelve algo distinto a -1, es que ya existe
                throw std::runtime_error("La clave ya existe en el diccionario.");
            }

            // Si no existe, insertamos (prepend es más eficiente O(1))
            table[cubeta].prepend(entry);
            n++;
        }

        // 2. BUSCAR
        V search(std::string key) override {
            int cubeta = h(key);
            
            // Creamos una entrada "dummy" solo con la clave para buscar
            TableEntry<V> busqueda(key); 
            
            // Buscamos el índice dentro de la lista enlazada
            int index = table[cubeta].search(busqueda);
            
            if (index != -1) {
                // Si existe, recuperamos el elemento completo usando get() de la lista
                return table[cubeta].get(index).value;
            } else {
                throw std::runtime_error("Clave no encontrada.");
            }
        }

        // 3. ELIMINAR
        V remove(std::string key) override {
            int cubeta = h(key);
            TableEntry<V> busqueda(key);
            
            int index = table[cubeta].search(busqueda);
            
            if (index != -1) {
                // Primero guardamos el valor para devolverlo
                V valor = table[cubeta].get(index).value;
                // Eliminamos de la lista (usando remove de ListLinked)
                table[cubeta].remove(index);
                n--;
                return valor;
            } else {
                throw std::runtime_error("Clave no encontrada, no se puede eliminar.");
            }
        }

        // 4. ELEMENTOS TOTALES
        int entries() override {
            return n;
        }
};

#endif