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
    void mergeQueue(queueNuevo<T>& q2) {
        if (!this->empty() && !q2.empty()) {
            Nodo* n1 = this->prim; // Recorre la primera lista
            Nodo* n2 = q2.prim; // Recorre la segunda 
            Nodo* ultElem = this->ult; // Representa el último elemento que forma parte de las lista final
            // Los elementos empiezan a colocarse después del último elemento de la primera lista
            // así tenemos localizado el principio de la nueva lista

            // Ahora recorremos las dos queues añadiendo los elementos de forma ordenada
            int i = 0, j = 0;
            while (i < this->size() && j < q2.size()) {
                if (n1->elem <= n2->elem) { // Si el n1 es menor o igual lo colocamos en la lista
                    ultElem->sig = n1;
                    ultElem = n1;
                    n1 = n1->sig;
                    i++;
                }
                else { // Si el n2 es menor lo colocamos en la lista
                    ultElem->sig = n2;
                    ultElem = n2;
                    n2 = n2->sig;
                    j++;
                }
            }
            this->prim = this->ult->sig; // El primer elemento lo hemos colocado después del
            // último de la primera lista.

            // Si han quedado elementos por añadir de la primera lista
            if (i < this->size()) ultElem->sig = n1, ultElem = this->ult;
            // Si han quedado elementos por añadir de la segunda lista
            if (j < q2.size()) ultElem->sig = n2, ultElem = q2.ult;

            this->ult = ultElem; // El último es el último elemento colocado
            this->ult->sig = nullptr; // El último siempre debe apuntar a null
            this->nelems += q2.size(); // Ahora el tamaño de la lista es del doble
        }
        else if (this->empty()) { // Si solo tiene elementos la segunda
            this->prim = q2.prim;
            this->ult = q2.ult;
            this->nelems = q2.nelems;
        }
        // Si ninguna de las dos tiene elementos o solo tiene la primera
        // la lista se quedará tal como estaba

        q2.prim = nullptr; // Dejamos la segunda lista vacía
        q2.ult = nullptr;
        q2.nelems = 0; // No hay elementos en la segunda lista
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


void resuelveCaso() {
    int e;
    queueNuevo<int> q1; // La primera cola
    queueNuevo<int> q2; // La segunda cola
    cin >> e;
    while (e != 0) {
        q1.push(e);
        cin >> e;
    }
    cin >> e;
    while (e != 0) {
        q2.push(e);
        cin >> e;
    }
    q1.mergeQueue(q2);
    q1.mostrar();
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

    int num;
    cin >> num;
    for (int i = 0; i < num; i++) resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}