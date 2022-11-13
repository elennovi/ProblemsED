#pragma once
#include <iomanip>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <queue>
using namespace std;

using fecha = string;
using cod = string;
using cantidad = int;
using cliente = string;

struct tInfoProducto {
	cantidad total;
	map<fecha, cantidad> fechas;
};

class Tienda {
public:
	Tienda() {}

	// Coste lineal respecto al número de clientes en espera con los que cuenta
	// ese producto (O(n))
	// La función para adquirir productos en el almaceén a una fecha determinada
	vector<cliente> adquirir(cod codigo, fecha f, cantidad cant) {
		auto it0 = listasEsperaProducto.find(codigo);
		// Si no hay clientes en la lista de espera para ese producto
		if (it0 == listasEsperaProducto.end()) {
			auto it1 = almacen.find(codigo);
			// Si ese producto todavia no se habia añadido al almacén
			if (it1 == almacen.end())
				almacen.insert({ codigo, {cant, {{f, cant}}} });
			// Si ese producto ya estaba en el almacén
			else {
				it1->second.fechas.insert({ f, cant });
				it1->second.total += cant;
			}
			return {};
		}
		// Si hay clientes en la lista de espera para ese producto
		else {
			cantidad aux = cant;
			vector<cliente> v;
			// Si tenemos clientes a la cola les vamos dando sus productos
			// uno a uno hasta que se vacie o nos quedemos sin productos
			while (!it0->second.empty() && aux > 0) {
				v.push_back(it0->second.front());
				it0->second.pop();
				aux--;
			}
			// Si tenemos productos todavia por vender los añadimos al almacen
			// para futuros clientes
			if (aux > 0) {
				auto it1 = almacen.find(codigo);
				// Si ese producto todavia no se habia añadido al almacén
				if (it1 == almacen.end())
					almacen.insert({ codigo, {cant, {{f, cant}}} });
				// Si ese producto ya estaba en el almacén
				else {
					it1->second.fechas.insert({ f, cant });
					it1->second.total += cant;
				}
			}
			// Si nos ha quedado vacía la cola para ese producto
			if (it0->second.empty()) {
				// Eliminamos ese producto de las listas de espera
				listasEsperaProducto.erase(it0);
			}
			return v;
		}
	}

	// Coste constante O(1)
	// La función para venderle el producto con el código cod al cliente
	// dado
	pair<bool, fecha> vender(cod codigo, cliente cli) {
		auto it0 = almacen.find(codigo);
		// Si no hay existencias en el almacén
		if (it0 == almacen.end()) {
			// Hay que añadir al cliente a la cola para ese código
			// Comprobamos si nadie más está a la cola de ese código
			auto it1 = listasEsperaProducto.find(codigo);
			// Si no hay nadie esperando para ese producto
			if (it1 == listasEsperaProducto.end()) {
				queue<cliente> q;
				q.push(cli);
				// Insertamos en las listas de espera ese codigo con esa lista 
				// de espera
				listasEsperaProducto.insert({ codigo, q });
			}
			// Si ya había una o más personas esperando para ese producto
			else
				it1->second.push(cli);
			return {false, " "};
		}
		// Si hay existencias en el almacén
		else {
			// Debemos adjudicarle el producto que tenga fecha más antigua
			auto it1 = it0->second.fechas.begin(); // El que tiene fecha menor 
			// es el primero del mapa de fechas
			fecha fAntigua = it1->first;
			// Hay que restarle uno a la cantidad que se tiene de ese producto 
			// con esa fecha
			it1->second--;
			// Si ya no hay unidades para ese producto en esa fecha debemos eliminar esa
			// fecha
			if (it1->second == 0)
				it0->second.fechas.erase(it1);
			// Hay que restarle uno a la cantidad total que se tiene de ese determinado
			// producto
			it0->second.total--;
			// Si ya no hay unidades para ese producto debemos eliminar ese prducto
			if (it0->second.total == 0)
				almacen.erase(it0);
			return {true, fAntigua};
		}
	}


	// Coste O(1) constante
	// La función que devuelve cuantas unidades se tienen de un producto dado
	// su código
	cantidad cuantos(cod codigo) {
		auto it = almacen.find(codigo);
		// Si ese producto no está en el almacén
		if (it == almacen.end())
			return 0;
		else
			return it->second.total;
	}

	// Coste O(1) constante
	// La función que comprueba si existe una lista de espera para un determinado
	// producto dado su código
	bool hay_esperando(cod codigo) {
		auto it = listasEsperaProducto.find(codigo);
		// Si no tiene lista de espera
		if (it == listasEsperaProducto.end())
			return false;
		else
			return true;
	}

private:
	// Necesitamos un almacén con los productos
	unordered_map<cod, tInfoProducto> almacen;
	// Clave: el codigo del producto
	// Valor: un par con la cantidad total de productos que se tienen junto con
	// una tabla ordenada cuya clave es la fecha de adquisicion y su valor la
	// cantidad de unidades de las que se dispone por dicho producto

	// Necesitamos también un queue de clientes para cada producto
	unordered_map<cod, queue<cliente>> listasEsperaProducto;
	// Clave: el código del producto por el que están esperando
	// Valor: una queue con los clientes
};