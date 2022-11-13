// Elena Novillo Luceño
// A51


#include "Gestor_futbolistas.h"


bool resuelveCaso() {
    string operacion;
    cin >> operacion;
    if (!std::cin)
        return false;
    gestor_futbolistas g;
    while (operacion != "FIN") {
        if (operacion == "fichar") {
            jugador j;
            equipo e;
            cin >> j >> e;
            g.fichar(j, e);
        }
        else if (operacion == "ultimos_fichajes") {
            equipo e;
            int n;
            cin >> e >> n;
            try {
                vector<jugador> v = g.utlimos_fichajes(e, n);
                cout << "Ultimos fichajes de " << e << ":";
                for (auto j : v)
                    cout << " " << j;
                cout << endl;
            }
            catch (exception& ex) {
                cout << "ERROR: " << ex.what() << endl;
            }
        }
        else if (operacion == "fichados") {
            equipo e;
            cin >> e;
            try {
                int num = g.fichados(e);
                cout << "Jugadores fichados por " << e << ": " << num << endl;
            }
            catch (exception& ex) {
                cout << "ERROR: " << ex.what() << endl;
            }
        }
        else if (operacion == "cuantos_equipos") {
            jugador j;
            cin >> j;
            try {
                int num = g.cuantos_equipos(j);
                cout << "Equipos que han fichado a " << j << ": " << num << endl;
            }
            catch (exception& ex) {
                cout << "ERROR: " << ex.what() << endl;
            }
        }
        else if (operacion == "equipo_actual") {
            jugador j;
            cin >> j;
            try {
                equipo e = g.equipo_actual(j);
                cout << "El equipo de " << j << " es " << e << endl;
            }
            catch (exception& ex) {
                cout << "ERROR: " << ex.what() << endl;
            }
        }
        cin >> operacion;
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


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}