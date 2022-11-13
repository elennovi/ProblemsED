// Elena Novillo Luceño
// A51

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
using namespace std;

struct tAccidente {
    string fecha;
    int valor;
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int numLineas;
    cin >> numLineas;
    if (!std::cin)
        return false;
    string fecha;
    int valor;
    stack<tAccidente> s;
    for (int i = 0; i < numLineas; i++) {
        cin >> fecha;
        cin >> valor;
        // Si la pila esta vacía no hay accidentes aereos
        while (!s.empty() && s.top().valor <= valor)
            s.pop();
        if (s.empty())
            cout << "NO HAY" << endl;
        else
            cout << s.top().fecha << endl;
        
        // Guardamos el elemento en la pila
        s.push({ fecha, valor });
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