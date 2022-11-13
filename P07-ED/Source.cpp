// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
using namespace std;

struct tAccidente {
    string fecha;
    int num;
};

bool resuelveCaso() {
    int N;
    cin >> N;
    if (!cin) return false;
    string fecha, sol;
    int num;
    stack<tAccidente> pila; 
    for (int i = 0; i < N; i++){
        cin >> fecha >> num;
        sol = "NO HAY";
        while (!pila.empty() && pila.top().num <= num ) {
            pila.pop(); // Hacemos pop del elemento
        }
        if (!pila.empty()) sol = pila.top().fecha; // Si después de buscar
        // el elemento hemos vaciado la pila es porque no existe
        pila.push({fecha, num}); // Siempre apilamos los elementos
        cout << sol << endl;
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