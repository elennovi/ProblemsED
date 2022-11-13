// Elena Novillo Luceño
// A51

#include "Persona.h"

template <class T, class Predicate>
void remove_if(list<T>& lista, Predicate pred) {
    auto it = lista.begin();
    while (it != lista.end()) {
        auto aux = ++it;
        if (!pred((*(--it)).getEdad()))
            lista.erase(it);
        it = aux;
    }
}

class filtro_edad {
public:
    filtro_edad(int min, int max): minEdad(min), maxEdad(max){}
    bool operator()(int edad) {
        return edad >= minEdad && edad <= maxEdad;
    }
private:
    int minEdad, maxEdad;
};

void mostrar(list<Persona> const&  l) {
    for (Persona e : l) cout << e.getNombre() << endl;
}

bool resuelveCaso() {
    int numElem, max, min;
    cin >> numElem >> min >> max;
    if (numElem == 0 && max == 0 && min == 0)
        return false;
    list<Persona> l;
    int edad;
    string nombre;
    char aux;
    for (int i = 0; i < numElem; i++) {
        cin >> edad;
        cin.get(aux);
        getline(cin, nombre);
        l.push_back(Persona(nombre, edad)); // Añadimos un nuevo elemento
    }
    remove_if(l, filtro_edad(min, max)); // Eliminamos los elementos que 
    // no pasan el filtro de edad
    mostrar(l); // Mostramos la lista
    cout << "---" << endl;
    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso());

#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
