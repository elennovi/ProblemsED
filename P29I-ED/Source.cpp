// Elena Novillo Luceño
// A51

#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h"
using namespace std;

struct tSol {
    int diametro, altura;
};

template <class T>
class nuevoArbol : public bintree<T> {
    using Link = typename bintree<T>::Link;
public:
    nuevoArbol() : bintree<T>() {}
    nuevoArbol(nuevoArbol<T> const& l, T const& e, nuevoArbol<T> const& r) : bintree<T>(l, e, r) {}
    int calculaDiametro(){
        return calculaDiametro(this->raiz).diametro;
    }
private:
    tSol calculaDiametro(Link r) {
        if (r == nullptr) return { 0, 0 };
        else {
            tSol actual;
            tSol izq = calculaDiametro(r->left);
            tSol der = calculaDiametro(r->right);
            actual.diametro = izq.altura + der.altura + 1;
            if (izq.diametro > actual.diametro)
                actual.diametro = izq.diametro;
            if (der.diametro > actual.diametro)
                actual.diametro = der.diametro;
            actual.altura = max(izq.altura, der.altura) + 1;
            return actual;
        }
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

void resuelveCaso() {
    char aux;
    cin.get(aux);
    nuevoArbol<char> b = leerNuevoArbol('.');
    cout << b.calculaDiametro() << endl;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

#ifndef DOMJUDGE 
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}