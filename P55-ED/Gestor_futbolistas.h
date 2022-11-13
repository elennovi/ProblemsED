#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
#include <unordered_map>
#include <vector>
#include <unordered_set>
using namespace std;

using jugador = string;
using equipo = string;

struct tJugador {
	unordered_set<equipo> equiposAntiguos;
	equipo equipoActual;
	list<jugador>::iterator it;
};

class gestor_futbolistas {
public:
	gestor_futbolistas() {}

	// La funci�n que da de alta a los jugadores para los equipos y a los equipos
	// si es que no est�n dados de alta ya. Tambi�n sirve para cambiar el equipo
	// en el que se encuentra un asistente
	void fichar(jugador j, equipo e) {
		auto it0 = equipos.find(e);
		// Si ese equipo no est� registrado
		if (it0 == equipos.end()) 
			// Insertamos el equipo
			equipos.insert({ e, {j} });
		// Si ese equipo s� est� registrado y el jugador no pertenece ya a ese
		// equipo
		else if (jugadores.find(j) == jugadores.end() || jugadores.find(j)->second.equipoActual != e)
			// Ponemos a la cola al nuevo jugador
			it0->second.push_front(j);

		// Ahora debemos comprobar si el jugador ya ten�a equipo asignado
		auto it1 = jugadores.find(j);
		// Calculamos el iterador al que apunta (siempre ser� el primer elemento de la
		// lista doblemente enlazada)
		auto it2 = equipos.find(e)->second.begin();
		// Si el jugador no estaba asignado a ning�n equipo anteriormente
		if (it1 == jugadores.end()) {
			// Simplemente lo a�adimos a los jugadores
			jugadores.insert({ j, {{e}, e, it2} });
		}
		// Si el jugador ya ten�a alg�n equipo asignado y es distitno del que se
		// le pretende asignar
		else if (it1->second.equipoActual != e) {
			// Primero lo eliminamos de la lista de jugadores asociada al anterior
			// equipo
			auto it3 = equipos.find(it1->second.equipoActual);

			// Como el equipo siempre estar� en el mapa de equipos simplemente lo eliminamos
			it3->second.erase(it1->second.it);

			// A�adimos el equipo a los que ha pertenecido el jugador si es que ese no era
			// uno al que ya pertenecia
			if (it1->second.equiposAntiguos.find(e) == it1->second.equiposAntiguos.end())
				it1->second.equiposAntiguos.insert(e);

			// Actualizamos el equipo en el que se encuentra actualmente el jugador
			it1->second.equipoActual = e;

			// Actualizamos el iterador del jugador para que apunte a la lista del 
			// nuevo equipo
			it1->second.it = it2;
		}
	}

	// La funci�n que devuelve el equipo en el que se encuentra actualmente un
	// jugador dado
	equipo equipo_actual(jugador j) {
		auto it0 = jugadores.find(j);
		// Si el jugador no est� registrado lanzamos una excepci�n
		if (it0 == jugadores.end())
			// Lanzamos la excepci�n domain error con el error correspondiente
			throw domain_error("Jugador inexistente");
		// Si el jugador est� registrado
		else {
			// Simplemente devolvemos el equipo en el que est� actualmente
			return it0->second.equipoActual;
		}
		return "";
	}

	// La fuci�n que determina cuantos jugadores tiene asociado un equipo en el
	// momento actual
	int fichados(equipo e) {
		auto it0 = equipos.find(e);
		// Si el equipo no est� en la base de datos
		if (it0 == equipos.end())
			throw domain_error("Equipo inexistente");
		// Si el equipo est� registrado
		else
			return it0->second.size();
		return 0;
	}

	// La funci�n que devuelve el numero n de ultimos fichajes para un determinado
	// equipo
	vector<jugador> utlimos_fichajes(equipo e, int n) {
		auto it0 = equipos.find(e);
		// Si el equipo no est� en la base de datos
		if (it0 == equipos.end())
			throw domain_error("Equipo inexistente");
		// Si el equipo est� registrado
		else {
			// Necesitamos recorrer la lista n veces
			vector<jugador> v;
			// Utilizaremos un iterador que la vaya recorriendo 
			auto r = it0->second.begin();
			for (int i = 0; i < n && r != it0->second.end(); i++) {
				// Lo guardamos en el vector
				v.push_back(*r);
				++r;
			}
			return v;
		}
		return {};
	}

	// La funci�n que calcula a cuantos equipos ha estado apuntado un determinado
	// jugador
	int cuantos_equipos(jugador j) {
		auto it0 = jugadores.find(j);
		// Si el jugador no est� dado de alta
		if (it0 == jugadores.end())
			return 0;
		// Si el jugador est� dado de alta
		else
			// Simplemente se devuelve el n�mero de equipos que hemos ido
			// contabilizando
			return it0->second.equiposAntiguos.size();
	}

private:
	// Necesitaremos representar a los jugadores con un mapa no necesariamente
	// ordenado en el que guardaremos la siguiente informaci�n
	unordered_map<jugador, tJugador> jugadores;
	// Clave: el nombre del jugador
	// Valor: el n�mero de equipos en los que ha estado, el equipo en el que se 
	// encuentra actualmente y un iterador que apunta a su posici�n en la lista
	// de jugadores en la que est� jugando actualmente

	// Necesitamos guardar los equipos 
	unordered_map<equipo, list<jugador>> equipos;
	// Clave: el nombre del equipo
	// Valor: una lista con los jugadores 
};