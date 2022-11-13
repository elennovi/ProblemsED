#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <list>
#include <map>
#include <unordered_map>
#include <vector>
#include <stdexcept>
using namespace std;

using persona = string;
using empleo = string;

class OficinaEmpleo {
public:
	OficinaEmpleo() : trabajos(unordered_map<empleo, list<persona>>()), personas(unordered_map<persona, map<empleo, list<persona>::iterator>>()) {}

	// La función altaOficina tiene coste constante O(1) pues todas las operaciones que se realizan en ella tienen coste
	// constante o constante amortizado.
	void altaOficina(persona p, empleo e) {
		// Comprobamos si el trabajo existe o es nuevo
		auto i = trabajos.find(e);
		if (i == trabajos.end()) { // Si el trabajo no existe
			// Insertamos en la lista de trabajos la cola con la persona
			trabajos.insert({ e, {p} });
		}
		else if(personas.find(p) == personas.end() || personas.find(p)->second.find(e) == personas.find(p)->second.end())// si el trabajo existe y no
			i->second.push_back(p); // ponemos a la cola a la persona

		// Comrpobamos si la persona está en la oficina
		auto f = personas.find(p);
		auto t = --((trabajos.find(e))->second.end());
		if (f == personas.end()) { // Si la persona no está en la oficina de empleo
			// Insertamos la persona con el empleo nuevo
			personas.insert({ p, {{e, t }} });
		}
		else { // Si la persona está apuntada en la oficina de empleo
			// Comprobamos si está apuntada al empleo dado
			auto f2 = f->second.find(e);
			if (f2 == f->second.end()) { // Si no está apuntada a ese empleo
				// Añadimos el empleo al conjunto de empleos de esa persona
				f->second.insert({e, t });
			}
		}
		
	}

	// La función ofertaEmpleo tiene coste lineal O(n) donde n es el número de trabajos a los
	// que está apuntado dicha persona. Eliminar a la persona de la lista de personas es
	// constante mientras que eliminar a esa persona de todos los trabajos de la lista de 
	// trabajos es más costoso.
	persona ofertaEmpleo(empleo const& e) {
		try {
			// Buscamos la primera persona apuntada en dicho trabajo
			persona p = trabajos.at(e).front();
			// Borramos a la persona de todos los empleos para los que estaba formada
			auto s = personas.at(p);
			auto j = s.begin();
			while (j != s.end()) {
				// Borramos a la persona de la lista de personas de cada trabajo que tenga asociado
				trabajos.at(j->first).erase(j->second);
				// Si esa era la única persona apuntada a ese trabajo debemos eliminar ese trabajo
				if (trabajos.at(j->first).empty())
					trabajos.erase(j->first);
				++j;
			}
			// Buscamos la persona dentro de las personas y la eliminamos
			personas.erase(p);
			return p;
		}
		catch (exception & ex) {
			throw domain_error("No existen personas apuntadas a este empleo");
		}
		return "";
	}

	// La función listadoEmpleos tiene coste lineal O(n) donde n es el número de trabajos con los que cuenta
	// esa persona ya que hay que recorrer el mapa de empleos de dicha persona.
	vector<empleo> listadoEmpleos(persona const& p) const { 
		vector<empleo> v;
		try {
			// Recorremos los empleos de la persona dada
			for (auto e : personas.at(p))
				v.push_back(e.first); // Guardamos el empleo en el vector
		}
		catch (exception & e) { // Si la persona no existe
			throw domain_error("Persona inexistente");
		}
		return v;
	}

private:
	unordered_map<empleo, list<persona>> trabajos;
	unordered_map<persona, map<empleo, list<persona>::iterator>> personas;
};

