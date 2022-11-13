// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include "bintree_eda.h" // Para poder extender de la clase
using namespace std;

template <class T>
class nuevoArbol : public bintree<T> {
    using Link = typename bintree<T>::Link;
public:
    nuevoArbol() : bintree<T>() {}
    nuevoArbol(nuevoArbol<T> const& l, T const& e, nuevoArbol<T> const& r) : bintree<T>(l, e, r) {}
    int numHojas() {
        return numHojas(this->raiz);
    }
    int numNodos() {
        return numNodos(this->raiz);
    }
    int altura() {
        return altura(this->raiz);
    }
private:
    int numHojas(Link r) {
        if (r == nullptr) return 0;
        else {
            int hIzquierda = numHojas(r->left);
            int hDerecha = numHojas(r->right);
            return ((r->left == nullptr) && (r->right == nullptr)) +
            hIzquierda + hDerecha;
        }
    }
    int numNodos(Link r) {
        if (r == nullptr) return 0;
        else {
            int nIzquierda = numNodos(r->left);
            int nDerecha = numNodos(r->right);
            return nIzquierda + nDerecha + 1;
        }
    }
    int altura(Link r) {
        if (r == nullptr) return 0;
        else {
            int aIzquierda = altura(r->left);
            int aDerecha = altura(r->right);
            return max(aIzquierda, aDerecha) + 1;
        }
    }
};

template <typename T>
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
    nuevoArbol<char> b = leerNuevoArbol<char>('.');
    cout << b.numNodos() << " " << b.numHojas() << " " << b.altura() << endl;
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