// Elena Novillo Luceño
// A51


#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <unordered_map>
#include <set>
using namespace std;

struct tInfoActor {
    int minutos;
    unordered_map<string, int> minsPorPeli;
    // La clave es el nombre de la pelicula 
    // El valor es el numero de minutos que aparecio en pantalla
    // para dicha pelicula
};

struct tInfoPelicula {
    int emisiones;
    list<string>::iterator it;
};

bool resuelveCaso() {
    // Las estructuras de datos para representar
    unordered_map<string, tInfoActor> tablaActores;
    // Clave: nombre
    // Valor: los minutos en emision de ese actor

    map<int, set<string>, greater<int>> tablaMinutos;
    // Clave: el número de minutos
    // Valor: un conjunto con los actores que han participado esos minutos

    unordered_map<string, vector<string>> tablaPeliculas;
    // Clave: la película
    // Valor: lleva un vector con los actores que participan en esa pelicula

    int numPelis;
    cin >> numPelis;
    if (numPelis == 0)
        return false;
    // Leemos para cada película los actores
    for (int i = 0; i < numPelis; i++) {
        string nombre;
        cin >> nombre;
        int numActores;
        cin >> numActores;
        vector<string> actoresPeli;
        for (int j = 0; j < numActores; j++) {
            string actor;
            cin >> actor;
            int minutos;
            cin >> minutos;
            auto it0 = tablaActores.find(actor);

            // Si es la primera vez que aparece
            if (it0 == tablaActores.end()) 
                tablaActores.insert({ actor, {minutos, {{nombre, minutos}}} });
            // Si ya ha aparecido le sumamos los nuevos
            else {
                // Eliminamos los anteriores miutos del actor
                auto it2 = tablaMinutos.find(it0->second.minutos);
                it2->second.erase(it2->second.find(actor));
                // Si ya ningún actor tiene ese número de minutos
                if (it2->second.empty())
                    tablaMinutos.erase(it2);

                // Le sumamos los nuevos minutos de emision
                it0->second.minutos += minutos;
                // Cada actor solo aparece en una película cada vez
                // por lo que siempre tendremos que insertar una nueva
                // película
                it0->second.minsPorPeli.insert({nombre, minutos});
            }
            auto it1 = tablaMinutos.find(tablaActores[actor].minutos);
            // Si ningún otro actor ha estado en emisión durante dichos
            // minutos
            if (it1 == tablaMinutos.end())
                tablaMinutos.insert({ tablaActores[actor].minutos, {actor} });
            
            // Si ya hay otro actor con esos minutos en emision
            else
                it1->second.insert(actor);
            actoresPeli.push_back(actor);
        }
        // Tenemos que insertar la película en la tabla de peliculas
        tablaPeliculas.insert({ nombre, actoresPeli });
    }

    // Para el listado de películas ordenadas necesitamos
    unordered_map<string, tInfoPelicula> emisionesPorPelicula;
    // La clave es el nombre de la pelicula
    // El valor es un entero indicando el número de emisiones que se han
    // hecho de esa película junto con un iterador que apunta a la lista
    // de peliculas para ese número de emisiones

    map<int, list<string>, greater<int>> peliculasPorNumEmisiones;
    // La clave es el número de emisiones
    // El valor es la lista de peliculas que han sido emitidas ese número
    // de emisiones

    // Ahora necesitamos leer las películas en orden de emisión
    int numEmisiones;
    cin >> numEmisiones;
    for (int i = 0; i < numEmisiones; i++) {
        string pelicula;
        cin >> pelicula;
        int emisionesPeli;

        // Comprobamos si la película ya ha aparecido alguna vez
        auto it0 = emisionesPorPelicula.find(pelicula);
        // Si no se había emitido ninguna vez
        if (it0 == emisionesPorPelicula.end())
            emisionesPeli = 1;
        // Si ya se había emitido alguna vez
        else
            emisionesPeli = it0->second.emisiones + 1;

        // Ahora modificamos la tabla de pelis por número de emisiones
        auto it1 = peliculasPorNumEmisiones.find(emisionesPeli);
        // Si no hay ninguna película con ese número de emisiones
        if (it1 == peliculasPorNumEmisiones.end())
            peliculasPorNumEmisiones.insert({ emisionesPeli, {pelicula} });
        // Si ya hay alguna película que se haya emitido ese número de veces
        else
            it1->second.push_front(pelicula); // Ponemos en la lista a la nueva película
        
        // Ahora ya podemos añadir la pelicula a la tabla de las emisiones por pelicula
        // Si no se ha emitido antes
        if (it0 == emisionesPorPelicula.end())
            emisionesPorPelicula.insert({ pelicula, {emisionesPeli, peliculasPorNumEmisiones[emisionesPeli].begin()} });
        // Si ya se ha emitido antes
        else {
            // Hay que eliminar a esa persona del anterior número de emisiones que había hecho
            auto it2 = peliculasPorNumEmisiones.find(emisionesPeli - 1);
            it2->second.erase(it0->second.it);
            // Si ahora ya ninguna película se ha emitido ese número de veces se elimina
            if (it2->second.empty())
                peliculasPorNumEmisiones.erase(it2);

            // Hay que añadir esa pelicula con el número de emisiones que le corresponde
            it0->second.emisiones = emisionesPeli;
            it0->second.it = peliculasPorNumEmisiones[emisionesPeli].begin();
        }
    }

    // Una vez tenemos insertadas las películas debemos actualizar el número de minutos que estuvieron
    // en pantalla cada uno de los actores de cada película (ya que hay películas que se han emitido
    // mas de una vez)
    for (auto p : tablaPeliculas) {
        auto it = emisionesPorPelicula.find(p.first);
        // Si se ha emitido
        if (it != emisionesPorPelicula.end()) {
            int emisionesPeli = it->second.emisiones;
            // Solo modificaremos los minutos de los actores que hayan aparecido en una película
            // que se ha emitido más de una vez
            if (emisionesPeli > 1) {
                // Recorremos todos los actores de esas películas
                for (auto a : p.second) {
                    auto it0 = tablaActores.find(a);
                    // Eliminamos al actor del anterior número de minutos
                    auto it1 = tablaMinutos.find(it0->second.minutos);
                    auto it2 = it1->second.find(a);
                    it1->second.erase(it2);
                    // Si no hay otros actores con esos minutos en pantalla eliminamos dichos minutos
                    if (it1->second.empty())
                        tablaMinutos.erase(it1);

                    // Modificamos los minutos de ese actor en la tabla de actores
                    it0->second.minutos += it0->second.minsPorPeli[p.first] * (emisionesPeli - 1);
                    it0->second.minsPorPeli[p.first] *= emisionesPeli;

                    // Movemos al actor al nuevo número de minutos
                    auto it3 = tablaMinutos.find(it0->second.minutos);
                    // Si no hay ningun actor más con el nuevo número de minutos
                    if (it3 == tablaMinutos.end())
                        tablaMinutos.insert({ it0->second.minutos, {a} });
                    // Si ya hay algún actor con ese mismo número de minutos
                    else
                        it3->second.insert(a);
                }
            }
        }
        // Si no se ha emitido
        else {
            for (auto a : p.second) {
                // Calculamos el número de minutos que aparecio
                auto it0 = tablaActores.find(a);

                // Eliminamos al actor del anterior número de minutos
                auto it1 = tablaMinutos.find(it0->second.minutos);
                auto it2 = it1->second.find(a);
                it1->second.erase(it2);
                // Si no hay otros actores con esos minutos en pantalla eliminamos dichos minutos
                if (it1->second.empty())
                    tablaMinutos.erase(it1);

                // Modificamos los minutos del actor en la tabla de actores
                it0->second.minutos -= it0->second.minsPorPeli[p.first];
                it0->second.minsPorPeli[p.first] = 0;

                // Añadimios al actor al nuevo número de minutos
                auto it3 = tablaMinutos.find(it0->second.minutos);
                // Si no hay ningun actor más con el nuevo número de minutos
                if (it3 == tablaMinutos.end())
                    tablaMinutos.insert({ it0->second.minutos, {a} });
                // Si ya hay algún actor con ese mismo número de minutos
                else
                    it3->second.insert(a);
            }
        }
    }

    // Finalmente solo tenemos que mostrar los datos que nos piden
    
    // Para las películas
    auto itPeli = peliculasPorNumEmisiones.begin();
    cout << itPeli->first << " " << *itPeli->second.begin() << endl;

    // Para los actores
    auto itActor = tablaMinutos.begin();
    cout << itActor->first;
    for (auto a : itActor->second)
        cout << " " << a;
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
