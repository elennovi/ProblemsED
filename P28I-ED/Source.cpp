// Elena Novillo Luceño
// A51

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "bintree_eda.h"
using namespace std;

template <class T>
class nuevoArbol : public bintree<T> {
    using Link = typename bintree<T>::Link;
public:
    nuevoArbol() : bintree<T>() {}
    nuevoArbol(nuevoArbol<T> const& l, T const& e, nuevoArbol<T> const& r) : bintree<T>(l, e, r) {}
    T minimo() {
        return minimo(this->raiz);
    }
private:
    T minimo(Link r) {
        T min = r->elem;
        if (r->left != nullptr) {
            T minIzquierda = minimo(r->left);
            if (minIzquierda < min)
                min = minIzquierda;
        }
        if (r->right != nullptr) {
            T minDerecha = minimo(r->right);
            if (minDerecha < min)
                min = minDerecha;
        }
        return min;
    }
};

template <class T>
inline nuevoArbol<T> leerNuevoArbol(T vacio) {
    T raiz;
    std::cin >> raiz;
    if (raiz == vacio) { // es un árbol vacío
        return {};
    }
    else { // leer recursivamente los hijos
        auto iz = leerNuevoArbol(vacio);
        auto dr = leerNuevoArbol(vacio);
        return { iz, raiz, dr };
    }
}

bool resuelveCaso() {
    string aux;
    cin >> aux; // Leemos el tipo de dato del arbol que vamos a leer
    if (!std::cin)
        return false;
    if (aux == "N") {
        nuevoArbol<int> b = leerNuevoArbol(-1); // Leemos el arbol de números
        int min = b.minimo();
        cout << min;
    }
    else {
        string vacio = "#";
        nuevoArbol<string> b = leerNuevoArbol(vacio); // Leemos los datos del arbol de strings
        string min = b.minimo();
        cout << min;
    }
    cout << endl;
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