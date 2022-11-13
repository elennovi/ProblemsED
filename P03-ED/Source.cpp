// Elena Novillo Luceño
// A51

#include <fstream>
#include "Complejo.h"

using p = pair <Complejo, bool>;

p resolver(Complejo const& c, int n) {
    if (n == 0) return { Complejo(0, 0), true };
    else {
        p sol = resolver(c, n - 1);
        sol.first = sol.first * sol.first + c;
        if (sol.second) return { sol.first, abs(sol.first.mod()) <= 2 };
        else return { sol.first, sol.second };
    }
}

void resuelveCaso() {
    Complejo c;
    int n;
    cin >> c >> n;
    p sol = resolver(c, n);
    if (sol.second) cout << "SI" << endl;
    else cout << "NO" << endl;
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

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}