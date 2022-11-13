#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

using profe = string;
using alumno = string;
using puntos = int;

using infoAlumno = pair<profe, puntos>;

class autoescuela {
public:
	autoescuela() {}

	// La función que da de alta cada alumno con un profesor o para cambiarle el 
	// profesor asignado si no estba apuntado con ese profesor
	void alta(alumno a, profe p) {
		unordered_map<alumno, infoAlumno>::iterator it = tablaAlumnos.find(a);
		// Si el alumno es nuevo 
		if (it == tablaAlumnos.end()) {
			// Insertamos al alumno con ese profesor en los alumnos
			tablaAlumnos.insert({ a, {p, 0} });

			// Insertamos a ese alumno en la tabla de los profesores
			insertaAlumnoEnProfes(a, p, 0);
		}
		// Si el alumno ya tenía otro profesor asignado
		else {
			profe profeAntiguo = it->second.first;
			// Solo lo modificamos si el profe es distinto
			if (profeAntiguo != p) {
				// Cambiamos el profesor del alumno en la tabla de alumnos
				it->second.first = p;

				// Añadimos al alumno en la tabla de los profesores para el nuevo 
				// profesor
				insertaAlumnoEnProfes(a, p, it->second.second);

				// Eliminamos al alumno del conjunto de alumnos que tenia el anterior
				// profesor
				eliminaAlumnoEnProfes(a, profeAntiguo);
			}
		}
	}

	// La función que comprueba si un alumno tiene asignado un determinado profesor
	bool es_alumno(alumno a, profe p) {
		unordered_map<alumno, infoAlumno>::iterator it = tablaAlumnos.find(a);
		// Si el alumno no está matriculado en la autoescuela
		if (it == tablaAlumnos.end())
			return false;
		// Si el alumno sí está matriculado
		else
			return it->second.first == p;
	}

	// La función que devuelve la puntuación de un alumno dado
	puntos puntuacion(alumno a) {
		unordered_map<alumno, infoAlumno>::iterator it = tablaAlumnos.find(a);
		// Si el alumno no está matriculado en la autoescuela
		if (it == tablaAlumnos.end())
			throw domain_error("El alumno " + a + " no esta matriculado");
		// Si el alumno sí está matriculado
		else
			return it->second.second;
	}

	// La función que aumenta en una cantidad de puntos dada los puntos de un alumno
	// dado
	void actualizar(alumno a, int n) {
		unordered_map<alumno, infoAlumno>::iterator it = tablaAlumnos.find(a);
		// Si el alumno no está matriculado en la autoescuela
		if (it == tablaAlumnos.end())
			throw domain_error("El alumno " + a + " no esta matriculado");
		// Si el alumno sí está matriculado
		else {
			it->second.second += n;
			// Actualizamos la puntuacion de la tabla de profesores para ese
			// alumno
			unordered_map<profe, map<alumno, puntos>>::iterator it1 = tablaProfes.find(it->second.first);
			if (it1 != tablaProfes.end()) {
				map<alumno, puntos>::iterator it2 = it1->second.find(a);
				if (it2 != it1->second.end())
					it2->second += n;
			}
		}
	}

	// La función que devuelve un vector con los alumnos de un profesor que tienen una puntuación
	// mayor de una dada 
	vector<alumno> examen(profe p, puntos n) {
		vector<alumno> v;
		unordered_map<profe, map<alumno, puntos>>::iterator it = tablaProfes.find(p);
		// Si el profe no tiene alumnos devolvemos el vector vacio
		if (it != tablaProfes.end())
			for (auto a : it->second)
				if (a.second >= n)
					v.push_back(a.first);
		return v;
	}

	// La función que elimina a un alumno 
	void aprobar(alumno a) {
		// Eliminamos al alumno de la tabla de alumnos
		unordered_map<alumno, infoAlumno>::iterator it = tablaAlumnos.find(a);
		// Si no estña en la autoescuela apuntado
		if (it == tablaAlumnos.end())
			throw domain_error("El alumno " + a + " no esta matriculado");
		// Si estaba en la autoescuela
		else {
			// Lo eliminamos del conjunto de alumnos asociado a su profe
			eliminaAlumnoEnProfes(a, it->second.first);
			// Lo eliminamos de la tabla de alumnos
			tablaAlumnos.erase(it);
		}
	}

private:

	// Necesitamos una tabla (no necesariamente ordenada) que guarde la informacion
	// de cada alumno: nombre del alumno, puntuacion del alumno y el profesor asociado
	unordered_map<alumno, infoAlumno> tablaAlumnos;

	// Necesitamos una tabla con todos los profesores que guarde la información que 
	// de los alumnos que tienen a ese profesor (ordenados alfabeticamente)
	unordered_map<profe, map<alumno, puntos>> tablaProfes;

	// Funciones privadas para evitar la repeticion de codigo:
	void insertaAlumnoEnProfes(alumno a, profe p, puntos n) {
		// Comprobamos si ese profesor no estaba ya en la tabla de profesores
		unordered_map<profe, map<alumno, puntos>>::iterator it1 = tablaProfes.find(p);
		// Si el profesor no tenía alumnos todavía
		if (it1 == tablaProfes.end())
			tablaProfes.insert({ p, {{a, n}} });
		// Si el profesor ya ha tenido algún alumno asignado
		else
			it1->second.insert({ a , n});
	}

	void eliminaAlumnoEnProfes(alumno a, profe p) {
		// Buscamos el profesor en la tabla de profesores
		unordered_map<profe, map<alumno, puntos>>::iterator it = tablaProfes.find(p);
		// Buscamos en el conjunto de alumnos que tiene el profesor al alumno 
		// que queremos borrar
		if (it != tablaProfes.end()) {
			map<alumno, puntos>::iterator it1 = it->second.find(a);
			if (it1 != it->second.end()) {
				// Lo eliminamos del conjunto de alumno
				it->second.erase(it1);

				if (it->second.empty())
					tablaProfes.erase(it);
			}
		}
	}
};