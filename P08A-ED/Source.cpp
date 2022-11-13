// Elena Novillo Luceño
// A51

#include <iostream>
#include <fstream>

#include "queue_eda.h"

class propSerPar {
public:
    bool operator() (int n) {
        return n % 2 == 0;
    }
};

template <class T>
class ListaAmpliada : public queue<T> {
    using Nodo = typename queue<T>::Nodo;
public:
    template <class comp>
    int contarElementos(comp propiedad) const {
        int cuenta = 0;
        Nodo* act; // Va a apuntar al elemento de la lista que estemos recorriendo
        act = this->prim;
        for (int i = 0; i < this->size(); i++) {
            if (propiedad(act->elem))
                ++cuenta; // si cumple la propiedad lo contamos
            act = act->sig;
        }
        return cuenta;
    }
};

bool resuelveCaso() {
    int numElem;
    std::cin >> numElem;
    if (numElem == 0) return false;

    ListaAmpliada<int> lista;
    for (size_t i = 0; i < numElem; ++i) {
        int n;
        std::cin >> n;
        lista.push(n);
    }
    int cont = lista.contarElementos(propSerPar());

    std::cout << cont << '\n';

    return true;
}


int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif

    while (resuelveCaso()) {} //Resolvemos todos los casos

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
