// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include "deque_eda.h"
using namespace std;

template <class T>
class dequeNuevo : public deque<T> {
    using Nodo = typename deque<T> ::Nodo;
public:
    void mergeDeque(dequeNuevo<T>& d2) {
        Nodo* ini1 = this->fantasma->sig;
        Nodo* ini2 = d2.fantasma->sig;
        Nodo* ult = this->fantasma;

        int i = 0, j = 0;
        int k = 0;
        while (i < this->size() && j < d2.size()) {
            if (k % 2 == 0) {
                ult->sig = ini1;
                ini1->ant = ult;
                ini1 = ini1->sig;
                ult = ult->sig;
                i++;
            }
            else {
                ult->sig = ini2;
                ini2->ant = ult;
                ini2 = ini2->sig;
                ult = ult->sig;
                j++;
            }
            k++;
        }
        // Si han quedado elementos sin recorrer en el primer deque
        if (i < this->size()) {
            ult->sig = ini1;
            ini1->ant = ult;
        }
        // Si han quedado elementos sin recorrer en el segundo deque
        if (j < d2.size()){
            ult->sig = ini2;
            ini2->ant = ult;
            this->fantasma->ant = d2.fantasma->ant;
            d2.fantasma->ant->sig = this->fantasma;
        }
        // Ahora tenemos más elementos
        this->nelems += d2.nelems;
        // Dejamos la segunda lista vacia
        d2.nelems = 0;
        d2.fantasma->sig = d2.fantasma;
        d2.fantasma->ant = d2.fantasma;
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
    dequeNuevo<int> d1, d2;
    int n1;
    cin >> n1;
    int elem;
    for (int i = 0; i < n1; i++) {
        cin >> elem;
        d1.push_back(elem);
    }
    int n2;
    cin >> n2;
    for (int i = 0; i < n2; i++) {
        cin >> elem;
        d2.push_back(elem);
    }
    d1.mergeDeque(d2);
    d1.mostrar();
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}