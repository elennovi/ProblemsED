// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "bintree_eda.h"
using namespace std;

template <class T>
class nuevoArbol: public bintree<T> {
    using Link = typename bintree<T>::Link;
public:
    nuevoArbol() : bintree<T>() {}
    nuevoArbol(nuevoArbol<T> const& l, T const& e, nuevoArbol<T> const& r) : bintree<T>(l, e, r) {}
    void calculaFrontera(vector<T>& v) {
        calculaFrontera(this->raiz, v); // Llamamos a la función privada que implementa la
        // solución almacenándolo en v
    }
private:
    void calculaFrontera(Link r, vector<T>& v) {
        if (r != nullptr) { // Solo continuamos si no es un arbol vacio
            calculaFrontera(r->left, v); // Primero de la izquierda porque los queremos en ese orden
            calculaFrontera(r->right, v); 
            if (r->left == nullptr && r->right == nullptr)
                v.push_back(r->elem); // Si es hoja entonces la metemos
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
    nuevoArbol<int> b = leerNuevoArbol(-1); // Leemos el arbol y lo escribimos en la nueva clase que
    // hereda de bintree
    vector<int> v; // El vector en el que vamos a almacenar la frontera
    b.calculaFrontera(v);
    for (int e : v) cout << e << " ";
    cout << endl;
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