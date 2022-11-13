// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>

#include "queue_eda.h"
using namespace std;

template <class T>
class queueNuevo : public queue<T> {
    using Nodo = typename queue<T> ::Nodo;
public:
    void invertirSegmento(int posIni, int tamInv) {
        // Primero buscamos el elemento que se encuentra en la posición en la que se comienza a invertir
        Nodo* anterior = nullptr;
        Nodo* primero = this->prim; 
        for (int i = 1; i < posIni; i++)
            anterior = primero, primero = primero->sig;
        if (tamInv > 1) { 
            Nodo* ant = primero; 
            Nodo* act = primero->sig; // Empezamos recorriendo desde el siguiente nodo que queremos invertir
            Nodo* sigui = nullptr;
            for (int i = 0; i < tamInv - 1; i++) {
                sigui = act->sig; 
                act->sig = ant;
                ant = act;
                act = sigui;
            } 
            if (this->prim == primero && this->ult != ant) {
                this->prim = ant;
                primero->sig = act;
            }
            else if(this->prim != primero && this->ult == ant) {
                primero->sig = nullptr;
                anterior->sig = ant;
                this->ult = primero;
            }
            else if (this->prim == primero && this->ult == ant) {
                this->prim->sig = nullptr;
                swap(this->prim, this->ult);
            }
            else {
                anterior->sig = ant;
                primero->sig = act;
            }
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
    int nelems, posIni, tam;
    cin >> nelems >> posIni >> tam;
    if (!std::cin)
        return false;
    int e;
    queueNuevo<int> q;
    for (int i = 0; i < nelems; i++) {
        cin >> e;
        q.push(e);
    }
    q.invertirSegmento(posIni, tam);
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