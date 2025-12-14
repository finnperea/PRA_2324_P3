#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include <stdexcept> // Para std::runtime_error
#include "BSNode.h"

template <typename T>
class BSTree {
    private:
        // --- ATRIBUTOS PRIVADOS ---
        int nelem;           // Número de elementos
        BSNode<T> *root;     // Nodo raíz

        // --- MÉTODOS PRIVADOS RECURSIVOS ---

        // 1. Búsqueda Recursiva
        BSNode<T>* search(BSNode<T>* n, T e) const {
            if (n == nullptr) {
                throw std::runtime_error("Elemento no encontrado.");
            }
            if (n->elem < e) {
                return search(n->right, e);
            } else if (n->elem > e) {
                return search(n->left, e);
            } else {
                return n; // Elemento encontrado
            }
        }

        // 2. Inserción Recursiva
        BSNode<T>* insert(BSNode<T>* n, T e) {
            if (n == nullptr) {
                return new BSNode<T>(e);
            } else if (n->elem == e) {
                throw std::runtime_error("Elemento duplicado.");
            } else if (n->elem < e) {
                n->right = insert(n->right, e);
            } else {
                n->left = insert(n->left, e);
            }
            return n;
        }

        // 3. Recorrido Inorden (Imprimir)
        void print_inorder(std::ostream &out, BSNode<T>* n) const {
            if (n != nullptr) {
                // I - R - D (Izquierda, Raíz, Derecha)
                print_inorder(out, n->left);
                out << n->elem << " "; // Imprimimos el elemento y un espacio
                print_inorder(out, n->right);
            }
        }

        // 4. Eliminación Recursiva
        BSNode<T>* remove(BSNode<T>* n, T e) {
            if (n == nullptr) {
                throw std::runtime_error("Elemento no encontrado.");
            } else if (n->elem < e) {
                n->right = remove(n->right, e);
            } else if (n->elem > e) {
                n->left = remove(n->left, e);
            } else {
                // Elemento encontrado. Procedemos a eliminar.
                
                // Caso A: Tiene 2 hijos
                if (n->left != nullptr && n->right != nullptr) {
                    // Reemplazamos por el MAX del subárbol izquierdo
                    n->elem = max(n->left);
                    n->left = remove_max(n->left);
                } 
                // Caso B: Tiene 1 o 0 hijos
                else {
                    BSNode<T>* temp = n; // Guardamos puntero para borrar memoria
                    n = (n->left != nullptr) ? n->left : n->right;
                    delete temp; // Liberación de memoria crítica en C++
                }
            }
            return n;
        }

        // 5. Auxiliar: Buscar el Máximo
        T max(BSNode<T>* n) const {
            if (n == nullptr) {
                throw std::runtime_error("Árbol vacío");
            }
            if (n->right != nullptr) {
                return max(n->right); // Seguimos bajando por la derecha
            } else {
                return n->elem; // No hay más derecha, este es el mayor
            }
        }

        // 6. Auxiliar: Eliminar el Máximo
        BSNode<T>* remove_max(BSNode<T>* n) {
            if (n->right == nullptr) {
                // Encontramos el máximo, nos quedamos con su hijo izquierdo (si tiene)
                BSNode<T>* leftChild = n->left;
                delete n; // Importante: liberar memoria
                return leftChild;
            } else {
                n->right = remove_max(n->right);
                return n;
            }
        }

        // 7. Liberación de memoria (Destructor)
        // Recorrido Post-Orden: Izq -> Der -> Raíz (borrar hijos antes que padres)
        void delete_cascade(BSNode<T>* n) {
            if (n != nullptr) {
                delete_cascade(n->left);
                delete_cascade(n->right);
                delete n;
            }
        }

    public:
        // --- MÉTODOS PÚBLICOS (Lanzaderas) ---

        // Constructor: Crea un árbol vacío
        BSTree() : nelem(0), root(nullptr) {}

        // Tamaño
        int size() const {
            return nelem;
        }

        // Búsqueda
        T search(T e) const {
            BSNode<T>* res = search(root, e);
            return res->elem;
        }

        // Operador []
        T operator[](T e) const {
            return search(e);
        }

        // Inserción
        void insert(T e) {
            root = insert(root, e);
            nelem++;
        }

        // Eliminación
        void remove(T e) {
            root = remove(root, e);
            nelem--;
        }

        // Destructor
        ~BSTree() {
            delete_cascade(root);
        }

        // Operador de impresión
        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst) {
            bst.print_inorder(out, bst.root);
            return out;
        }
};

#endif