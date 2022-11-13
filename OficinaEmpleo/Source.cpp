// Elena Novillo Luceño
// A51
// https://youtu.be/cgFV9orx5wU

#include "OficinaEmpleo.h"

bool resuelveCaso() {
    OficinaEmpleo ofi = OficinaEmpleo();
    string operacion;
    cin >> operacion;
    if (!cin)
        return false;
    while (operacion != "FIN") {
        if (operacion == "altaOficina") {
            string persona, empleo;
            cin >> persona >> empleo;
            ofi.altaOficina(persona, empleo);
        }
        else if (operacion == "ofertaEmpleo") {
            string empleo;
            cin >> empleo;
            try {
                string persona = ofi.ofertaEmpleo(empleo);
                cout << empleo << ": " << persona << endl;
            }
            catch (domain_error& ex) {
                cout << "ERROR: " << ex.what() << endl;
            }
        }
        else if (operacion == "listadoEmpleos") {
            string persona;
            cin >> persona;
            try {
                vector<string> v = ofi.listadoEmpleos(persona);
                cout << persona << ":";
                for (string e : v)
                    cout << " " << e;
                cout << endl;
            }
            catch (domain_error& ex){
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
