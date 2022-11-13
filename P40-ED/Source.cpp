// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include "set_eda.h"
using namespace std;

template <class T, class Comparator = std::less<T>>
class setExtended : public set<T> {
    using Link = typename set<T>::Link;
public:
    setExtended(): set<T>() {}
    pair <T, bool> lower_bound(T const& elem) {
        return lower_bound(this->raiz, elem);
    }
private:
    pair <T, bool> lower_bound(Link r, T elem) {
        if (r == nullptr) return {elem, false};
        else {
            if (r->elem > elem) { // Podría encontrarse a la derecha o a la izquierda
                pair<T, bool> izquierda = lower_bound(r->iz, elem); // Recorremos la derecha 
                if (!izquierda.second) // Si no se ha encontrado en la derecha recorremos
                    return { r->elem, true };
                else return izquierda;
            }
            else if (r->elem == elem) // La raiz es el número que estamos buscando
                return { elem, true };
            else // Debería encontrarse a la derecha
                return lower_bound(r->dr, elem);
        }
    }
};

bool resuelveCaso() {
    int N, M;
    setExtended<int> s;
    int elem;
    // Leemos los elementos del conjunto
    cin >> N;
    if (N == 0) return false;
    for (int i = 0; i < N; i++) {
        cin >> elem;
        s.insert(elem);
    }
    // Leemos las preguntas que se van a hacer
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> elem;
        pair<int, bool> sol = s.lower_bound(elem);
        if (!sol.second)
            cout << "NO HAY";
        else
            cout << sol.first;
        cout << endl;
    }
    cout << "---" << endl;
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 

    while (resuelveCaso());


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}