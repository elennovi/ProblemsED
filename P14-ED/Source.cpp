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
    void invertir() {
        Nodo* act = this->fantasma;
        for (int i = 0; i <= this->size(); i++) {
            swap(act->sig, act->ant);
            act = act->ant;
        }
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
    int n;
    cin >> n;
    if (!std::cin)
        return false;
    dequeModificado<int> d;
    while (n != 0){
        d.push_back(n);
        cin >> n;
    }
    d.invertir();
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