// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include "queue_eda.h"
using namespace std;

template<class T>
class queueExtendida : public queue<T> {
    using Nodo = typename queue<T>::Nodo;
public:
    void invertirQueue() {
        // Solo lo hacemos para listas que no estén vacías
        if (!this->empty()) {
            Nodo* a = this->prim;
            Nodo* s = a->sig;
            for (int i = 0; i < this->size() - 1; i++) {
                Nodo* ss = s->sig;
                s->sig = a;
                a = s;
                s = ss;
            }
            Nodo* prim = this->prim;
            this->prim = a;
            this->ult = prim;
            this->ult->sig = nullptr;
        }
    }
    void mostrar() {
        Nodo* act = this->prim;
        for (int i = 0; i < this->size(); i++) {
            cout << act->elem << " ";
            act = act->sig;
        }
        cout << endl;
    }
};

bool resuelveCaso() {
    int num;
    cin >> num;
    if (!std::cin)
        return false;
    queueExtendida<int> q;
    while (num != 0) {
        q.push(num);
        cin >> num;
    }
    q.invertirQueue();
    q.mostrar();
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
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