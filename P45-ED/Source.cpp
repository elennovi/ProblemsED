// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdio.h>
#include <unordered_map>
#include <map>
#include <set>
using namespace std;

// Devuelve un bool indicando si la palabra que se ha pasado por argumentos
// está en mayuculas o no
bool esMayuscula(string s){
    for (int i = 0; i < s.length(); i++) {
        // En cuanto encuentre una letra en minuscula devuelve false
        if (islower(s.at(i)))
            return false;
    }
    // Si no se ha encontrado ningún valor en minúsculas
    return true;
}

bool resuelveCaso() {
    string palabra;
    cin >> palabra;
    if (!std::cin)
        return false;
    // Necesitamos un mapa no ordenado con el nombre de cada deporte
    unordered_map<string, int> tablaDeportes;
    // La clave: el nombre del equipo
    // El valor: un iterador a un set que contendrá la lista de deportes con un 
    // determinado número de elementos
    
    // Necesitamos un mapa no ordenado con el nombre de las personas y el
    // deporte que practican
    unordered_map<string, string> tablaPersonas;
    // La clave: el nombre de la persona
    // El valor: el nombre del deporte al que está apuntada

    // Necesitamos un mapa ordenado por el número de elementos de los distintos
    // deportes y con un conjunto en el que se guardan todos los deportes con ese 
    // número de elementos
    map<int, set<string>, greater<int>> tablaNumPersonasDeporte;
    // La clave: el número de personas que tienen apuntadas estos deportes
    // El valor: el conjunto de deportes ordenados alfabeticamente 

    while (palabra != "_FIN_") {
       // Insertamos el deporte con el numero 0 de personas
       map<int, set<string>>::iterator n =  tablaNumPersonasDeporte.find(0);
       if (n == tablaNumPersonasDeporte.end())
           tablaNumPersonasDeporte.insert({ 0, { palabra } });
       else
           n->second.insert(palabra);
       // Insertamos el deporte en la tabla de deportes
       tablaDeportes.insert({ palabra, 0 });
       string deporteActual = palabra;

       cin >> palabra;
       while (!esMayuscula(palabra)) {
           unordered_map<string, string>::iterator it = tablaPersonas.find(palabra);
           // Si no encontramos a la persona en la tabla de personas podemos añadirla
           // a ese deporte y a la tabla de personas
           if (it == tablaPersonas.end()) {
               int numPersonas = tablaDeportes.find(deporteActual)->second;
               map<int, set<string>>::iterator conjuntoPersonas = tablaNumPersonasDeporte.find(numPersonas);
               conjuntoPersonas->second.erase(conjuntoPersonas->second.find(deporteActual));
               // Si era la única persona con ese número de personas apuntadas
               // lo eliminamos
               if (conjuntoPersonas->second.empty())
                   tablaNumPersonasDeporte.erase(conjuntoPersonas);
               map<int, set<string>>::iterator nuevoNumPersonas = tablaNumPersonasDeporte.find(numPersonas + 1);
               // Si no lo hemos encontrado en la tabla lo añadimos
               if (nuevoNumPersonas == tablaNumPersonasDeporte.end()) 
                   tablaNumPersonasDeporte.insert({ numPersonas + 1, {deporteActual} });
               // Si ya hay algun deporte con ese número de personas apuntadas
               else
                   nuevoNumPersonas->second.insert(deporteActual);
               // Modificamos la tabla de deportes para que el número de participantes
               // se mantenga actualizado
               tablaDeportes.find(deporteActual)->second = numPersonas + 1;
               // A continuación añadimos la persona a la lista de personas
               tablaPersonas.insert({ palabra, deporteActual });
           }
           // Si ya se encuentra en la lista de personas la borramos del deporte en el que
           // aparece
           else if (it->second != deporteActual) {
               // Buscamos el deporte en la tabla de deportes
               unordered_map<string, int>::iterator deporteAnteriorPersona = tablaDeportes.find(it->second);
               // Si ese deporte existe en la tabla de deportes es porque es la 
               // primera vez que se repite esa persona en el tablón por lo que
               // habrá que restarle uno al número de personas asociadas a ese deporte
               if (deporteAnteriorPersona != tablaDeportes.end()) {
                   // Ahora añadimos el nuevo deporte al número de personas nuevo (anterior - 1)
                   if (tablaNumPersonasDeporte.find(deporteAnteriorPersona->second - 1) == tablaNumPersonasDeporte.end())
                       tablaNumPersonasDeporte.insert({ deporteAnteriorPersona->second - 1, {deporteAnteriorPersona->first} });
                   else
                       tablaNumPersonasDeporte.find(deporteAnteriorPersona->second - 1)->second.insert(deporteAnteriorPersona->first);
                   // Borramos el deporte del conjunto de deportes con el anterior número
                   // de personas apuntadas
                   map<int, set<string>>::iterator numPersonasDeporteAnterior = tablaNumPersonasDeporte.find(deporteAnteriorPersona->second);
                   numPersonasDeporteAnterior->second.erase(it->second);
                   // Si no hay ningún deporte mas asociado a ese número de personas lo borramos
                   if (numPersonasDeporteAnterior->second.empty())
                       tablaNumPersonasDeporte.erase(deporteAnteriorPersona->second);
                   // Restamos uno al deporte en el que estaba anteriormente esa persona
                   deporteAnteriorPersona->second--;
                   // Sustituimos el valor asociado por un campo vacío
                   it->second = "";
               }
           }
           cin >> palabra;
       }
    }

    for (auto e1 : tablaNumPersonasDeporte)
        for (auto e2 : e1.second)
            cout << e2 << " " << e1.first << endl;
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