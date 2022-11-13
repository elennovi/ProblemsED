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

	// La función que añade un nuevo DNI
	void nuevo(dni DNI) {
		unordered_map<dni, tInfoConductor>::iterator it = tablaConductores.find(DNI);
		// Si ya existía
		if (it != tablaConductores.end())
			throw domain_error("Conductor duplicado");
		// Si no existía
		else {
			unordered_map<puntos, list<dni>>::iterator it1 = tablaPuntos.find(15);
			// Si todavía no hay ningún conductor que tenga ese número de puntos
			// asociados
			if (it1 == tablaPuntos.end())
				// Añadimos este nuevo número de puntos
				tablaPuntos.insert({ 15, {DNI} });
			// Si ya existe ese conductor en el mapa
			else
				// Existe un conductor más que tiene dichos puntos
				it1->second.push_front(DNI);

			// Lo guardamos en la tabla de conductores
			tablaConductores.insert({ DNI, {15, tablaPuntos[15].begin()} });
			// Lo tenemos en cuenta en la tabla de los puntos
		}
	}

	// La función que resta puntos a un conductor tras una infracción
	void quitar(dni DNI, puntos ptos) {
		unordered_map<dni, tInfoConductor>::iterator it = tablaConductores.find(DNI);
		// Si no existe el DNI con el que estamos trabajando
		if (it == tablaConductores.end())
			throw domain_error("Conductor inexistente");
		// Si ese DNI existe
		else if (max(it->second.ptos - ptos, 0) != it->second.ptos) {
			// Guardamos los puntos que teníamos
			puntos ptosAntes = it->second.ptos;
			puntos ptosDespues = max(ptosAntes - ptos, 0); // Para que no sea menor de 0
			// Ahora eliminamos a ese conductor de los puntos anteriores
			tablaPuntos[ptosAntes].erase(it->second.it);
			// Si ya no hay ningún conductor con esos puntos lo eliminamos
			if (tablaPuntos[ptosAntes].empty())
				tablaPuntos.erase(ptosAntes);

			// Ahora tenemos un nuevo conductor en los puntos actuales
			unordered_map<puntos, list<dni>>::iterator it1 = tablaPuntos.find(ptosDespues);
			// Si no hay nadie con esos puntos
			if (it1 == tablaPuntos.end())
				// Lo añadimos
				tablaPuntos.insert({ ptosDespues, {DNI} });
			// Si ya hay alguien que tenga ese número de puntos
			else
				// Le sumamos uno
				it1->second.push_front(DNI);

			// Ahora cambiamos el número de puntos que tiene dicha persona
			it->second.ptos = ptosDespues;
			it->second.it = tablaPuntos[ptosDespues].begin();
		}
	}

	// La función que resta puntos a un conductor tras una infracción
	void recuperar(dni DNI, puntos ptos) {
		unordered_map<dni, tInfoConductor>::iterator it = tablaConductores.find(DNI);
		// Si no existe el DNI con el que estamos trabajando
		if (it == tablaConductores.end())
			throw domain_error("Conductor inexistente");
		// Si ese DNI existe
		else if(min(it->second.ptos + ptos, 15) != it->second.ptos){
			// Guardamos los puntos que teníamos
			puntos ptosAntes = it->second.ptos;
			puntos ptosDespues = min(ptosAntes + ptos, 15); // Para que no sea menor de 0
			// Ahora eliminamos a ese conductor de los puntos anteriores
			tablaPuntos[ptosAntes].erase(it->second.it);
			// Si ya no hay ningún conductor con esos puntos lo eliminamos
			if (tablaPuntos[ptosAntes].empty())
				tablaPuntos.erase(ptosAntes);

			// Ahora tenemos un nuevo conductor en los puntos actuales
			unordered_map<puntos, list<dni>>::iterator it1 = tablaPuntos.find(ptosDespues);
			// Si no hay nadie con esos puntos
			if (it1 == tablaPuntos.end())
				// Lo añadimos
				tablaPuntos.insert({ ptosDespues, {DNI} });
			// Si ya hay alguien que tenga ese número de puntos
			else
				// Le sumamos uno
				it1->second.push_front(DNI);

			// Ahora cambiamos el número de puntos que tiene dicha persona
			it->second.ptos = ptosDespues;
			it->second.it = tablaPuntos[ptosDespues].begin();
		}
	}

	// La función consultar que devuelve los puntos actuales
	puntos consultar(dni DNI) {
		unordered_map<dni, tInfoConductor>::iterator it = tablaConductores.find(DNI);
		// Si no existe el conductor
		if (it == tablaConductores.end())
			throw domain_error("Conductor inexistente");
		// Si se puede acceder a los puntos de los conductores
		else
			return it->second.ptos;
	}

	// La función que devuelve los conductores con un determinado número de puntos
	int cuantos_con_puntos(puntos ptos) {
		// Comprobamos que los puntos sean correctos
		// Si no son correctos
		if (ptos < 0 || ptos > 15)
			throw domain_error("Puntos no validos");
		// Si son correctos
		else {
			unordered_map<puntos, list<dni>>::iterator it = tablaPuntos.find(ptos);
			// Si hay algúna persona registrada con esos puntos
			if (it != tablaPuntos.end())
				return it->second.size();
			// Si no hay ninguna persona registrada con esos puntos
			else
				return 0;
		}
	}
	
	// La función que devuelve un listado con tosos los conductores que tienen 
	// un determinado número de puntos
	list<dni> lista_por_puntos(puntos ptos) {
		// Comprobamos que los puntos sean correctos
		// Si no son correctos
		if (ptos < 0 || ptos > 15)
			throw domain_error("Puntos no validos");
		// Si son correctos
		else {
			unordered_map<puntos, list<dni>>::iterator it = tablaPuntos.find(ptos);
			// Si hay algúna persona registrada con esos puntos
			if (it != tablaPuntos.end())
				return tablaPuntos[ptos];
			else 
				return {};
		}
	}

private:
	// La representación de los se puede hacer un mapa que no necesita orden
	unordered_map<dni, tInfoConductor> tablaConductores;

	// La representación de los puntos se podría hacer con un mapa sin orden
	unordered_map<puntos, list<dni>> tablaPuntos;
	// El int representa el número de conductores con "puntos" número de puntos
};
