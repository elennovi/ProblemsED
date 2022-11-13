#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
#include <string>
using namespace std;

class Persona {
public:
	Persona(string n, int e) : nombre(n), edad(e) {}
	string getNombre() { return nombre; }
	int getEdad() { return edad; }
private:
	string nombre;
	int edad;
};