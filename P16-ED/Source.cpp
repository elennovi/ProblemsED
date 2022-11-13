// Elena Novillo Luceño
// A51

#include <iostream>
#include <iomanip>
#include <fstream>

#include "deque_eda.h"
using namespace std;

template <class T>
class dequeModificado : public deque<T> {
    using Nodo = typename deque<T> ::Nodo;
public:
    void mergeDeque(dequeModificado& d2) {
        int i = 0, j = 0; // Los índices que indican por qué parte
        // de cada lista vamos
        Nodo* n1 = this->fantasma->sig; // El primer elemento de la primera
        // lista
        Nodo* n2 = d2.fantasma->sig; // El primer elemento de la segunda
        // lista
        Nodo* ultElemento = this->fantasma; // El último nodo añadido a la
        // lista final

        // Ahora recorremos las dos listas
        while (i < this->size() && j < d2.size()) {
            if (n1->elem <= n2->elem) {
                ultElemento->sig = n1;
                n1->ant = ultElemento;
                ultElemento = ultElemento->sig;
                n1 = n1->sig;
                i++;
            }
            else {
                ultElemento->sig = n2;
                n2->ant = ultElemento;
                ultElemento = ultElemento->sig;
                n2 = n2->sig;
                j++;
            }
        }
        // Por si han quedado elementos sin recorrer de la primera lista
        if (i < this->size()) { 
            ultElemento->sig = n1;
            ultElemento = this->fantasma->ant;
        }
        // Por si han quedado elementos sin recorrer de la segunda lista
        if (j < d2.size()) {
            ultElemento->sig = n2;
            ultElemento = d2.fantasma->ant;
        }
        // Dejamos el nodo fantasma para que el anterior sea el último
        // elemento colocado 
        ultElemento->sig = this->fantasma;
        this->fantasma->ant = ultElemento;
        this->nelems += d2.nelems;
        // Dejamos la segunda lista sin elementos
        d2.fantasma->sig = d2.fantasma;
        d2.fantasma->ant = d2.fantasma;
        d2.nelems = 0;
        
    }
    void mostrar() {
        Nodo* act = this->fantasma->sig;
        for (int i = 0; i < this->size(); i++) {
            cout << act->elem << " ";
            act = act->sig;
        }
        cout << endl;
    }
};

void resuelveCaso() {
    dequeModificado<int> d1; // La primera lista enlazada
    dequeModificado<int> d2; // La segunda lista enlazada
    int e;
    cin >> e;
    while (e != 0) {
        d1.push_back(e);
        cin >> e;
    }
    cin >> e;
    while (e != 0) {
        d2.push_back(e);
        cin >> e;
    }
    d1.mergeDeque(d2);
    d1.mostrar();
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; i++) 
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}