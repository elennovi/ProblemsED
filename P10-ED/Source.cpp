// Elena Novillo Luceño
// A51

#include <iostream>
#include <fstream>

#include "queue_eda.h"
using namespace std;

template <class T>
class listaInvertida : public queue<T> {
    using Nodo = typename queue<T>::Nodo;
public:
    void invierte() {
        if (!this->empty()) {
            Nodo* act = this->prim->sig;
            Nodo* ant = this->prim;
            Nodo* sig;
            for (int i = 0; i < this->size() - 1; i++) {
                sig = act->sig;
                act->sig = ant;
                ant = act;
                act = sig;
            }
            this->prim->sig = nullptr;
            swap(this->ult, this->prim);
        }
    }
    void muestraLista() const {
        Nodo* act = this->prim;
        for (int i = 0; i < this->size(); i++) {
            cout << act->elem << " ";
            act = act->sig;
        }
        cout << endl;
    }
};

bool resuelveCaso() {
    int e;
    cin >> e;
    if (!cin) return false;
    listaInvertida<int> lista;
    while (e != 0) {
        lista.push(e); // guardamos el elemento en la lista
        cin >> e;
    }
    lista.invierte(); // Invertimos la lista una vez hemos leido todos
    // los elementos
    lista.muestraLista(); // Mostramos la lista
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
