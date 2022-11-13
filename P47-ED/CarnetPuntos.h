#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <unordered_map>
using namespace std;

using dni = string;
using puntos = int;

struct tInfoConductor {
	puntos ptos;
	list<dni>::iterator it;
};

class carnet_puntos {
public:
	carnet_puntos() {}

	// La funci�n que a�ade un nuevo DNI
	void nuevo(dni DNI) {
		unordered_map<dni, tInfoConductor>::iterator it = tablaConductores.find(DNI);
		// Si ya exist�a
		if (it != tablaConductores.end())
			throw domain_error("Conductor duplicado");
		// Si no exist�a
		else {
			unordered_map<puntos, list<dni>>::iterator it1 = tablaPuntos.find(15);
			// Si todav�a no hay ning�n conductor que tenga ese n�mero de puntos
			// asociados
			if (it1 == tablaPuntos.end())
				// A�adimos este nuevo n�mero de puntos
				tablaPuntos.insert({ 15, {DNI} });
			// Si ya existe ese conductor en el mapa
			else
				// Existe un conductor m�s que tiene dichos puntos
				it1->second.push_front(DNI);

			// Lo guardamos en la tabla de conductores
			tablaConductores.insert({ DNI, {15, tablaPuntos[15].begin()} });
			// Lo tenemos en cuenta en la tabla de los puntos
		}
	}

	// La funci�n que resta puntos a un conductor tras una infracci�n
	void quitar(dni DNI, puntos ptos) {
		unordered_map<dni, tInfoConductor>::iterator it = tablaConductores.find(DNI);
		// Si no existe el DNI con el que estamos trabajando
		if (it == tablaConductores.end())
			throw domain_error("Conductor inexistente");
		// Si ese DNI existe
		else if (max(it->second.ptos - ptos, 0) != it->second.ptos) {
			// Guardamos los puntos que ten�amos
			puntos ptosAntes = it->second.ptos;
			puntos ptosDespues = max(ptosAntes - ptos, 0); // Para que no sea menor de 0
			// Ahora eliminamos a ese conductor de los puntos anteriores
			tablaPuntos[ptosAntes].erase(it->second.it);
			// Si ya no hay ning�n conductor con esos puntos lo eliminamos
			if (tablaPuntos[ptosAntes].empty())
				tablaPuntos.erase(ptosAntes);

			// Ahora tenemos un nuevo conductor en los puntos actuales
			unordered_map<puntos, list<dni>>::iterator it1 = tablaPuntos.find(ptosDespues);
			// Si no hay nadie con esos puntos
			if (it1 == tablaPuntos.end())
				// Lo a�adimos
				tablaPuntos.insert({ ptosDespues, {DNI} });
			// Si ya hay alguien que tenga ese n�mero de puntos
			else
				// Le sumamos uno
				it1->second.push_front(DNI);

			// Ahora cambiamos el n�mero de puntos que tiene dicha persona
			it->second.ptos = ptosDespues;
			it->second.it = tablaPuntos[ptosDespues].begin();
		}
	}

	// La funci�n que resta puntos a un conductor tras una infracci�n
	void recuperar(dni DNI, puntos ptos) {
		unordered_map<dni, tInfoConductor>::iterator it = tablaConductores.find(DNI);
		// Si no existe el DNI con el que estamos trabajando
		if (it == tablaConductores.end())
			throw domain_error("Conductor inexistente");
		// Si ese DNI existe
		else if(min(it->second.ptos + ptos, 15) != it->second.ptos){
			// Guardamos los puntos que ten�amos
			puntos ptosAntes = it->second.ptos;
			puntos ptosDespues = min(ptosAntes + ptos, 15); // Para que no sea menor de 0
			// Ahora eliminamos a ese conductor de los puntos anteriores
			tablaPuntos[ptosAntes].erase(it->second.it);
			// Si ya no hay ning�n conductor con esos puntos lo eliminamos
			if (tablaPuntos[ptosAntes].empty())
				tablaPuntos.erase(ptosAntes);

			// Ahora tenemos un nuevo conductor en los puntos actuales
			unordered_map<puntos, list<dni>>::iterator it1 = tablaPuntos.find(ptosDespues);
			// Si no hay nadie con esos puntos
			if (it1 == tablaPuntos.end())
				// Lo a�adimos
				tablaPuntos.insert({ ptosDespues, {DNI} });
			// Si ya hay alguien que tenga ese n�mero de puntos
			else
				// Le sumamos uno
				it1->second.push_front(DNI);

			// Ahora cambiamos el n�mero de puntos que tiene dicha persona
			it->second.ptos = ptosDespues;
			it->second.it = tablaPuntos[ptosDespues].begin();
		}
	}

	// La funci�n consultar que devuelve los puntos actuales
	puntos consultar(dni DNI) {
		unordered_map<dni, tInfoConductor>::iterator it = tablaConductores.find(DNI);
		// Si no existe el conductor
		if (it == tablaConductores.end())
			throw domain_error("Conductor inexistente");
		// Si se puede acceder a los puntos de los conductores
		else
			return it->second.ptos;
	}

	// La funci�n que devuelve los conductores con un determinado n�mero de puntos
	int cuantos_con_puntos(puntos ptos) {
		// Comprobamos que los puntos sean correctos
		// Si no son correctos
		if (ptos < 0 || ptos > 15)
			throw domain_error("Puntos no validos");
		// Si son correctos
		else {
			unordered_map<puntos, list<dni>>::iterator it = tablaPuntos.find(ptos);
			// Si hay alg�na persona registrada con esos puntos
			if (it != tablaPuntos.end())
				return it->second.size();
			// Si no hay ninguna persona registrada con esos puntos
			else
				return 0;
		}
	}
	
	// La funci�n que devuelve un listado con tosos los conductores que tienen 
	// un determinado n�mero de puntos
	list<dni> lista_por_puntos(puntos ptos) {
		// Comprobamos que los puntos sean correctos
		// Si no son correctos
		if (ptos < 0 || ptos > 15)
			throw domain_error("Puntos no validos");
		// Si son correctos
		else {
			unordered_map<puntos, list<dni>>::iterator it = tablaPuntos.find(ptos);
			// Si hay alg�na persona registrada con esos puntos
			if (it != tablaPuntos.end())
				return tablaPuntos[ptos];
			else 
				return {};
		}
	}

private:
	// La representaci�n de los se puede hacer un mapa que no necesita orden
	unordered_map<dni, tInfoConductor> tablaConductores;

	// La representaci�n de los puntos se podr�a hacer con un mapa sin orden
	unordered_map<puntos, list<dni>> tablaPuntos;
	// El int representa el n�mero de conductores con "puntos" n�mero de puntos
};
