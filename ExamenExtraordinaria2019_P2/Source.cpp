// Elena Novillo Luceño
// A51

#include "Tienda.h"
using namespace std;

bool resuelveCaso() {
    string operacion;
    cin >> operacion;
    if (!std::cin)
        return false;

    Tienda t;
    while (operacion != "FIN") {
        if (operacion == "vender") {
            cod codigo;
            cliente cli;
            cin >> codigo >> cli;
            pair<bool, fecha> p = t.vender(codigo, cli);
            // Si se ha podido vender al cliente
            if (p.first)
                cout << "VENDIDO " << p.second << endl;
            // Si no se ha podido vender al cliente
            else
                cout << "EN ESPERA" << endl;
        }
        else if (operacion == "adquirir") {
            cod codigo;
            fecha f;
            cantidad cant;
            cin >> codigo >> f >> cant;
            vector<cliente> v = t.adquirir(codigo, f, cant);
            cout << "PRODUCTO ADQUIRIDO";
            // Recorremos el vector mostrando a los clientes que ahora han podido
            // adquirir el producto
            for (auto cliente : v)
                cout << " " << cliente;
            cout << endl;
        }
        else if (operacion == "cuantos") {
            cod codigo;
            cin >> codigo;
            cantidad cuantos = t.cuantos(codigo);
            cout << cuantos << endl;
        }
        else if (operacion == "hay_esperando") {
            cod codigo;
            cin >> codigo;
            bool hay = t.hay_esperando(codigo);
            if (hay)
                cout << "SI" << endl;
            else
                cout << "NO" << endl;
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