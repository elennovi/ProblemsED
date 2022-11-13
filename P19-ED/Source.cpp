// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include <deque>
using namespace std;

using pii = pair<int, int>;

bool resuelveCaso() {
    int nelems, intervalo;
    cin >> nelems >> intervalo;
    if (nelems == 0 && intervalo == 0)
        return false;
    deque<pii> q; // Creamos el deque
    int elem;
    cin >> elem;
    q.push_back({ elem, 0 }); // El primer elemento siempre se guarda
    for (int i = 1; i < intervalo; i++) {
        cin >> elem;
        while (!q.empty() && q.back().first < elem) q.pop_back();
        q.push_back({ elem, i }); // Metemos el nuevo elemento
    }
    cout << q.front().first;
    for (int i = intervalo; i < nelems; i++) {
        cin >> elem; 
        if (q.front().second <= i - intervalo)
            q.pop_front(); // El último elemento ya no pertenece al intervalo
        while (!q.empty() && q.back().first < elem) q.pop_back();
        q.push_back({ elem, i }); // Metemos el nuevo elemento
        cout << " " << q.front().first;
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
