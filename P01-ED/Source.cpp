// Elena Novillo Luceño
// A51

#include <iomanip>
#include <fstream>
#include "Horas.h"

Hora proximaHora(vector <Hora> const& hs, bool& encontrado, Hora const& hora) {
    auto pos = lower_bound(hs.begin(), hs.end(), hora);
    if (pos != hs.end()) {
        encontrado = true;
        return *pos;
    }
    else return hora;
}

bool resuelveCaso() {
    int tamHorario, numHoras;
    cin >> tamHorario >> numHoras;
    if (tamHorario == 0 && numHoras == 0)
        return false;
    vector <Hora> horarioTrenes(tamHorario);
    vector <Hora> horas(numHoras);
    for (Hora& h : horarioTrenes) { // Leemos los horarios de los trenes
        cin >> h;
    }
    for (Hora& h : horas) {
        try {
            cin >> h;
            bool encontrado = false;
            Hora prox = proximaHora(horarioTrenes, encontrado, h);
            if (encontrado) cout << prox << endl;
            else cout << "NO" << endl;
        }
        catch (invalid_argument& ia){
            cout << ia.what() << endl;
        }
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
