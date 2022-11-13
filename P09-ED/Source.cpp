// Elena Novillo Luceño
// A51

#include <iostream>
#include <fstream>

#include "queue_eda.h"
using namespace std;

template <class T>
class ListaDuplicada: public queue<T> {
    using Nodo = typename queue<T>::Nodo;
public:
    void duplica() {
        Nodo* act = this->prim;
        for (int i = 0; i < this->size(); i++) {
            Nodo* duplicado = new Nodo(act->elem); 
            duplicado->sig = act->sig;
            act->sig = duplicado;
            act = duplicado->sig;
        }
        this->nelems *= 2;
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
    ListaDuplicada<int> lista;
    while (e != 0) {
        lista.push(e); // guardamos el elemento en la lista
        cin >> e; 
    }
    lista.duplica(); // Duplicamos la lista una vez hemos leido todos
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
