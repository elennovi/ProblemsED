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
    void invertirSegmento(int pos, int tam) {
        // Primero buscamos el primer elemento a invertir
        Nodo* act = this->fantasma;
        for (int i = 0; i < pos; i++)
            act = act->sig;
        Nodo* ant = act->ant; 
        for (int i = 0; i < tam; i++) {
            swap(act->sig, act->ant);
            act = act->ant;
        }
        swap(act->ant, ant->sig);
        act->ant->sig = act;
        ant->sig->ant = ant;
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

bool resuelveCaso() {
    int nelems, posIni, tam;
    cin >> nelems;
    if (!std::cin)
        return false;
    cin >> posIni >> tam;
    dequeModificado<int> d;
    int e;
    for (int i = 0; i < nelems; i++) {
        cin >> e;
        d.push_back(e);
    }
    d.invertirSegmento(posIni, tam);
    d.mostrar();
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}